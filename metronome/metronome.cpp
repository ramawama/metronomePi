#include "metronome.hpp"

metronome::metronome(){

}

metronome::~metronome(){

}

void metronome::start_timing(){
    m_timing = true;
    m_beat_count = 0;
    // starts learning so reset beat_count
}

void metronome::stop_timing(){
    m_timing = false;
}

void metronome::tap(){
    
}

size_t metronome::get_bpm() const {

}

