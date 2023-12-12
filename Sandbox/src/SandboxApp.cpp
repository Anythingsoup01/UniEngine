#include <UniHeaders.h>

#include "UniEngine/ImGui/ImGuiLayer.h"



class ExampleLayer : public UE::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), oc_Camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.0f), cameraRotation(0.0f)
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
	
			void main()
			{
			a_Position = v_Position;
			a_Color = v_Color;
			gl_Position = oc_ViewProjection * vec4(v_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 a_Position;
			in vec4 a_Color;

			void main()
			{
				color = vec4(a_Position * 0.5 + 0.5, 1.0);
				color = a_Color;
			}
		)";
		as_Shader.reset(new UE::Shader(vertexSrc, fragmentSrc));

		std::string blueVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 v_Position;
			
			uniform mat4 oc_ViewProjection;
			
			out vec3 a_Position;
	
			void main()
			{
			a_Position = v_Position;
			gl_Position = oc_ViewProjection * vec4(v_Position, 1.0);
			}
		)";

		std::string blueFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 a_Position;

			void main()
			{
				color = vec4(a_Position * 0.5 + 0.5, 1.0);
			}
		)";

		as_BlueShader.reset(new UE::Shader(blueVertexSrc, blueFragmentSrc));

	}

	void OnUpdate() override
	{

		if (UE::Input::IsKeyPressed(UE_KEY_W)) {
			cameraPosition.y += cameraMoveSpeed;
		}
		else if (UE::Input::IsKeyPressed(UE_KEY_S)) {
			cameraPosition.y -= cameraMoveSpeed;
		}
		if (UE::Input::IsKeyPressed(UE_KEY_A)) {
			cameraPosition.x -= cameraMoveSpeed;
		}
		else if (UE::Input::IsKeyPressed(UE_KEY_D)) {
			cameraPosition.x += cameraMoveSpeed;
		}

		if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_4) && UE::Input::IsKeyPressed(UE_KEY_LEFT_SHIFT)) {
			cameraRotation -= cameraRotationSpeedCombo;
		}
		else if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_5) && UE::Input::IsKeyPressed(UE_KEY_LEFT_SHIFT)) {
			cameraRotation += cameraRotationSpeedCombo;
		}

		else if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_4)) {
			cameraRotation -= cameraRotationSpeed;
		}
		else if (UE::Input::IsMouseButtonPressed(UE_MOUSE_BUTTON_5)) {
			cameraRotation += cameraRotationSpeed;
		}
		



		UE::RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 0.05f });
		UE::RenderCommand::Clear();

		oc_Camera.SetPosition(cameraPosition);
		oc_Camera.SetRotation(cameraRotation);

		UE::Renderer::BeginScene(oc_Camera);

		UE::Renderer::Submit(as_BlueShader, aa_SquareVA);
		UE::Renderer::Submit(as_Shader, aa_VertexArray);

		UE::Renderer::EndScene();

	}

	virtual void OnImGuiRender() override
	{
		
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
	float cameraMoveSpeed = 0.025f;

	float cameraRotation = 0.0f;
	float cameraRotationSpeed = .25f;
	float cameraRotationSpeedCombo = 0.5f;
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