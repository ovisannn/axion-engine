#pragma once
#include "Axion/Event/Event.h"

namespace Axion {
	class ApplicationCloseEvent : public Event {
	public:
		ApplicationCloseEvent() = default;

		static EventType GetStaticType() { return EventType::WindowClose; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "ApplicationCloseEvent"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class ApplicationResizeEvent : public Event {
	public:
		ApplicationResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {
		}
		static EventType GetStaticType() { return EventType::WindowResize; }
		EventType GetEventType() const override { return GetStaticType(); }
		const char* GetName() const override { return "ApplicationResizeEvent"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }
		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "ApplicationResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowFocusEvent : public Event {
	public:
		WindowFocusEvent() = default;

		EventType GetEventType() const override { return EventType::WindowFocus; }
		const char* GetName() const override { return "ApplicationFocusEvent"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class WindowLostFocusEvent : public Event {
	public:
		WindowLostFocusEvent() = default;

		EventType GetEventType() const override { return EventType::WindowLostFocus; }
		const char* GetName() const override { return "ApplicationLostFocusEvent"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class WindowMovedEvent : public Event {
	public:
		WindowMovedEvent(int x, int y)
			: m_X(x), m_Y(y) {
		}
		EventType GetEventType() const override { return EventType::WindowMoved; }
		const char* GetName() const override { return "ApplicationMovedEvent"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }
		int GetX() const { return m_X; }
		int GetY() const { return m_Y; }

	private:
		int m_X, m_Y;
	};
}