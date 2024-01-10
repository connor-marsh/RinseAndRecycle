# RinseAndRecycle
Repository for code, schematics, and other info about the University of Pittsburgh Classroom to Community project Rinse and Recycle

Wiring info:

Power:
2 power supplies, 9V and 12V.
9V power supply plugs in via barrel jack to the RedBot Mainboard.
12V power supply uses barrel jack to jumper wire adapter to connect via solder.

5V comes from the RedBot Mainboard and is for:
Limit switch.
Beam break sensor and emitter.
Hall Effect Encoders (2x).
A4988 stepper driver logic signal.

9V is for:
Power the RedBot Mainboard.
RedBot Motors (Powered through the RedBot Mainboard built in motor drivers).

12V is for:
Pump motor power.
Stepper motor power.

Signals:
RedBot DIO 3 --> A4988 DIR | 
RedBot DIO ~9 --> A4988 STEP | 
RedBot DIO ~11 --> Pump MOSFET gate | 
RedBot A0 <-- Beam break sensor | 
RedBot A1 <-- Limit switch | 
RedBot A4 and A5 <-- Hall Effect Encoders (2x)

A4988 Stepper Driver notes:
Blue Stepper wire --> A4988 1B | 
Red Stepper wire --> A4988 1A | 
Green Stepper wire --> A4988 2A | 
Black Stepper wire --> A4988 2B ---
A4988 DIR set to HIGH will rotate Stepper Clockwise.
This will push the leadscrew nut AWAY from the stepper.
Best delay time inbetween steps is 1 millisecond.
With 500 microseconds setting A4988 STEP to HIGH
then 500 microseconds setting A4988 STEP to LOW

Sensor notes:
Beam break sensor analog read value < 100 means the beam is broken
