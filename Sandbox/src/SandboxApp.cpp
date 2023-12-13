#include <UniHeaders.h>

#include "UniEngine/ImGui/ImGuiLayer.h"
#include "Platform/OpenGL/OpenGLShader.h"




class ExampleLayer : public UE::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), oc_Camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.0f), cameraRotation(0.0f), squarePos(0.0f)
	{

		aa_VertexArray.reset(UE::VertexArray::Create());

		const int z = 0;
		float vertices[3 * 7] = {
			 -0.5f, -0.5f, z, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, z, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f, 0.5f, z, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<UE::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(UE::VertexBuffer::Create(vertices, sizeof(vertices)));
		UE::BufferLayout layout = {
			{ UE::ShaderDataType::Vector3, "v_Position" },
			{ UE::ShaderDataType::Vector4, "v_Color" }
		};

		vertexBuffer->SetLayout(layout);
		aa_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<UE::IndexBuffer> indexBuffer;
		indexBuffer.reset(UE::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		aa_VertexArray->SetIndexBuffer(indexBuffer);

		aa_SquareVA.reset(UE::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, z,
			 0.5f, -0.5f, z,
			 0.5f,  0.5f, z,
			-0.5f,  0.5f, z
		};
		std::shared_ptr<UE::VertexBuffer> squareVB; squareVB.reset(UE::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({ {UE::ShaderDataType::Vector3, "v_Position"} });
		aa_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<UE::IndexBuffer> squareIB; squareIB.reset(UE::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		aa_SquareVA->SetIndexBuffer(squareIB);


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
		as_Shader.reset(UE::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate(UE::TimeStep DeltaTime) override
	{
		UE_INFO("DeltaTime: {0}s, {1}ms", DeltaTime, DeltaTime.GetMilliseconds());
		if (UE::Input::IsKeyPressed(UE_KEY_W)) {
			cameraPosition.y += cameraMoveSpeed * DeltaTime;
		}
		else if (UE::Input::IsKeyPressed(UE_KEY_S)) {
			cameraPosition.y -= cameraMoveSpeed * DeltaTime;
		}
		if (UE::Input::IsKeyPressed(UE_KEY_A)) {
			cameraPosition.x -= cameraMoveSpeed * DeltaTime;
		}
		else if (UE::Input::IsKeyPressed(UE_KEY_D)) {
			cameraPosition.x += cameraMoveSpeed * DeltaTime;
		}

		if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_4) && UE::Input::IsKeyPressed(UE_KEY_LEFT_SHIFT)) {
			cameraRotation -= cameraRotationSpeedCombo * DeltaTime;
		}
		else if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_5) && UE::Input::IsKeyPressed(UE_KEY_LEFT_SHIFT)) {
			cameraRotation += cameraRotationSpeedCombo * DeltaTime;
		}

		else if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_4)) {
			cameraRotation -= cameraRotationSpeed * DeltaTime;
		}
		else if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_5)) {
			cameraRotation += cameraRotationSpeed * DeltaTime;
		}
		
		if (UE::Input::IsKeyPressed(UE_KEY_UP)) {
			squarePos.y += objectMoveSpeed * DeltaTime;
		}
		else if (UE::Input::IsKeyPressed(UE_KEY_DOWN)) {
			squarePos.y -= objectMoveSpeed * DeltaTime;
		}
		if (UE::Input::IsKeyPressed(UE_KEY_LEFT)) {
			squarePos.x -= objectMoveSpeed * DeltaTime;
		}
		else if (UE::Input::IsKeyPressed(UE_KEY_RIGHT)) {
			squarePos.x += objectMoveSpeed * DeltaTime;
		}


		UE::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 0.05f });
		UE::RenderCommand::Clear();

		oc_Camera.SetPosition(cameraPosition);
		oc_Camera.SetRotation(cameraRotation);

		UE::Renderer::BeginScene(oc_Camera);

		static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f));

		glm::vec4 redColor(0.8f, 0.3f, 0.2f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		
		std::dynamic_pointer_cast<UE::OpenGLShader>(as_Shader)->Bind();
		std::dynamic_pointer_cast<UE::OpenGLShader>(as_Shader)->UploadUniformFloat3("u_Color", squareColor);
		for (int y = 0; y < 5; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				glm::vec3 pos(x * 0.06f, y * 0.06f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				UE::Renderer::Submit(as_Shader, aa_SquareVA, transform);
			}
		}


		UE::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(squareColor));
		ImGui::End();
	}

	void OnEvent(UE::Event& e) override
	{
		UE::EventDispatcher dispatcher(e);


	}

private:
	std::shared_ptr<UE::VertexArray> aa_VertexArray;
	std::shared_ptr<UE::Shader> as_Shader;
	std::shared_ptr<UE::Shader> as_BlueShader;
	std::shared_ptr<UE::VertexArray> aa_SquareVA;

	UE::OrthographicCamera oc_Camera;

	glm::vec3 cameraPosition;
	float cameraMoveSpeed = 1.0f;

	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 25.f;
	float cameraRotationSpeedCombo = 50.0f;

	glm::vec3 squarePos;
	float objectMoveSpeed = 100.0f;

	glm::vec3 squareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public UE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

UE::Application* UE::CreateApplication()
{
	return new Sandbox();
}