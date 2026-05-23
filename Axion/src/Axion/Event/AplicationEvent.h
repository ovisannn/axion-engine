#pragma once
#include "Axion/Event/Event.h"

namespace Axion {
	class ApplicationCloseEvent : public Event {
	public:
		ApplicationCloseEvent() = default;

		EventType GetEventType() const override { return EventType::WindowClose; }
		const char* GetName() const override { return "ApplicationCloseEvent"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }
	};

	class ApplicationResizeEvent : public Event {
	public:
		ApplicationResizeEvent(uint32_t width, uint32_t height)
			: m_Width(width), m_Height(height) {
		}
		EventType GetEventType() const override { return EventType::WindowResize; }
		const char* GetName() const override { return "ApplicationResizeEvent"; }
		int GetCategoryFlags() const override { return EventCategoryApplication; }
		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
	private:
		unsigned int m_Width, m_Height;
	};

	class WindowFocusEvent : public Event {
		
	};
	//WindowFocusEvent, WindowLostFocusEvent — no data
	//WindowMovedEvent — stores position

}