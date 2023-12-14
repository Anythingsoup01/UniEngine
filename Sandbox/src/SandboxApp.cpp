#include <UniHeaders.h>
#include <UniEngine/Core/EntryPoint.h>

#include "UniEngine/ImGui/ImGuiLayer.h"
#include "Platform/OpenGL/OpenGLShader.h"

#include "Sandbox2D.h"



class ExampleLayer : public UE::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), cameraController(1920.0f / 1080.0f, true)
	{

			vertexArray = UE::VertexArray::Create();

			const int z = 0;
			float vertices[3 * 7] = {
				 -0.5f, -0.5f, z, 1.0f, 0.0f, 0.0f, 1.0f,
				 0.5f, -0.5f, z, 0.0f, 1.0f, 0.0f, 1.0f,
				 0.0f, 0.5f, z, 0.0f, 0.0f, 1.0f, 1.0f
			};

			UE::Reference<UE::VertexBuffer> vertexBuffer;
			vertexBuffer.reset(UE::VertexBuffer::Create(vertices, sizeof(vertices)));
			UE::BufferLayout layout = {
				{ UE::ShaderDataType::Vector3, "v_Position" },
				{ UE::ShaderDataType::Vector4, "v_Color" }
			};

			vertexBuffer->SetLayout(layout);
			vertexArray->AddVertexBuffer(vertexBuffer);

			unsigned int indices[3] = { 0, 1, 2 };
			UE::Reference<UE::IndexBuffer> indexBuffer;
			indexBuffer.reset(UE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
			vertexArray->SetIndexBuffer(indexBuffer);

		squareVA = UE::VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		UE::Reference<UE::VertexBuffer> squareVB; squareVB.reset(UE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{UE::ShaderDataType::Vector3, "v_Position"},
			{UE::ShaderDataType::Vector2, "a_TexCoords"}
			});
		squareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		UE::Reference<UE::IndexBuffer> squareIB; squareIB.reset(UE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 v_Position;
			layout(location = 1) in vec4 v_Color;

			out vec3 a_Position;
			out vec4 a_Color;

			uniform mat4 oc_ViewProjection;
			uniform mat4 o_Transform;
	
			void main()
			{
			a_Position = v_Position;
			a_Color = v_Color;
			gl_Position = oc_ViewProjection * o_Transform * vec4(v_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 a_Position;
			in vec4 a_Color;

			uniform vec3 u_Color;

			void main()
			{
				
				color = vec4(u_Color, 1.0);
			}
		)";
		simpleShader = UE::Shader::Create(vertexSrc, fragmentSrc);

		textureShader = UE::Shader::Create("assets/shaders/Texture.shader");

		m_Texture = (UE::Texture2D::Create("assets/textures/baldursgate.png"));

		std::dynamic_pointer_cast<UE::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<UE::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(UE::TimeStep DeltaTime) override
	{
		//Update
		cameraController.OnUpdate(DeltaTime);

		//Render
		UE::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 0.05f });
		UE::RenderCommand::Clear();

		UE::Renderer::BeginScene(cameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));

		
		std::dynamic_pointer_cast<UE::OpenGLShader>(simpleShader)->Bind();
		std::dynamic_pointer_cast<UE::OpenGLShader>(simpleShader)->UploadUniformFloat3("u_Color", squareColor);
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.06f, y * 0.06f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				UE::Renderer::Submit(simpleShader, squareVA, transform);
			}
		}

		m_Texture->Bind();
		UE::Renderer::Submit(textureShader, squareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		UE::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Inspector");

		ImGui::End();

		ImGui::Begin("Assets");

		ImGui::End();

		ImGui::Begin("Hierarchy");

		ImGui::End();
	}

	void OnEvent(UE::Event& e) override
	{
		cameraController.OnEvent(e);
	}

private:
	UE::Reference<UE::VertexArray> vertexArray;
	UE::Reference<UE::Shader> simpleShader;

	UE::Reference<UE::Shader> textureShader;
	UE::Reference<UE::VertexArray> squareVA;

	UE::Reference<UE::Texture2D> m_Texture;

	UE::OrthographicCameraController cameraController;
	glm::vec3 squareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public UE::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}

};

UE::Application* UE::CreateApplication()
{
	return new Sandbox();
}