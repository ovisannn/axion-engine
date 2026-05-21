#include <Axion.h>
#include <Axion/Core/EntryPoint.h>

// ---------------------------------------------------------------------------
// Sandbox - test application using the Axion engine.
// ---------------------------------------------------------------------------

class SandboxApp : public Axion::Application {
public:
    SandboxApp() : Application("Sandbox - Axion Engine") {
        AX_INFO("SandboxApp created");
    }

    ~SandboxApp() override {
        AX_INFO("SandboxApp destroyed");
    }
};

// Hook into the engine entry point
Axion::Application* Axion::CreateApplication() {
    return new SandboxApp();
}