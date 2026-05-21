#include "axpch.h"
#include "Axion/Core/Application.h"
#include "Axion/Core/Log.h"

#include <glad/glad.h>

namespace Axion {

    Application* Application::s_Instance = nullptr;

    Application::Application(const std::string& name) {
        s_Instance = this;
        m_Window = Window::Create(WindowProps(name));
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

            m_Window->OnUpdate();
        }

        AX_CORE_INFO("Axion application shutting down");
    }

    void Application::Close() {
        m_Running = false;
    }

}