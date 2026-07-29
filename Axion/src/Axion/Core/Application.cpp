#include "axpch.h"
#include "Axion/Core/Application.h"
#include "Axion/Core/Log.h"

#include "Axion/Event/AplicationEvent.h"

#include <glad/glad.h>

namespace Axion {

    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& name, uint32_t width, uint32_t height) {
        s_Instance = this;
        m_Window = Window::Create(WindowProps(name, width, height));
        // send every event OnEvent method
		m_Window->SetEventCallback(AX_BIND_EVENT_FN(OnEvent)); //this line logging every event. do mind to enable this if you want to see them in the console
    }

    Application::~Application() {
        // Window destroyed automatically
    }

    void Application::Run() {
        AX_CORE_INFO("Axion application starting main loop");

        while (m_Running && !m_Window->ShouldClose()) {
            // Clear the screen to a dark teal 
            glClearColor(0.1f, 0.15f, 0.18f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            //OnUpdate();
            for (Layer* layer : m_LayerStack) { //<- bottom-top update
				layer->OnUpdate(0.0f);  // TODO: pass delta time later
                
				//m_Window->OnUpdate(); // Update the window after each layer update
            }

            m_Window->OnUpdate();
        }

        AX_CORE_INFO("Axion application shutting down");
    }

    void Application::Close() {
        m_Running = false;
    }

    void Application::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<ApplicationCloseEvent>(AX_BIND_EVENT_FN(OnWindowClose));
        dispatcher.Dispatch<ApplicationResizeEvent>(AX_BIND_EVENT_FN(OnWindowResize));

        //if (!e.Handled)
        //    AX_CORE_TRACE("{0}", e.ToString());

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
            if (e.Handled) {
				break;
			}
			(*it)->OnEvent(e);
        }
    }

    bool Application::OnWindowClose(ApplicationCloseEvent& e) {
        (void)e;
        Close();
        return true;  // event handled — stop propagating
    }

    bool Application::OnWindowResize(ApplicationResizeEvent& e) {
        glViewport(0, 0, static_cast<GLsizei>(e.GetWidth()), static_cast<GLsizei>(e.GetHeight()));
        return false;
    }

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay) {
		m_LayerStack.PushOverlay(overlay);
	}

}