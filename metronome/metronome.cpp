#include "metronome.hpp"

metronome::metronome(){
    m_timing = false; // Initialize m_timing to false
    m_beat_count = 60; // Initialize m_beat_count to 0
    playMode = true; //starts in learn mode, change it  later
}

metronome::~metronome() {}


void metronome::start_timing() { // learn mode
    m_timing = true;
    playMode = false;
}

void metronome::stop_timing() { //play mode
    m_timing = false;
    playMode = true;
}


void metronome::tap(){
    auto now = std::chrono::steady_clock::now();
    if (last_tap == 0) { // First tap
        last_tap = now;
        return;
    }
    else if (curr_index < 3){ //first 4 taps
        m_beats[curr_indx] = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tap).count();
        last_tap = now;
        curr_indx++;
    }
    else { // iterates removing oldest 
        m_beats[0] = m_beats[1];
        m_beats[1] = m_beats[2];
        m_beats[2] = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tap).count();
        last_tap = now;
    }
}

// bool metronome::is_timing() const{
//     return false;
// }

size_t metronome::get_bpm() const {
    return this->m_beat_count;
}

