Ben says:

```
you might find this useful when your MQ-135 sensors arrive
I have mine connected directly to 5VDC, GND and A0 - no resistors
you need to download the MQ135 library from the git repo and leave the sensor running for 24 hours to burn in and calibrate
then update MQ135.h with the `rzero` when the sensor is nice and stable, and reload the sketch
should get a stable CO2 value of around 400ppm in normal conditions
```
