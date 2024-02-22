# metronomePi

### Group Name: Visionary Nexus Hub
### Group Members: Rama Janco, Devin DuBois, Stephen Coomes, Patrick Nguyen

## Description
We created this simple metronome project utilizing a Raspberry Pi for CIS4930, Mobile Computing. We implemented two buttons, one to switch modes and one to set the bpm, alongside two LEDs on our Pi board. We utilized C++ to implement these embedded functions. We also created a simple web interface using Next.JS to display and interact with the metronome's current BPM and its minimum and maximum tempo. These requests are performed through the Flask transport layer, ensuring we can interact with the Pi remotely.

## Frontend 
The frontend of this project was developed using Node.js and react, with the assistance of v0. All of the UI elements were built with [v0](https://v0.dev/r/bqcPoocq8Iu) while their functionality was implemented in typescript using Node.js.

### Dependencies
Inside the **metronome** directory, run the development server using ```npm run dev```. If you receive any errors, review [Next.js Documentation.](https://nextjs.org/docs/getting-started/installation)

### Features
- *Refresh BPM* Sends a **GET** request to the API to fetch and display the results above. 
- *Reset Min and Max* Calls a **DELETE** request from the API, removing the MIN and MAX variables locally and on the API. 
- *Set Your BPM* This box includes an input field and button. Upon the click of the button, a **PUT** request is sent to the API and updates to the user's input, provided it is valid.

## API
The API is built in python using flask and follows REST protocols, the API facilitates communication between the frontend and backend and 3 different endpoints.

### Dependencies
This requires python to be already installed on your system.
Inside the **api** directory, install flask and CORS using ```pip install -U Flask``` and ```pip install -U flask-cors```. Then the API can be run using ```python main.py```. The API is hosted on localhost, and its methods can be accessed accordingly. 
Text Stephen if you have any questions/concerns!

### Features
Endpoints:
- ```\bpm\``` Uses GET method to return the current BPM or update with a PUT method.
- ```\bpm\max\``` Uses GET method to return the current maximum BPM or remove with a DELETE method.
- ```\bpm\min\``` Uses GET method to return the current minimum BPM or sets to 0 with a DELETE method.

## Backend
The backend of this project was implemented using C++. This embedded application involved crafting a circuit on the Pi breadboard to simulate a metronome utilizing two LEDs and two buttons. Our code makes use of threads to handle blinking as well as user input. It calculates bpm based on a running average of three samples. It also calls the API to display the current maximum and minimum and set the bpm from the webpage. 

### Dependencies
To run the backend, compile the code by entering the command below. Ensure that you are in the **metronome directory** so it compiles properly.
```shell
sudo g++ -o main main.cpp metronome.cpp -lpigpio -lrt -lpthread -lcurl -ljsoncpp
```
After compiling enter this command below.
```shell
sudo ./main
```
