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
	private:
		bool m_Repeat;
	};
	class KeyReleased