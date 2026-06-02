#pragma once
#include "Axion/Event/Event.h"

namespace Axion {

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {
		}
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		EventType GetEventType() const override { return EventType::MouseMoved; }
		const char* GetName() const override { return "MouseMovedEvent"; }
		int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {
		}
		inline float GetXOffset() const { return m_XOffset; }
		inline float GetYOffset() const { return m_YOffset; }

		EventType GetEventType() const override { return EventType::MouseScrolled; }
		const char* GetName() const override { return "MouseScrolledEvent"; }
		int GetCategoryFlags() const override { return EventCategoryMouse | EventCategoryInput; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_Button; }
		int GetCategoryFlags() const override {
			return EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton;
		}
	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {
		}
		int m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {
		}
		EventType GetEventType() const override { return EventType::MouseButtonPressed; }
		const char* GetName() const override { return "MouseButtonPressedEvent"; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {
		}
		EventType GetEventType() const override { return EventType::MouseButtonReleased; }
		const char* GetName() const override { return "MouseButtonReleasedEvent"; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
	};

}
