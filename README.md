# Chris-Controller

This project is dedicated to my sister who is forced to live with a stationary oxygen concentrator 
in her house. The unit is extremely loud and not placed in a part of the house she wants to sleep 
or be in.  However, to change the oxygen flowrate, it is necessary for someone to do it at the machine.
For someone who is not mobile, this is a dificult task.  Further complicated by the fact that
in order to get up, she must first increase her oxygen flowrate.  Not possible without a caretaker
to go to the unit and manually change it.  

While some oxygen concentrators are available with remote control flow systems, they are not
FDA approved (as of this writing), as such medical supply companies do not provide these
units.

Her options are to increase the flow at the concentrator and use a second flowmeter at her location
that moves with her.  This creates a few problems, first the backpressure for the remote flowmeter
does not allow humidification at the concentrator to work properly.  Thus she is left with dry oxygen
which results in discomfort and nose bleeds.  Second, the backpressure can cause the concetrator
to alarm repeately.  Finally, this requires more hoses at her end of the system, which tangle and 
get caught when she tries to go to her walker or wheel chair.

The following paper by Duke University (https://pmc.ncbi.nlm.nih.gov/articles/PMC10122499/) provides
the basis for which this project is undertaken.  The project recommends that the controller at the 
stationary concentrator communicate via Bluetooth to a iPhone.  This requires an app on the iPhone to
controll the unit at the concentrator.  Since I'm not that well versed in creating applications for
the Apple Store, I instead created a remote control unit (based upon the ESP32-S2 chip, using the
ESP-NOW protocol).  This system uses the 2.4GHz WiFi frequency, but does not require connection
to a local WiFi network.

Since the paper that describes the hardware is a non-commercial license (CC BY-NC 3.0), the hardware
portion of this project is non-commercial. However, the software code developed for this project
is licensed under GNU General Pulbic License

Building the Controller:

To build the Chris Controller, you will need to make the controller as well as the remote control.  The Controller consists of 3 3D printed gears, a mounting plate for the stepper motor and potentiometer and a base and cover.  The Fusion 360 files used to create the files for printing are included.  The parts were output to *stl files that were imported into PrusaSlicer.  The 3D input and output files are included in the Controller Directory.  PETG was used to print all parts. The potentiometer mounting plate requires supports on the dished part that holds the potentiometer.  The Cover has supports on the portion of the opening that accepts the 12V plug.  No other parts required supports for printing.
The stepper motor used is the 28BYJ-48 stepper motor.  This motor is found in 12V and 5V versions.  This project used the 12V version.  The potentiometer uses is the Bourns 3590-2-103L 10k ohm multiturn potentiometer.  The output jack supplied with the stepper motor is the JST 5 pin XH series connector.  The mating male connector is used on the PCB.  The potentiometer is connected to the PCB using the 2 pin JST connectors (XH series as well).  
The controller for the stepper is the ULN2003A Darlington array DIP.  Rather than use an SMT part, the DIP package was used since this is a common failure point of stepper motor systems.  Thus, using a 16pin socket on the PCB, the ULN2003A is easily replaceable.
The PCB uses an ESP32-S2-Solo-2 module for a microcontroller.  This module has the WiFi antenna included.  The code for the controller and remote uses the ESP-NOW protocol for communication.  This eliminates the need for a WiFi connection but provides superior range over a Bluetooth connection.  

The schematic and gerber files to order the PCB are provided in the KiCad directory.  The BOM used to order the PCB’s do not include the ESP32 module or any through hole parts (sockets, etc.) since these are easily added.  The ESP32 module is relatively inexpensive, but when supplied as a separate module, and not part of development kit, it must first be programmed prior to soldering to the PCB.  There is no way to update the firmware of the ESP32 once installed, other than Over-The -Air updates.  Therefore, the first loading of the firmware requires a wired connection to a PC.  Using a development board with flexipins allows for easy programming of the ESP32 module before installing.  If such a board is not available (I made my own for such purposes), the schematic and PCB can be redesigned to use a ESP32-S2-DevkitC-1.  This will increase the footprint of the PCB, but can be made functional.
The power supply used is a standard 12VDC adapter.  The stepper and ULN2003A take 12V inputs, the ESP32 is supplied with 3.3V from a buck switching regulator.  A switching regulator was chosen for its efficiency.  If a linear regulator is used, accommodation for heat dissipation must be considered since dropping from 12V to 3.3V will involve significant heat on linear regulators.

