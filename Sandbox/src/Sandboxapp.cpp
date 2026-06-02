#include <Axion.h>
#include <Axion/Core/EntryPoint.h>

// ---------------------------------------------------------------------------
// Sandbox - test application using the engine.
// ---------------------------------------------------------------------------

class SandboxApp : public Axion::Application {
public:
    SandboxApp() : Application("Sandbox - Axion Engine", 800U, 600U) {
        AX_INFO("SandboxApp created");
    }

    ~SandboxApp() override {
        AX_INFO("SandboxApp destroyed");
    }
};

Axion::Application* Axion::CreateApplication() {
    return new SandboxApp();
}