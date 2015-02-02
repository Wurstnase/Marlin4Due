# Marlin4Due
Marlin for Adruino Due 32bit

This Version has some additional Functions.
- Faster READ/WRITE
- A low-pass filter for Temp_0
- A moving average for Temp_bed
- Modified ISR
  - HAL_step_isr with 42MHz
  - HAL_temp_isr with ~650kHz
- under config_adv you can choose your frequency when double stepping begins
