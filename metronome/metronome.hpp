#pragma once

#include <cstddef>
#include <vector>

class metronome
{
public:
	enum { beat_samples = 3 };
	// Constructor and destructor
	metronome() {
        m_timing = false; // Initialize m_timing to false
        m_beat_count = 60; // Initialize m_beat_count to 0
    }
	~metronome() {}
	//std::vector<std::chrono::steady_clock::time_point> taps; // list of taps, to cacluate intevrals
	bool playMode = true; //starts in learn mode, change it  later

	// Call when entering "learn" mode
	void start_timing();
	// Call when leaving "learn" mode
	void stop_timing();

	// Should only record the current time when timing
	// Insert the time at the next free position of m_beats
	void tap();

	bool is_timing() const { return m_timing; }
	// Calculate the BPM from the deltas between m_beats
	// Return 0 if there are not enough samples
	size_t get_bpm() const;

private:
	bool m_timing;
	
	// Insert new samples at the end of the array, removing the oldest
	size_t m_beats[beat_samples];
	size_t m_beat_count;
};

