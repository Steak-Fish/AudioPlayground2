#include "Oscillator.hpp"

#include <cmath>

#include "imgui.h"
#include "imgui-knobs.hpp"

Oscillator::Oscillator(float gain) {
    this->gain.store(gain, RELAXED);
    offset.store(0, RELAXED);
    waveform = Waveform::SINE;
}

float Oscillator::process(float frequency, float& phase) {
    if(gain.load(RELAXED) == 0.0f) {
        return 0.0f;
    }
    // Simple sine wave oscillator
    float freq = offset.load(RELAXED) + frequency;
    float g = gain.load(RELAXED);

    float sample;

    switch(waveform) {
    case Waveform::SINE:
        sample = std::sin(2.0f * M_PI * phase) * g;
        break;
    case Waveform::SQUARE:
        sample = (std::fmod(std::floor(2.0 * phase), 2.0) * 2.0) - 1.0;
        break;
    case Waveform::SAW:
        sample = std::fmod(2 * phase, 2) - 1;
        break;
    case Waveform::TRIANGLE:
        sample = 4.0f * std::fabs(phase - 0.5f) - 1.0f;
        break;
    default:
        sample = 0;
    }

    phase += freq / 48000.0f;
    if (phase >= 1.0f) phase -= 1.0f;

    return sample;
}

void Oscillator::render() {
    float offsetVal = offset.load(RELAXED);
    ImGuiKnobs::Knob("Offset", &offsetVal, 0.0f, 100.0f, 0.0f, "%.1f Hz", ImGuiKnobVariant_Tick, 40.0f);
    offset.store(offsetVal, RELAXED);
    ImGui::SameLine();

    float gainValue = gain.load(RELAXED);
    ImGuiKnobs::Knob("Gain", &gainValue, 0.0f, 1.0f, 0.0f, "%.3f %", ImGuiKnobVariant_Tick, 40.0f);
    gain.store(gainValue, RELAXED);
    ImGui::SameLine();

    Waveform wf = waveform.load();
    std::string wfString = waveformToString(wf);


    if (ImGui::BeginCombo("##Waveform", wfString.c_str())) {
        for (int i = 0; i < (int) Waveform::COUNT; i++) {

            bool is_selected = (i == static_cast<int>(wf));

            if (ImGui::Selectable(waveformToString(static_cast<Waveform>(i)).c_str(), is_selected))
                waveform = static_cast<Waveform>(i);

            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }

        ImGui::EndCombo();
    }
}

std::string waveformToString(Waveform waveform) {
    switch (waveform) {
    case Waveform::SINE:
        return ("Sine");
    case Waveform::SAW:
        return ("Saw");
    case Waveform::SQUARE:
        return ("Square");
    case Waveform::TRIANGLE:
        return ("Triangle");
    default:
        return ("Undefined");
    }
}