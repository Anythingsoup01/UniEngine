#include "uepch.h"
#include "Application.h"

#include "UniEngine/Log.h"

#include "UniEngine/Renderer/Rendering/Renderer.h"

#include "Input.h"


namespace UE {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	/*                 x  y*/
	float Point1[2] = {-0.5f, -0.5f};
	float Point2[2] = {0.5f, -0.5f};
	float Point3[2] = {0.0f, 0.5f};


	Application* Application::a_Instance = nullptr;


	Application::Application() 
	{
		UE_CORE_ASSERT(!a_Instance, "Application already exists!");
		a_Instance = this;

		aw_Window = std::unique_ptr<Window>(Window::Create());
		aw_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		ag_ImGuiLayer = new ImGuiLayer();
		PushOverlay(ag_ImGuiLayer);
		
		aa_VertexArray.reset(VertexArray::Create());

		const int z = 0;
		float vertices[3 * 7] = {
			 -0.5f, -0.5f, z, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, z, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f, 0.5f, z, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Vector3, "v_Position" },
			{ ShaderDataType::Vector4, "v_Color" }
		};

		vertexBuffer->SetLayout(layout);
			aa_VertexArray->AddVertexBuffer(vertexBuffer);
		
		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		aa_VertexArray->SetIndexBuffer(indexBuffer);

		aa_SquareVA.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, z,
			 0.5f, -0.5f, z,
			 0.5f,  0.5f, z,
			-0.5f,  0.5f, z
		};
		std::shared_ptr<VertexBuffer> squareVB; squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({ {ShaderDataType::Vector3, "v_Position"} });
		aa_SquareVA->AddVertexBuffer(squareVB);

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0};
		std::shared_ptr<IndexBuffer> squareIB; squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		aa_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 v_Position;
			layout(location = 1) in vec4 v_Color;

			out vec3 a_Position;
			out vec4 a_Color;
	
			void main()
			{
			a_Position = v_Position;
			a_Color = v_Color;
			gl_Position = vec4(v_Position, 1.0);
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
		as_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string blueVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 v_Position;

			out vec3 a_Position;
	
			void main()
			{
			a_Position = v_Position;
			gl_Position = vec4(v_Position, 1.0);
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

		as_BlueShader.reset(new Shader(blueVertexSrc, blueFragmentSrc));

	}

	

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		al_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		al_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = al_LayerStack.end(); it != al_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (ab_Running)
		{
			RenderCommand::SetClearColor({ 0.05f, 0.05f, 0.05f, 0.05f });
			RenderCommand::Clear();

			Renderer::BeginScene();

			
			Renderer::Submit(aa_SquareVA);


			as_Shader->Bind();
			Renderer::Submit(aa_VertexArray);
			Renderer::EndScene();


			for (Layer* layer : al_LayerStack)
				layer->OnUpdate();

			ag_ImGuiLayer->Begin();
			for (Layer* layer : al_LayerStack)
			{
				layer->OnImGuiRender();
			}
			ag_ImGuiLayer->End();

			aw_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		ab_Running = false;
		return true;
	}

}