#pragma once
#include "Axion/Core/KeyCodes.h"
#include "Axion/Core/MouseCodes.h"


namespace Axion {
	class Input {
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
	};
}