#pragma once

#include <atomic>
#include <string>

#define RELAXED std::memory_order_relaxed

/**
 * @brief List of all waveforms
 * @note Visualization of the waveforms available at:
 *       https://www.desmos.com/calculator/9viyik7low
 */
enum class Waveform {
    SINE,
    SQUARE,
    SAW,
    TRIANGLE,
    TANH,
    
    COUNT
};

constexpr int NUM_WAVEFORMS = static_cast<int>(Waveform::COUNT);

std::string waveformToString(Waveform waveform);

class Oscillator {
public:
    Oscillator(Waveform waveform, float gain);
    Oscillator() {
        waveform.store(static_cast<int>(Waveform::SINE), RELAXED);
        gain = 0.1;
    }
    std::atomic<int> offset_semitones{0};
    std::atomic<int> offset_cents{0};
    std::atomic<float> gain;
    std::atomic<size_t> waveform;
    std::atomic<float> drive = 1.0f;

    Waveform getWafeform() const;

    float process(float frequency, float& phase);

    Oscillator(const Oscillator&) = delete;            // no copying
    Oscillator& operator=(const Oscillator&) = delete;

    // CUSTOM MOVE CONSTRUCTOR
    Oscillator(Oscillator&& other) noexcept
        : offset_semitones(other.offset_semitones.load(std::memory_order_relaxed)),
          offset_cents(other.offset_cents.load(std::memory_order_relaxed)),
          gain(other.gain.load(std::memory_order_relaxed)) {}
    Oscillator& operator=(Oscillator&&) = default;

    void render();
};