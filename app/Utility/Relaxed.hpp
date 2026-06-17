#pragma once

#define RELAXED std::memory_order_relaxed

#include "imgui.h"
#include "imgui-knobs.hpp"

constexpr unsigned int sampleRate = 48000;
extern unsigned int bufferFrames;