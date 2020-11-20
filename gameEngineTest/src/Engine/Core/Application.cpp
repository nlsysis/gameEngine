#include "egpch.h"
#include "Application.h"

#include "Engine/Events/ApplicationEvent.h"
#include "Input.h"

#include "Engine/Renderer/Renderer.h"
#include "Timestep.h"

#include <GLFW/glfw3.h>

namespace Engine
{
#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{ 
		EG_PROFILE_FUNCTION();

		EG_CORE_ASSERT(!s_Instance, "Application already exsits!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}


	Application::~Application()
	{
		EG_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::Run()
	{
		EG_PROFILE_FUNCTION();

		while (m_Running)
		{
			float time = glfwGetTime();   ///may change for multi platform
			Timestep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			//if the mian window is minimized, the operations on the Imgui will not change anything.
			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnUpdate(ts);

				m_ImGuiLayer->Begin();
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
				m_ImGuiLayer->End();
			}

			m_Window->OnUpdate();

		}

	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event & e)
	{
		EG_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer * layer)
	{
		EG_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer * layer)
	{
		EG_PROFILE_FUNCTION();

		m_LayerStack.PushOverLay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}