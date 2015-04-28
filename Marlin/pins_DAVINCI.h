/****************************************************************************************
* Arduino Due pin assignment
*
* for DAVINCI
****************************************************************************************/
//TODO Need to add conditions and pins for DAVINCI 1.0/2.0 SF/DF 1.0A/2.0A
//TODO Need to add SDCARD PINS and Support
//TODO Need to add Sensor PINS
//TODO Need to add Light support
//TODO Need to add DAVINCI Keypad Support
//TODO Need to add DAVINCI thermistor tables for Extruder 1.0/2.0 for Extruder 1.0A/2.0A and Bed
//TODO Need Define the Serial Output properly
//TODO Need to add virtual EEPROM support
//TODO Need add watchdog support

#define X_STEP_PIN 			15
#define X_DIR_PIN			14
#define X_ENABLE_PIN		29
	
#define Y_STEP_PIN			30
#define Y_DIR_PIN		  	12
#define Y_ENABLE_PIN	  	69

#define Z_STEP_PIN         118
#define Z_DIR_PIN          119
#define Z_ENABLE_PIN       120

#define X_MIN_PIN          11
#define X_MAX_PIN          -1  //Max endstops default to disabled "-1", set to commented value to enable.
#define Y_MIN_PIN          68
#define Y_MAX_PIN          -1  //Max endstops default to disabled "-1", set to commented value to enable.
#define Z_MIN_PIN          124
#define Z_MAX_PIN          -1  //Max endstops default to disabled "-1", set to commented value to enable.

#define E0_STEP_PIN        123
#define E0_DIR_PIN         122
#define E0_ENABLE_PIN      121

#define E1_STEP_PIN        53
#define E1_DIR_PIN         3
#define E1_ENABLE_PIN      128

#define E2_STEP_PIN        -1
#define E2_DIR_PIN         -1
#define E2_ENABLE_PIN      -1

#define SDPOWER            -1
#define SDSS               55 //10 Display
#define LED_PIN            78

#define BEEPER             66

#define FAN_PIN            25

#define PS_ON_PIN          40

#define KILL_PIN           -1

#if defined(FILAMENT_SENSOR)  // FMM added for Filament Extruder
  // define analog pin for the filament width sensor input
  #define FILWIDTH_PIN        -1
#endif

#if defined(FILAMENT_RUNOUT_SENSOR)
  #define FILRUNOUT_PIN        -1
#endif

#define HEATER_BED_PIN     17    // BED
#define HEATER_0_PIN       16
#define HEATER_1_PIN       -1  // 12
#define HEATER_2_PIN       -1  // 11
#define HEATER_3_PIN       -1

#define TEMP_BED_PIN       14   // ANALOG NUMBERING
#define TEMP_0_PIN         13   // ANALOG NUMBERING
#define TEMP_1_PIN          9  // 1   // ANALOG NUMBERING
#define TEMP_2_PIN         -1  // 2   // ANALOG NUMBERING
#define TEMP_3_PIN         -1  // 3   // ANALOG NUMBERING


#define LCD_PINS_RS 		8
#define LCD_PINS_ENABLE 	125
#define LCD_PINS_D4 		38
#define LCD_PINS_D5 		39
#define LCD_PINS_D6 		40
#define LCD_PINS_D7 		41
#define LCD_PIN_RW			45
#define LCD_PIN_BL			78

#define SDCARDDETECT 		-1 //currently disabled until SDSUPPORT implemented


