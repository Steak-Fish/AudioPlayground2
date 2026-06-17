#pragma once

#include <atomic>
#include <vector>
#include <array>
#include <cmath>

#include "Instrument.hpp"
#include "DebugBuffer.hpp"
#include "Audio.hpp"
#include "NOscillator.hpp"

class Playground {
public:

    NOscillator instrument{3};

    void process(float* out, unsigned int nFrames);
    void noteOn(int midiNote, float velocity);
    void noteOff(int midiNote);

    void render();

private:
    Audio audio{this};
    DebugBuffer debugBuffer{bufferFrames};
};