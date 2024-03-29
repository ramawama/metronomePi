#include <chrono>
#include <thread>
using namespace std::chrono_literals;

#include <csignal>
#include <iostream>
#include <pigpio.h>
//#include <stream>
#include "api_call.cpp"
#include "metronome.hpp"

#define LED_RED   3 // red led
#define LED_GREEN 14 // green led
#define BTN_MODE  2 // blue button
#define BTN_TAP   17 //red button
std::string BPMurl = "http://127.0.0.1:5000/bpm/";
std::string BPMMaxurl = "http://127.0.0.1:5000/bpm/max/";
std::string BPMMinurl = "http://127.0.0.1:5000/bpm/min/";


metronome myMetronome;
std::chrono::steady_clock::time_point last_tap = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point last_mode_change = std::chrono::steady_clock::now();
constexpr auto debounce_period = std::chrono::milliseconds(250);


void blink() {
	bool on = true;
	// ** This loop manages LED blinking. **
	while (on) {
		if (myMetronome.is_playmode()){ //If playing, blink
			std::cout << "metronome play on" << std::endl;

			size_t getBpm = getAndParseJson(BPMurl);
			std::cout << "getBPM:  "<< getBpm <<  std::endl;

			// if (getBpm == 0) { // if failed to get bpm from server
			// 	std::cerr << "Error: Fetched BPM is 0, avoiding division by zero." << std::endl;
			// } // dont want ot divide 60k by 0
			// else getBpm = 60000 / getBpm; // since bpm is in ms already
			if (getBpm != 0) {
				getBpm = 60000 / getBpm;
				myMetronome.set_bpm(getBpm);
				std::cout << "BPM changed from user input" << std::endl;
			}

			size_t bpm = myMetronome.get_bpm(); // get current bpm
			auto delay = std::chrono::milliseconds(bpm); // bpm -> ms
			// The LED state will toggle for delay.
			gpioWrite(LED_GREEN, 1); // turn it on 
			std::this_thread::sleep_for(delay/2);
			gpioWrite(LED_GREEN, 0); // turn it off 
			std::this_thread::sleep_for(delay/2);

		}
		else {
			std::this_thread::sleep_for(1s);
			std::cout << "metronome play off" << std::endl;
		}
	}
}

void mode_change(int gpio, int level, uint32_t tick) {
    // Toggle metronome timing mode
    if (myMetronome.is_timing()) { // if in learn mode switch to play
        myMetronome.stop_timing();
        //gpioWrite(LED_GREEN, 1); // Turn on green LED when stopping
    } else if (myMetronome.is_playmode()) { // in play mode start learning
        myMetronome.start_timing();
		//Json for bpm call
		Json::Value root;
    	root["BPM"] = std::to_string(60000 / myMetronome.get_bpm());
    	Json::StyledWriter writer; 
    	std::string jsonData = writer.write(root);
		//Json for max call
		Json::Value max;
		max["Max"] = std::to_string(myMetronome.get_max());
		Json::StyledWriter maxWriter; 
		std::string maxData = maxWriter.write(max);
		std::cout << "MAX BPM:" << maxData << std::endl;
		//Json for min call
		Json::Value min;
		min["Min"] = std::to_string(myMetronome.get_min());
		Json::StyledWriter minWriter; 
		std::string minData = minWriter.write(min);
		sendPutRequest(BPMurl, jsonData);
		sendPutRequest(BPMMaxurl, maxData);
		sendPutRequest(BPMMinurl, minData);
        gpioWrite(LED_GREEN,0); // Turn off green LED when starting
    }
}

void tap_input(int gpio, int level, uint32_t tick) {
	auto now = std::chrono::steady_clock::now();
	if ((now - last_mode_change > debounce_period) && myMetronome.is_timing()){
		myMetronome.tap();
		// Flash red LED on tap
		gpioWrite(LED_RED, 1);
		std::this_thread::sleep_for(100ms);
		gpioWrite(LED_RED, 0);
	}
    
}

int main(){
	if (gpioInitialise() < 0) { //init gpio
			std::cerr << "Failed to initialize GPIO" << std::endl;
			return 1;
		}
	// setting LEDs as an output
	gpioSetMode(LED_RED, PI_OUTPUT); 
    gpioSetMode(LED_GREEN, PI_OUTPUT);
	// setting buttons as an input
    gpioSetMode(BTN_MODE, PI_INPUT); 
    gpioSetMode(BTN_TAP, PI_INPUT);
	
	// sets up internal state for the buttons so it does not pick up noise
	// so when it is not pressesd it is as low volt stage
	gpioSetPullUpDown(BTN_MODE, PI_PUD_DOWN);
    gpioSetPullUpDown(BTN_TAP, PI_PUD_DOWN);

	// set handlers for button presses, to change mode or set bpm
    gpioSetISRFunc(BTN_MODE, RISING_EDGE, 0, mode_change);
    gpioSetISRFunc(BTN_TAP, RISING_EDGE, 0, tap_input);

	// now congiure rest service here

	//

	// Use a separate thread for the blinking.
	// This way we do not have to worry about any delays
	// caused by polling the button state / etc.
	std::thread blink_thread(blink);
	blink_thread.detach();
	gpioWrite(LED_GREEN, 0);

	while (true) { // main input loop
	    //bool current_btn_mode_state = (digitalRead(BTN_MODE) == HIGH);

        // std::this_thread::sleep_for(1s);
        // Main loop can be used for additional tasks,
        // like updating BPM display if you have one.
    }
	gpioTerminate();
	return 0;
}



