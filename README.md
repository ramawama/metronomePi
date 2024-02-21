# metronomePi
### Group Name: Visionary Nexus Hub
### Group Members: Rama Janco, Devin DuBois, Stephen Coomes, Patrick Nguyen

## Description
We created this simple metronome project utilizing a Raspberry Pi for CIS4930, Mobile Computing. We implemented two buttons, one to switch modes and one to set the bpm, alongside two LEDs on our Pi board. We utilized C++ to implement these embedded functions. We also created a simple web interface using Next.JS to display and interact with the metronome's current BPM and its minimum and maximum tempo. These requests are performed through the Flask transport layer, ensuring we can interact with the Pi remotely.

## Frontend 
TODO: explain how to run frontend and what we did/used.

## API
### Dependencies
This requires python already installed on your system.
In order to run the API ```cd .\api\``` into the api folder and install flask using ```pip install -U Flask```. Then the api can be ran using ```python main.py```. The api is hosted on localhost and its methods can be accessed accordingly. 
Text Stephen if you have any questions/concerns!

### Documentation
Used flask and python to create a REST api that has 3 endpoints:
1. "\bpm\\"
Uses GET method to return the current BPM or update with a PUT method.
2. "\bpm\max\\"
Uses GET method to return the current maximum BPM or remove with a DELETE method.
3. "\bpm\min\\"
Uses GET method to return the current minimum BPM or sets to 0 with a DELETE method.

## Backend
To run the backend, compile the code by entering the command below. Ensure that you are in the **metronome directory** so it compiles properly.
```shell
sudo g++ -o main main.cpp metronome.cpp -lpigpio -lrt -lpthread
```
After compiling enter this command below.
```shell
sudo ./main
```
