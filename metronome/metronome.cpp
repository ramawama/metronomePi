#include "metronome.hpp"



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

// bool metronome::is_timing() const{
//     return false;
// }

size_t metronome::get_bpm() const {
    return this->m_beat_count;
}

