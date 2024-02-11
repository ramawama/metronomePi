#include "metronome.hpp"

metronome::metronome(){
    playMode = true; // change
    
}

metronome::~metronome(){

}

void metronome::start_timing(){
    m_timing = true;
    m_beat_count = 0;
    for (int i = 0; i < beat_samples; i++){
        m_beats[i] = 0; // resetting beat array
    }
    // starts learning so reset beat_count
}

void metronome::stop_timing(){
    m_timing = false;
}

void metronome::tap(){

}

size_t metronome::get_bpm() const {
    return 60;
}

