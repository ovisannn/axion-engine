#pragma once

#include "Axion/Core/Base.h"
#include "Axion/Core/Window.h"

namespace Axion {

    class Application {
    public:
        Application(const std::string& name = "Axion App", uint32_t widht = 1280U, uint32_t height = 720U);
        virtual ~Application();

        void Run();
        void Close();

        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

    private:
        Scope<Window> m_Window;
        bool m_Running = true;

        static Application* s_Instance;
    };

    // To be defined in CLIENT (Sandbox)
    Application* CreateApplication();

}