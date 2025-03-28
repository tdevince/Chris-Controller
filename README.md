# Chris-Controller
Project to create a remote control system for oxygen concentrators

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
