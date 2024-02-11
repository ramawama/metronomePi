#include <chrono>
#include <thread>
using namespace std::chrono_literals;

#include <csignal>
#include <iostream>
#include <pigpio.h>

#include "metronome.hpp"

#define LED_RED   3 // red led
#define LED_GREEN 14 // green led
#define BTN_MODE  26 // blue button
#define BTN_TAP   2 //red button

metronome myMetronome;

void blink() {
	bool on = false;
	// ** This loop manages LED blinking. **
	while (true) {
		if (myMetronome.playMode){ //If playing, blink
			auto bpm = myMetronome.get_bpm(); // get current bpm
			auto delay = 60000ms / bpm; // bpm -> ms
			// The LED state will toggle for delay.
			gpioWrite(LED_GREEN, 1); // turn it on 
			std::this_thread::sleep_for(delay/2);
			gpioWrite(LED_GREEN, 0); // turn it off 
			std::this_thread::sleep_for(delay/2);

		}
		else {
			std::this_thread::sleep_for(1s);
		}
	}
}

void mode_change(int gpio, int level, uint32_t tick) {
    // Toggle metronome timing mode
    if (myMetronome.is_timing()) { // if in learn mode switch to play
        myMetronome.stop_timing();
        gpioWrite(LED_GREEN, 0); // Turn off green LED when stopping
    } else { // in play mode start learning
        myMetronome.start_timing();
        gpioWrite(LED_GREEN, 1); // Turn on green LED when starting
    }
}

void tap_input(int gpio, int level, uint32_t tick) {
    myMetronome.tap();
    // Flash red LED on tap
    gpioWrite(LED_RED, 1);
    std::this_thread::sleep_for(100ms);
    gpioWrite(LED_RED, 0);
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

	while (true) { // main input loop
        // std::this_thread::sleep_for(1s);
        // Main loop can be used for additional tasks,
        // like updating BPM display if you have one.
    }
	gpioTerminate();
	return 0;
}


/* helal code 
** Remember to update these numbers to your personal setup. **
#define LED_RED   17
#define LED_GREEN 27
#define BTN_MODE  23
#define BTN_TAP   24

// Mark as volatile to ensure it works multi-threaded.
volatile bool btn_mode_pressed = false;

// Run an additional loop separate from the main one.
void blink() {
	bool on = false;
	// ** This loop manages LED blinking. **
	while (true) {
		// The LED state will toggle once every second.
		std::this_thread::sleep_for(1s);

		// Perform the blink if we are pressed,
		// otherwise just set it to off.
		if (btn_mode_pressed)
			on = !on;
		else
			on = false;

		// HIGH/LOW probably equal 1/0, but be explicit anyways.
		digitalWrite(LED_RED, (on) ? HIGH : LOW);
	}
}

// This is called when a GET request is made to "/answer".
void get42(web::http::http_request msg) {
	msg.reply(200, web::json::value::number(42));
}

// This program shows an example of input/output with GPIO, along with
// a dummy REST service.
// ** You will have to replace this with your metronome logic, but the
//    structure of this program is very relevant to what you need. **
int main() {
	// WiringPi must be initialized at the very start.
	// This setup method uses the Broadcom pin numbers. These are the
	// larger numbers like 17, 24, etc, not the 0-16 virtual ones.
	gpioInitialise();
	// Set up the directions of the pins.
	// Be careful here, an input pin set as an output could burn out.
	pinMode(LED_RED, OUTPUT);
	pinMode(BTN_MODE, INPUT);
	// Note that you can also set a pull-down here for the button,
	// if you do not want to use the physical resistor.
	//pullUpDnControl(BTN_MODE, PUD_DOWN);

	// Configure the rest services after setting up the pins,
	// but before we start using them.
	// ** You should replace these with the BPM endpoints. **
	auto get42_rest = rest::make_endpoint("/answer");
	get42_rest.support(web::http::methods::GET, get42);

	// Start the endpoints in sequence.
	get42_rest.open().wait();

	// Use a separate thread for the blinking.
	// This way we do not have to worry about any delays
	// caused by polling the button state / etc.
	std::thread blink_thread(blink);
	blink_thread.detach();

	// ** This loop manages reading button state. **
	while (true) {
		// We are using a pull-down, so pressed = HIGH.
		// If you used a pull-up, compare with LOW instead.
		btn_mode_pressed = (digitalRead(BTN_MODE) == HIGH);
		// Delay a little bit so we do not poll too heavily.
		std::this_thread::sleep_for(10ms);

		// ** Note that the above is for testing when the button
		// is held down. For detecting "taps", or momentary
		// pushes, you need to check for a "rising edge" -
		// this is when the button changes from LOW to HIGH... **
	}

	return 0;
}
*/
