#pragma once
#include "Axion/Event/Event.h"

namespace Axion {

	class KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		int GetCategoryFlags() const override { return EventCategoryKeyboard | EventCategoryInput; }
	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {
		}
		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keycode, bool repeat)
			: KeyEvent(keycode), m_Repeat(repeat) {
		}
		bool IsRepeat() const { return m_Repeat; }
		EventType GetEventType() const override { return EventType::KeyPressed; }
		const char* GetName() const override { return "KeyPressedEvent"; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (repeat=" << m_Repeat << ")";
			return ss.str();
		}
	private:
		bool m_Repeat;
	};

	class KeyReleased : public KeyEvent {
	public:
		KeyReleased(int keycode)
			: KeyEvent(keycode) {
		}
		EventType GetEventType() const override { return EventType::KeyReleased; }
		const char* GetName() const override { return "KeyReleasedEvent"; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
	};

	class KeyTypedEvent : public KeyEvent {
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {
		}
		EventType GetEventType() const override { return EventType::KeyTyped; }
		const char* GetName() const override { return "KeyTypedEvent"; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
	};

}