#include "axpch.h"
#include "Axion/Core/Window.h"
#include "Axion/Core/Log.h"

#include "Axion/Event/AplicationEvent.h"
#include "Axion/Event/KeyEvent.h"
#include "Axion/Event/MouseEvent.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Axion {

    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char* description) {
        AX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Scope<Window> Window::Create(const WindowProps& props) {
        return CreateScope<Window>(props);
    }

    Window::Window(const WindowProps& props) {
        Init(props);
    }

    Window::~Window() {
        Shutdown();
    }

    void Window::Init(const WindowProps& props) {
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;

        AX_CORE_INFO("Creating window '{0}' ({1}x{2})",
            props.Title, props.Width, props.Height);

        if (s_GLFWWindowCount == 0) {
            int success = glfwInit();
            if (!success) {
                AX_CORE_CRITICAL("Could not initialize GLFW!");
                return;
            }
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        // Request OpenGL 4.5 core profile
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef AX_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif

        m_Window = glfwCreateWindow(
            static_cast<int>(props.Width),
            static_cast<int>(props.Height),
            props.Title.c_str(),
            nullptr, nullptr);

        if (!m_Window) {
            AX_CORE_CRITICAL("Failed to create GLFW window!");
            return;
        }
        ++s_GLFWWindowCount;

        glfwMakeContextCurrent(m_Window);

        // Load OpenGL via glad
        int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        if (!gladStatus) {
            AX_CORE_CRITICAL("Failed to initialize Glad!");
            return;
        }

        AX_CORE_INFO("OpenGL Info:");
        AX_CORE_INFO("  Vendor:   {0}", (const char*)glGetString(GL_VENDOR));
        AX_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        AX_CORE_INFO("  Version:  {0}", (const char*)glGetString(GL_VERSION));

        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);

        SetGLFWCallbacks();
    }

    // Register all GLFW C-style callbacks. Each one fetches WindowData back
    void Window::SetGLFWCallbacks() {
        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            data.Width = static_cast<uint32_t>(width);
            data.Height = static_cast<uint32_t>(height);

            ApplicationResizeEvent event(data.Width, data.Height);
            if (data.EventCallback) data.EventCallback(event);
        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            ApplicationCloseEvent event;
            if (data.EventCallback) data.EventCallback(event);
        });

        glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            if (focused) {
                WindowFocusEvent event;
                if (data.EventCallback) data.EventCallback(event);
            } else {
                WindowLostFocusEvent event;
                if (data.EventCallback) data.EventCallback(event);
            }
        });

        glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int x, int y) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            WindowMovedEvent event(x, y);
            if (data.EventCallback) data.EventCallback(event);
        });

        glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, false);
                    if (data.EventCallback) data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleased event(key);
                    if (data.EventCallback) data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, true);
                    if (data.EventCallback) data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int codepoint) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            KeyTypedEvent event(static_cast<int>(codepoint));
            if (data.EventCallback) data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int /*mods*/) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    if (data.EventCallback) data.EventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    if (data.EventCallback) data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
            if (data.EventCallback) data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double x, double y) {
            WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
            MouseMovedEvent event(static_cast<float>(x), static_cast<float>(y));
            if (data.EventCallback) data.EventCallback(event);
        });
    }

    void Window::Shutdown() {
        if (m_Window) {
            glfwDestroyWindow(m_Window);
            m_Window = nullptr;
            --s_GLFWWindowCount;
        }

        if (s_GLFWWindowCount == 0) {
            glfwTerminate();
        }
    }

    void Window::OnUpdate() {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::SetVSync(bool enabled) {
        glfwSwapInterval(enabled ? 1 : 0);
        m_Data.VSync = enabled;
    }

}