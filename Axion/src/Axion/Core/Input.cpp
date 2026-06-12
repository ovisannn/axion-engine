#pragma once
#include "axpch.h"
#include "Axion/Core/Application.h"
#include "Axion/Core/Input.h"
#include "Axion/Core/Log.h"
#include "Axion/Core/KeyCodes.h"

#include <GLFW/glfw3.h>

namespace Axion {

	bool Input::IsKeyPressed(KeyCode key) {
		int keycode = static_cast<int>(key);
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, static_cast<int>(keycode));

		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonPressed(MouseCode key) {
		int keycode = static_cast<int> (key);
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, keycode);

		return state == GLFW_PRESS;
	}
	std::pair<float, float> Input::GetMousePosition() {
		auto* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		
		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return { static_cast<float>(x), static_cast<float>(y) };
	}
}