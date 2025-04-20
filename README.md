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

## Repository Files:

* Files necessary for 3D printing are in the folder "3D Print Files".
* The Fusion360 files used to create these files are in the folder titled "Fusion360"
* An instruction manual that describes the operation and use of the system is included as a *.pdf file in the "Instruciton Manual" folder.  
* The circuit was designed using KiCad 9.0.  The schematic as well as the PCB files are in the folder "KiCad 9.0 fiies".  This folder also has the gerber files, position files and BOM files necessary for ordering the PCB's from JLCPCB.com.
* Two other repositories are used for the code used to program the controller and the remote.  The links to these repositories are in the folders "Controller" and "Remote".

## Building the Controller:

To build the Chris Controller, you will need to make the controller as well as the remote control.  The Controller consists of 3 3D printed gears, a mounting plate for the stepper motor and potentiometer and a base and cover.  The Fusion 360 files used to create the files for printing are included.  The parts were output to *stl files that were imported into PrusaSlicer.  The 3D input and output files are included in the Controller Directory.  PETG was used to print all parts. The potentiometer mounting plate requires supports on the dished part that holds the potentiometer.  The Cover has supports on the portion of the opening that accepts the 12V plug.  No other parts required supports for printing.
The stepper motor used is the 28BYJ-48 stepper motor.  This motor is found in 12V and 5V versions.  This project used the 12V version.  The potentiometer uses is the Bourns 3590-2-103L 10k ohm multiturn potentiometer.  The output jack supplied with the stepper motor is the JST 5 pin XH series connector.  The mating male connector is used on the PCB.  The potentiometer is connected to the PCB using the 2 pin JST connectors (XH series as well).  
The controller for the stepper is the ULN2003A Darlington array DIP.  Rather than use an SMT part, the DIP package was used since this is a common failure point of stepper motor systems.  Thus, using a 16pin socket on the PCB, the ULN2003A is easily replaceable.
The PCB uses an ESP32-S2-Solo-2 module for a microcontroller.  This module has the WiFi antenna included.  The code for the controller and remote uses the ESP-NOW protocol for communication.  This eliminates the need for a WiFi connection but provides superior range over a Bluetooth connection.  

The schematic and gerber files to order the PCB are provided in the KiCad directory.  The BOM used to order the PCB’s do not include the ESP32 module or any through hole parts (sockets, etc.) since these are easily added.  The ESP32 module is relatively inexpensive, but when supplied as a separate module, and not part of development kit, it must first be programmed prior to soldering to the PCB.  There is no way to update the firmware of the ESP32 once installed, other than Over-The -Air updates.  Therefore, the first loading of the firmware requires a wired connection to a PC.  Using a development board with flexipins allows for easy programming of the ESP32 module before installing.  If such a board is not available (I made my own for such purposes), the schematic and PCB can be redesigned to use a ESP32-S2-DevkitC-1.  This will increase the footprint of the PCB, but can be made functional.
The power supply used is a standard 12VDC adapter.  The stepper and ULN2003A take 12V inputs, the ESP32 is supplied with 3.3V from a buck switching regulator.  A switching regulator was chosen for its efficiency.  If a linear regulator is used, accommodation for heat dissipation must be considered since dropping from 12V to 3.3V will involve significant heat on linear regulators.

## Building the Remote:

The remote 3d files print a total of 7 items.  These are:
	Remote Cover
	Remote Base
	Up Button
	Down Button
	Battery Box
	Battery Box Cover

The Remote Cover and the Battery Box print as two items each if you want to print text(on the cover) and battery icons (on the battery box).  The text and icons are two different parts in the Fusion360 files.

To print different colors on the same layer in Prusaslicer, first go to “General” settings and change the number of extruders to 2.  Then on the Custom Code, enter “M600” for tool change.  This will cause the printer to pause and prompt to load a new color.  This method works well when only one or two layers need a different color inserted (such as text or battery icons).  When using this method, it is best if the text/icon part is part #2.  This way the rest of the layer is printed first, and success rate is higher in getting the text to look good without lifting or other print errors.

The *.gcode files are set up to print the multicolor as described above.  The cover is designed to have a 1mm thick acrylic sheet as a display window to protect the OLED screen.  The window cover should be cut and fit to the space in the cover before gluing.  Use a 5 minute epoxy rather than a CynoAcrylic (CA, Superglue, etc.) type of glue.  The CA glues will tend to fog the acrylic sheet.

The battery box uses a total of 8 keystone style 5209 terminal clips.  The clips are inserted into the box, and the tabs then bent outward 90 degrees.  The tabs then may be soldered to provide the 4 cells in series (i.e. positive to negative with the first and last tabs being the +6V and -0V tabs).

The positive tab is then routed to the slide switch (the cover is designed to use the CW Industries model G-107-SI-0005 slide switch.  The output of the slide switch, with the negative terminal of the battery box are then connected to the PCB using a JST XH series two pin connector.

Once the battery box is soldered, it may then be glued into the cover.  There are indexing tabs designed into the battery cover for the battery box.  

The two buttons (Up and Down) are also printed in PETG, I used red to offset it from the urban grey I used for the remainder of the remote.  These buttons merely fit inside the cover and are held into position by the PCB and push buttons.  The push buttons used are similar to https://www.amazon.com/Tactile-Switch-Momentary-Arduino-6x6x5mm/dp/B06XRH6GNX

Only two buttons are exposed by to the push buttons that are printed (the up and down buttons).  The calibration button is accessible using a paper clip through the small hole in the upper left of the remote cover.  The fourth button of the PCB is for OTA updates and is not accessible with the cover in place.

The remote uses a 1.3” OLED monochrome I2C display.  Note the order of the 4 contacts on the PCB to ensure that the one you are using will work, if not a redesign of the PCB may be necessary so that SDL, SCL, VCC and GND align.  The OLED uses the SH1106 chip, thus the library for the remote codes is built around this display.

Similar to the controller, the remote uses an ESP32-S2-Solo-2 bare module (https://www.digikey.com/en/products/detail/espressif-systems/ESP32-S2-SOLO-2-N4/16591892?gclid=1df37c397d151f5e88d9143c09d1c049&gclsrc=3p.ds&&utm_adgroup=General&utm_source=bing&utm_medium=cpc&utm_campaign=Dynamic%20Search_EN_RLSA_Cart&utm_term=digikey&utm_content=General&utm_id=bi_cmp-384476623_adg-1302921504343591_ad-81432677981980_dat-2333232393680003:loc-190_dev-c_ext-_prd-&msclkid=1df37c397d151f5e88d9143c09d1c049) .  

The module will need to be programmed before soldering to the PCB, so that OTA updates are possible.  The advantage of using the bare module rather than development board is that it drastically reduces the footprint on the PCB (thus a smaller remote) as well as reducing the vampire load when the module is put to sleep.  Most development boards use a linear voltage regulator, which will consume much more battery power than the switching regulator used in this design.



