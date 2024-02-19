#include "metronome.hpp"

metronome::metronome(){
    m_timing = false; // Initialize m_timing to false
    m_beat_count = 60; // Initialize m_beat_count to 0
    playMode = true; //starts in learn mode, change it  later
}

metronome::~metronome() {}


void metronome::start_timing() {
    m_timing = true;
    playMode = false;
    m_taps.clear(); // Clear previous taps
}

void metronome::stop_timing() {
    m_timing = false;
    if (m_taps.size() >= beat_samples + 1) { // Ensure we have enough samples
        m_beat_count = set_bpm(); // Update BPM based on recent taps
        playMode = true;

    }
}

void metronome::set_bpm(){
    if (m_taps.size() < beat_samples + 1) return 0; // Not enough taps

    // Calculate total duration between first and last tap in milliseconds
    size_t average = 0;
    for (int i = 0; i < m_taps.size() - 1; i++){
        average += m_taps[i+1] - m_taps[i]; // calculate the periods between taps
    }
    average /= m_taps.size() - 1; // Calculate average period
    // Calculate average BPM
    size_t average_bpm = static_cast<size_t>(60000 * average);
    this->m_beat_count = average_bpm;
}

void metronome::tap(size_t time){
    if (m_timing) {
        m_taps.push_back(time);
    }
}

// bool metronome::is_timing() const{
//     return false;
// }

size_t metronome::get_bpm() const {
    return this->m_beat_count;
}

