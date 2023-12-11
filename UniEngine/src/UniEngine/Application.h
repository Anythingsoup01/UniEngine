#pragma once

#include "Core.h"

#include "Window.h"
#include "UniEngine/LayerStack.h"
#include "UniEngine/Events/Event.h"
#include "UniEngine/Events/ApplicationEvent.h"

#include "UniEngine/ImGui/ImGuiLayer.h"

#include "Renderer/Shader/Shader.h"
#include "Renderer/Buffer/Buffer.h"
#include "Renderer/Arrays/VertexArray.h"

namespace UE {

	class UE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *aw_Window; }

		inline static Application& Get() { return *a_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> aw_Window;
		ImGuiLayer* ag_ImGuiLayer;
		bool ab_Running = true;
		LayerStack al_LayerStack;

		std::shared_ptr<VertexArray> aa_VertexArray;
		std::shared_ptr<Shader> as_Shader;
		std::shared_ptr<Shader> as_BlueShader;
		std::shared_ptr<VertexArray> aa_SquareVA;

	private:
		static Application* a_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}