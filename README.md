<!--horizontal divider(gradiant)-->
<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

<!--Repo Banner-->
<img height=350 alt="Repo Banner - AVR-Smart-Lock" src="https://capsule-render.vercel.app/api?type=waving&color=c4a2bd&height=300&section=header&text=AVR%20Smart%20Lock&fontSize=50&fontColor=ffffff&animation=fadeIn&fontAlignY=38&desc=Proteus%20Simulation%20and%20Analysis&descAlignY=60&descAlign=50"></img>

<!--Title-->
<p align="center">
  <b>AVR Smart Lock</b>
  <br> <small> <i>- A simple digital lock system using RFID, LCD, and AVR microcontroller -</i> </small> <br>
</p>  


<!--Body-->
## Introduction:

This embedded system project aimed at designing a digital lock using the CodeVisionAVR or Atmel Studio.
<br>
The system utilizes an AVR microcontroller (ATmega32) to integrate RFID technology for secure access control, alongside real-time display of time, temperature, and lock status on an LCD.
<br>
This project not only demonstrates the practical application of embedded systems but also serves as a learning tool for mastering AVR architecture, C programming, and peripheral interfacing.
<br>

## Hardware Overview:

The hardware setup includes several key components:  
- ATmega32 Microcontroller: The core of the system, responsible for processing data from the RFID reader, handling inputs, controlling outputs, and managing the overall operation of the lock.
- RFID Reader Module: Used for scanning RFID tags to authenticate users and control access to the system.
- LCD Display (16x2): Displays real-time data including time, temperature, and lock status, providing an interactive interface for users.
- LM35 Temperature Sensor: Measures the ambient temperature, with the data processed by the microcontroller’s ADC for display and monitoring.
- Other Components: Includes resistors, capacitors, LEDs, relays, and power supply units, which ensure stable operation and facilitate the control of physical lock mechanisms.
<br>

##  Software Overview:

The software is developed in C using the CodeVisionAVR IDE, focusing on efficiency and modularity.
<br>
The software is divided into the following key sections:
1. Initialization and Configuration: This section involves setting up the microcontroller’s ports, ADC, USART, and initializing the LCD display to prepare the system for operation.
2. Main Loop: The core of the program, where the system continuously updates and displays time and temperature, while remaining alert for any RFID scans that trigger access control.
3. Interrupt Handling: Critical for ensuring quick responses to RFID scans, the interrupt routines manage the detection and processing of RFID data, comparing it against pre-stored valid IDs to determine access.
<br>

## Project Goals

This project was developed with the following educational and practical objectives in mind:
- Understanding AVR Architecture: Gaining deep insights into the internal workings of the ATmega32 microcontroller.
- Mastering C Programming: Enhancing programming skills by developing complex, real-time embedded software.
- Using CodeVisionAVR: Familiarizing with the CodeVisionAVR IDE for efficient microcontroller programming.
- Peripheral Interfacing: Learning how to interface with and control various hardware components such as RFID readers, LCDs, and sensors.
- Real-Time System Design: Developing a system capable of handling real-time data processing and interrupt-driven events.
- Proteus Simulation: Successfully configuring and simulating the RFID device in Proteus.

## Conclusion

This project is more than just a digital lock; it’s a comprehensive project that blends RFID access control with real-time monitoring and user interaction.
<br>
Whether you're a student, hobbyist, or professional, this project offers some insights into the world of embedded systems, microcontroller programming, and simulation tools like Proteus.

## License:

This project is licensed under the MIT License - see the
[LICENSE.md](https://github.com/Nariman-Z/SmartLock_RFID_AVR/blob/main/LICENSE) file for
details.
<br>
<br>
<br>
<br>


<!--Footer-->
### Made with ♥️ by: [Nariman_Z](https://github.com/Nariman-Z) ###
See also: [My Website](https://nariman-z.github.io/)

<!--horizontal divider(gradiant)-->
<img src="https://user-images.githubusercontent.com/73097560/115834477-dbab4500-a447-11eb-908a-139a6edaec5c.gif">

<div>
  <p> Last Edited on:  August 10, 2024 </p>
  <!--profile visit count-->
    <a href="https://visitcount.itsvg.in">
    <img src="https://visitcount.itsvg.in/api?id=Nariman-Z&label=Total%20Views&color=12&icon=8&pretty=true" />
  </a>
</div>