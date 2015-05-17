/**
 * pins.h
 */

#ifndef PINS_H
#define PINS_H

// Preset optional pins
#define X_MS1_PIN -1
#define X_MS2_PIN -1
#define Y_MS1_PIN -1
#define Y_MS2_PIN -1
#define Z_MS1_PIN -1
#define Z_MS2_PIN -1
#define E0_MS1_PIN -1
#define E0_MS2_PIN -1
#define E1_MS1_PIN -1
#define E1_MS2_PIN -1
#define DIGIPOTSS_PIN -1
#define HEATER_3_PIN -1
#define TEMP_3_PIN -1

#if MB(RADDS)
  #include "pins_RADDS.h"
#elif MB(RAMPS_FD_V1) || MB(RAMPS_FD_V2)
  #include "pins_RAMPS_FD.h"
#elif MB(RAMPS4DUE)
  #include "pins_RAMPS4DUE.h"
#else
  #error Unknown MOTHERBOARD value set in Configuration.h
#endif

// List of pins which to ignore when asked to change by gcode, 0 and 1 are RX and TX, do not mess with those!
#define _E0_PINS E0_STEP_PIN, E0_DIR_PIN, E0_ENABLE_PIN, HEATER_0_PIN, analogInputToDigitalPin(TEMP_0_PIN),
#define _E1_PINS
#define _E2_PINS
#define _E3_PINS

#if EXTRUDERS > 1
  #undef _E1_PINS
  #define _E1_PINS E1_STEP_PIN, E1_DIR_PIN, E1_ENABLE_PIN, HEATER_1_PIN, analogInputToDigitalPin(TEMP_1_PIN),
  #if EXTRUDERS > 2
    #undef _E2_PINS
    #define _E2_PINS E2_STEP_PIN, E2_DIR_PIN, E2_ENABLE_PIN, HEATER_2_PIN, analogInputToDigitalPin(TEMP_2_PIN),
    #if EXTRUDERS > 3
      #undef _E3_PINS
      #define _E3_PINS E3_STEP_PIN, E3_DIR_PIN, E3_ENABLE_PIN, HEATER_3_PIN, analogInputToDigitalPin(TEMP_3_PIN),
    #endif
  #endif
#endif

#ifdef X_STOP_PIN
  #if X_HOME_DIR < 0
    #define X_MIN_PIN X_STOP_PIN
    #define X_MAX_PIN -1
  #else
    #define X_MIN_PIN -1
    #define X_MAX_PIN X_STOP_PIN
  #endif
#endif

#ifdef Y_STOP_PIN
  #if Y_HOME_DIR < 0
    #define Y_MIN_PIN Y_STOP_PIN
    #define Y_MAX_PIN -1
  #else
    #define Y_MIN_PIN -1
    #define Y_MAX_PIN Y_STOP_PIN
  #endif
#endif

#ifdef Z_STOP_PIN
  #if Z_HOME_DIR < 0
    #define Z_MIN_PIN Z_STOP_PIN
    #define Z_MAX_PIN -1
  #else
    #define Z_MIN_PIN -1
    #define Z_MAX_PIN Z_STOP_PIN
  #endif
#endif

#ifdef DISABLE_MAX_ENDSTOPS
  #undef X_MAX_PIN
  #undef Y_MAX_PIN
  #undef Z_MAX_PIN
  #define X_MAX_PIN          -1
  #define Y_MAX_PIN          -1
  #define Z_MAX_PIN          -1
#endif

#ifdef DISABLE_MIN_ENDSTOPS
  #undef X_MIN_PIN
  #undef Y_MIN_PIN
  #undef Z_MIN_PIN
  #define X_MIN_PIN          -1
  #define Y_MIN_PIN          -1
  #define Z_MIN_PIN          -1
#endif

#if defined(DISABLE_Z_PROBE_ENDSTOP) || !defined(Z_PROBE_ENDSTOP) // Allow code to compile regardless of Z_PROBE_ENDSTOP setting.
  #undef Z_PROBE_PIN
  #define Z_PROBE_PIN        -1
#endif

#ifdef DISABLE_XMAX_ENDSTOP
  #undef X_MAX_PIN
  #define X_MAX_PIN          -1
#endif

#ifdef DISABLE_XMIN_ENDSTOP
  #undef X_MIN_PIN 
  #define X_MIN_PIN          -1
#endif

#ifdef DISABLE_YMAX_ENDSTOP
  #define Y_MAX_PIN          -1
#endif

#ifdef DISABLE_YMIN_ENDSTOP
  #undef Y_MIN_PIN
  #define Y_MIN_PIN          -1
#endif

#ifdef DISABLE_ZMAX_ENDSTOP
  #undef Z_MAX_PIN
  #define Z_MAX_PIN          -1
#endif

#ifdef DISABLE_ZMIN_ENDSTOP
  #undef Z_MIN_PIN 
  #define Z_MIN_PIN          -1
#endif

#define SENSITIVE_PINS { 0, 1, \
                        X_STEP_PIN, X_DIR_PIN, X_ENABLE_PIN, X_MIN_PIN, X_MAX_PIN, \
                        Y_STEP_PIN, Y_DIR_PIN, Y_ENABLE_PIN, Y_MIN_PIN, Y_MAX_PIN, \
                        Z_STEP_PIN, Z_DIR_PIN, Z_ENABLE_PIN, Z_MIN_PIN, Z_MAX_PIN, Z_PROBE_PIN, \
                        PS_ON_PIN, HEATER_BED_PIN, FAN_PIN, \
                        _E0_PINS _E1_PINS _E2_PINS _E3_PINS \
                        analogInputToDigitalPin(TEMP_BED_PIN) \
                       }

#define HAS_DIGIPOTSS (DIGIPOTSS_PIN >= 0)

#endif //__PINS_H

