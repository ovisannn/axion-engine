#include <Axion.h>
#include <Axion/Core/EntryPoint.h>
#include <Axion/Core/Input.h>
#include <Axion/Core/Log.h>
#include "Axion/Core/KeyCodes.h"


// ---------------------------------------------------------------------------
// Sandbox - test application using the engine.
// ---------------------------------------------------------------------------

class SandboxApp : public Axion::Application {
public:
    SandboxApp() : Application("Sandbox - Axion Engine", 800U, 600U) {
        AX_INFO("SandboxApp created");

    }

	void OnUpdate() override {
		if (Axion::Input::IsKeyPressed(KeyCode::W)) {
			AX_INFO("W key is pressed wolwolwolwolwo");
		}

        if (Axion::Input::IsMouseButtonPressed(MouseCode::Button0)) {
            AX_INFO("mouse button 0 is pressed");
        }
	}

    ~SandboxApp() override {
        AX_INFO("SandboxApp destroyed");
    }
};

Axion::Application* Axion::CreateApplication() {
    return new SandboxApp();
}