#pragma once

#include "Axion/Core/Application.h"
#include "Axion/Core/Log.h"

// ---------------------------------------------------------------------------
// Entry point.
// The client (Sandbox) includes this in EXACTLY ONE .cpp file
// after defining CreateApplication().
// ---------------------------------------------------------------------------

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    Axion::Log::Init();
    AX_CORE_INFO("Axion engine initialized");

    auto app = Axion::CreateApplication();
    app->Run();
    delete app;

    return 0;
}