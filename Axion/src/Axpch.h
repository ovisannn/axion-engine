#pragma once

// ---------------------------------------------------------------------------
// Axion precompiled header
// Contains commonly used headers across the engine.
// ---------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <chrono>

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#ifdef AX_PLATFORM_WINDOWS
#ifndef NOMINMAX
#define NOMINMAX
#endif
#endif