/****************************************************************************************
* Arduino Due pin assignment
*
* for RAMPS-FD
****************************************************************************************/

//
#ifdef MB(RAMPS_FD_V1)
  #define INVERTED_HEATER_PINS
  #define INVERTED_MOSFET_CHANNELS
   //WARNING:If you have a RAMPS_FD_V1 modded for bugfix (same http://forums.reprap.org/read.php?219,424146,507810), you must use RAMPS_FD_V2 configuration 
  // No EEPROM - unless you trivially add it . . .
  // Use 4k7 thermistor tables
#else
  // #define RAMPS_FD_V2
  // EEPROM supported
  // Use 1k thermistor tables
#endif

#define X_STEP_PIN         63
#define X_DIR_PIN          62
#define X_ENABLE_PIN       48
#define X_MIN_PIN          22
#define X_MAX_PIN          30

#define Y_STEP_PIN         65
#define Y_DIR_PIN          64
#define Y_ENABLE_PIN       46
#define Y_MIN_PIN          24
#define Y_MAX_PIN          38

#define Z_STEP_PIN         67
#define Z_DIR_PIN          66
#define Z_ENABLE_PIN       44
#define Z_MIN_PIN          26
#define Z_MAX_PIN          34

#define E0_STEP_PIN        36
#define E0_DIR_PIN         28
#define E0_ENABLE_PIN      42

#define E1_STEP_PIN        43
#define E1_DIR_PIN         41
#define E1_ENABLE_PIN      39

#define E2_STEP_PIN        32
#define E2_DIR_PIN         47
#define E2_ENABLE_PIN      45

#define SDPOWER            -1
#define SDSS               4
#define LED_PIN            13

#define BEEPER             -1

#define FAN_PIN            10 //fet3

#define PS_ON_PIN          -1

#define KILL_PIN           41 //Dawson


#define HEATER_BED_PIN     8    // BED //Dawson - OTW, not on the right power feed!

#define HEATER_0_PIN       9 //Dawson - OTW, not on the right power feed!
#define HEATER_1_PIN       -1
// #define HEATER_2_PIN       11
#define HEATER_2_PIN       -1 // Dawson - use this for stepper fan control

#define TEMP_BED_PIN       0   // ANALOG NUMBERING

#define TEMP_0_PIN         1   // ANALOG NUMBERING
#define TEMP_1_PIN         2  // 2    // ANALOG NUMBERING
#define TEMP_2_PIN         -1  // 3     // ANALOG NUMBERING

#define TEMP_3_PIN         -1   // ANALOG NUMBERING
#define TEMP_4_PIN         -1   // ANALOG NUMBERING



  #ifdef NUM_SERVOS
    #define SERVO0_PIN         7

    #if NUM_SERVOS > 1
      #define SERVO1_PIN         6
    #endif

    #if NUM_SERVOS > 2
      #define SERVO2_PIN         5
    #endif

    #if NUM_SERVOS > 3
      #define SERVO3_PIN         4
    #endif
  #endif

  #ifdef ULTRA_LCD

    #ifdef NEWPANEL
      // ramps-fd lcd adaptor
      #define LCD_PINS_RS 16
      #define LCD_PINS_ENABLE 17
      #define LCD_PINS_D4 23
      #define LCD_PINS_D5 25
      #define LCD_PINS_D6 27
      #define LCD_PINS_D7 29

      #ifdef REPRAP_DISCOUNT_SMART_CONTROLLER
        #define BEEPER 37

        #define BTN_EN1 33
        #define BTN_EN2 31
        #define BTN_ENC 35

        #define SDCARDDETECT 49
     
      #elif defined(SSD1306_OLED_I2C_CONTROLLER)
        #define BTN_EN1 31
        #define BTN_EN2 33
        #define BTN_ENC 35
        #define BEEPER -1
        #define LCD_SDSS 49
        #define SDCARDDETECT 37
        #define KILL_PIN 39
      #endif

      #endif

  #endif //ULTRA_LCD


// SPI for Max6675 Thermocouple

#ifndef SDSUPPORT
// these pins are defined in the SD library if building with SD support
  #define MAX_SCK_PIN          52
  #define MAX_MISO_PIN         50
  #define MAX_MOSI_PIN         51
  #define MAX6675_SS       53
#else
  #define MAX6675_SS       49
#endif

// --------------------------------------------------------------------------
// 
// --------------------------------------------------------------------------
