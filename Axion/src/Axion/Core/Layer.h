#pragma once
#include "Axion/Event/Event.h"
#include <string>

namespace Axion {
	class Layer {
	public:
		Layer(const std::string& name= "Layer");
		virtual ~Layer() = default;
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(float) {}
		virtual void OnEvent(Event&) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}