#pragma once

#include "Axion/Core/Base.h"

#include <string>
#include <functional>

struct GLFWwindow;

namespace Axion {

	class Event;

    struct WindowProps {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(
            const std::string& title = "Axion Engine",
            uint32_t width = 1280,
            uint32_t height = 720)
            : Title(title), Width(width), Height(height) {
        }
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event&)>;

        Window(const WindowProps& props);
        ~Window();

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        void OnUpdate();

        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }
        bool ShouldClose() const;

        void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

        void SetVSync(bool enabled);
        bool IsVSync() const { return m_Data.VSync; }

        void* GetNativeWindow() const { return m_Window; }

        static Scope<Window> Create(const WindowProps& props = WindowProps());

    private:
        void Init(const WindowProps& props);
        void SetGLFWCallbacks();
        void Shutdown();

    private:
        GLFWwindow* m_Window = nullptr;

        struct WindowData {
            std::string Title;
            uint32_t Width = 0;
            uint32_t Height = 0;
            bool VSync = true;
            EventCallbackFn EventCallback; 
        };

        WindowData m_Data;
    };

}