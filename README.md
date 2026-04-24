# High-Velocity Optical Trigger System 

A hardware-software integration project designed to detect and log high-speed objects using IR/optical sensors and custom C++ firmware.

##  Project Overview
This system acts as a precision "radar" for small, fast-moving objects (like a ball). It utilizes a microcontroller to bridge the gap between physical motion and digital data, providing real-time triggers based on optical interruptions.

##  Key Engineering Challenges
* **Timing Calibration:** Iteratively refined `delay()` and timing windows to synchronize software loops with the physical velocity of the target object.
* **Debouncing & Accuracy:** Implemented logic to filter out "noise" from the sensors, ensuring that a single pass results in a single, clean trigger event.
* **Logic Integration:** Designed the circuit architecture using CAD models before physical prototyping to ensure signal integrity between the sensor and the microcontroller.

##  Technical Implementation
* **Language:** Embedded C++ (Arduino)
* **Components:** IR Optical Sensors, Logic Inverters, Microcontroller (ATmega328P).
* **Concepts:** State Machines, Interrupt Latency, Signal Conditioning.

##  Future Development
* **Physical Assembly:** Currently migrating from the digital prototype to a permanent breadboard/PCB build.
* **Data Logging:** Integrating an SD card module to record velocity data for post-run analysis.
