#pragma once

#include <cstddef>
#include <vector>
#include <iostream>
#include <chrono>

class metronome
{
public:
	enum { tap_samples = 3 };
	// Constructor and destructor
	metronome();
	~metronome();
	//std::vector<std::chrono::steady_clock::time_point> taps; // list of taps, to cacluate intevrals
	

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
	bool is_playmode() const { return playMode; }
	size_t get_bpm() const;
	void set_bpm(size_t newBPM);

	size_t get_max() const;
	size_t get_min() const;

private:
	bool m_timing;
	bool playMode;
	// Insert new samples at the end of the array, removing the oldest
	size_t m_beats[tap_samples];
	int curr_indx = 0;
	size_t m_beat_count;
	bool firstTap = true;
	std::chrono::steady_clock::time_point last_tap = std::chrono::steady_clock::time_point::min(); 

};

