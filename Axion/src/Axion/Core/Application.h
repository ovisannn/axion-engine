#pragma once

#include "Axion/Core/Base.h"
#include "Axion/Core/Window.h"
#include "Axion/Core/LayerStack.h"

namespace Axion {

    class Event;
    class ApplicationCloseEvent;
    class ApplicationResizeEvent;

    class Application {
    public:
        Application(const std::string& name = "Axion App", uint32_t widht = 1280U, uint32_t height = 720U);
        virtual ~Application();
        virtual void OnUpdate() {};
        void Run();
        void Close();

        // Called by the Window whenever an event occurs.
        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

    private:
        // Specific handlers invoked by the EventDispatcher inside OnEvent.
        bool OnWindowClose(ApplicationCloseEvent& e);
        bool OnWindowResize(ApplicationResizeEvent& e);

        LayerStack m_LayerStack;
        Scope<Window> m_Window;
        bool m_Running = true;

        static Application* s_Instance;
    };

    // To be defined in CLIENT 
    Application* CreateApplication();

}