#include "metronome.hpp"

metronome::metronome(){
    m_timing = true; // Initialize m_timing to false
    m_beat_count = 0; // Initialize m_beat_count to 0
    playMode = false; //starts in learn mode, change it  later
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
    if (last_tap == std::chrono::steady_clock::time_point::min()) { // First tap
        last_tap = now;
        return; // return since first tap need at least two for durations
    }
    else if (curr_indx < 3){ //first 4 taps
        m_beats[curr_indx] = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tap).count();
        last_tap = now;
        curr_indx++;
    }
    else { // iterates removing oldest 
        m_beats[0] = m_beats[1];
        m_beats[1] = m_beats[2];
        m_beats[2] = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_tap).count();
        last_tap = now;
        m_beat_count = (m_beats[0] + m_beats[1] + m_beats[2]) / 3;
    }
}

// bool metronome::is_timing() const{
//     return false;
// }

size_t metronome::get_bpm() const {
    if (curr_indx < 3) {
        std::cerr << "Not enough samples" << std::endl;
        return 0;
    }
    return this->m_beat_count;
}

