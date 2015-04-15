# Marlin4Due 3D Printer Firmware
<img align="right" src="Documentation/Logo/Marlin%20Logo%20GitHub.png" />

### Story about Marlin 32bit
Some time ago bobc started with this port. After some time sadly he stopped with the development. So I started to take his work and try to make some small modifications. After a couple of weeks I found the most importent things which speed up my new fork. Thanks to bobc for this great work! I'm not a professional programmer and without bobc I couldn't do that.

Also a big thanks to all Marlin8bit-developers. Keep on working.

Last but not least, many thanks to Repetier. ~~His ARM-port gives me a lot of inspiration.~~
It's not just inspiration anymore. I think this ports goes now more to a mix of the ARM-part (Timer, ADC...) of Repetier and the rest (stepper control, temperature control...) with Marlin.

*Wurstnase*

### New features are:
* Steprates up to 320.000 steps/s (top for 1/128 stepper driver)
* smoother temperature (median of last 5 values)
 
### known issues:
  * watchdog doesn't work, don't activate it

---
# Marlin 3D Printer Firmware
  * [Configuration & Compilation](/Documentation/Compilation.md)
  * Supported
    * [Features](/Documentation/Features.md)
    * [Hardware](/Documentation/Hardware.md)
    * [GCodes](/Documentation/GCodes.md)
  * Notes
    * [Auto Bed Leveling](/Documentation/BedLeveling.md)
    * [Filament Sensor](/Documentation/FilamentSensor.md)
    * [Ramps Servo Power](/Documentation/RampsServoPower.md)
    * [LCD Language - Font - System](Documentation/LCDLanguageFont.md)
    * [Mesh Bed Leveling](/Documentation/MeshBedLeveling.md)

##### [RepRap.org Wiki Page](http://reprap.org/wiki/Marlin)

## Quick Information

This is a firmware for reprap single-processor electronics setups.
It also works on the Ultimaker PCB. It supports printing from SD card+Folders and look-ahead trajectory planning.
This firmware is a mashup between [Sprinter](https://github.com/kliment/Sprinter), [grbl](https://github.com/simen/grbl), and many original parts.

## Current Status: Bug Fixing


## Credits

The current Marlin4Due dev team consists of:

 - Nico [@wurstnase]
 - 

## Donation

If you find our work usefull please consider donating. Donations will be used to pay for our website http://www.marlinfirmware.org/ and to pay some food or rent money for the very active Collaborators

## License

Marlin is published under the [GPL license](/Documentation/COPYING.md) because We believe in open development.
Do not use this code in products (3D printers, CNC etc) that are closed source or are crippled by a patent.

[![Flattr the 8bit Marlin](http://api.flattr.com/button/flattr-badge-large.png)](https://flattr.com/submit/auto?user_id=ErikZalm&url=https://github.com/MarlinFirmware/Marlin&title=Marlin&language=&tags=github&category=software)
