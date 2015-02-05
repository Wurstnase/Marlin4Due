# Marlin4Due
At the moment the status is pre-alpha.

Todo:
- at higher frequency the trapezoid should not work as expected. The acc/decc works, also the linear motion. The problem could be the small time when reaching the expected speed.
- slower READ for temperature, to be more stable
- implementation in the actual original Marlin
  - This needs alot of rework (HAL)

This Version has some additional Functions.
- Faster READ/WRITE
- A low-pass filter for Temp_0
- A moving average for Temp_bed
- Modified ISR
  - HAL_step_isr with 42MHz
  - HAL_temp_isr with ~650kHz
- under config_adv you can choose your frequency when double stepping begins
