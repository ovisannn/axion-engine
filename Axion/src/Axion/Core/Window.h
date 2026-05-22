#pragma once

#include "Axion/Core/Base.h"

#include <string>

struct GLFWwindow;

namespace Axion {

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
        Window(const WindowProps& props);
        ~Window();

        // Non-copyable
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        void OnUpdate();

        uint32_t GetWidth() const { return m_Data.Width; }
        uint32_t GetHeight() const { return m_Data.Height; }
        bool ShouldClose() const;

        void SetVSync(bool enabled);
        bool IsVSync() const { return m_Data.VSync; }

        void* GetNativeWindow() const { return m_Window; }

        static Scope<Window> Create(const WindowProps& props = WindowProps());

    private:
        void Init(const WindowProps& props);
        void Shutdown();

    private:
        GLFWwindow* m_Window = nullptr;

        struct WindowData {
            std::string Title;
            uint32_t Width = 0;
            uint32_t Height = 0;
            bool VSync = true;
        };

        WindowData m_Data;
    };

}