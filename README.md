# Marlin4Due
At the moment the status is pre-alpha.

Todo:
- Implementation of more heater (Only Heatbed and Heater0 are supported at the moment)
- Add new features from Marlin8bit
- Clean code from AVR-part

This Version has some additional Functions.
- Max. speed is 320.000 steps/s (you can test more in adv_config)
- Faster READ/WRITE
- A low-pass filter for Temp_0
- A moving average for Temp_bed
- Modified ISR
  - HAL_step_isr with 42MHz
  - HAL_temp_isr with ~650kHz
- under config_adv you can choose your frequency when double stepping begins
