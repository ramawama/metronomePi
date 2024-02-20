#pragma once

#include <cstddef>
#include <vector>
#include <chrono>

class metronome
{
public:
	enum { tap_samples = 3 };
	// Constructor and destructor
	metronome();
	~metronome();
	//std::vector<std::chrono::steady_clock::time_point> taps; // list of taps, to cacluate intevrals
	bool playMode;

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
	size_t m_beats[tap_samples];
	int curr_indx = 0;
	size_t m_beat_count;
	std::chrono::steady_clock::time_point last_tap = std::chrono::steady_clock::time_point::min(); 

};

