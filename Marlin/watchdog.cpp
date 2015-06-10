#include "Marlin.h"

#ifdef USE_WATCHDOG

#include "watchdog.h"
#include "ultralcd.h"

//===========================================================================
//============================ private variables ============================
//===========================================================================

//===========================================================================
//================================ functions ================================
//===========================================================================


/// intialise watch dog with a 4 sec interrupt time
void watchdog_init()
{
  const uint32_t wdtTicks = 256;	// number of watchdog ticks @ 32768Hz/128 before the watchdog times out (max 4095)
  WDT_Enable(WDT, (wdtTicks << WDT_MR_WDV_Pos) | (wdtTicks << WDT_MR_WDD_Pos) | WDT_MR_WDRSTEN);	// enable watchdog, reset the mcu if it times out
}

/// reset watchdog. MUST be called every 1s after init or avr will reset.
void watchdog_reset() 
{
	WDT_Restart(WDT);
}

#endif
