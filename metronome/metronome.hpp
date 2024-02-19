#pragma once

#include <cstddef>
#include <vector>
#include <chrono>

class metronome
{
public:
	static const size_t beat_samples = 3;
	// Constructor and destructor
	metronome();
	~metronome();
	bool playMode;

	// Call when entering "learn" mode
	void start_timing();
	// Call when leaving "learn" mode
	void stop_timing();

	// Should only record the current time when timing
	// Insert the time at the next free position of m_beats
	void tap(size_t time);

	bool is_timing() const { return m_timing; }
	// Calculate the BPM from the deltas between m_beats
	// Return 0 if there are not enough samples
	size_t get_bpm() const;

	void set_bpm();

private:
	bool m_timing;
	
	// Insert new samples at the end of the array, removing the oldest

	std::vector<size_t> m_taps; // Use a vector to store tap times

	size_t m_beat_count;
};

