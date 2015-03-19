// This file contains only 32bit-Due-boards

#ifndef BOARDS_H
#define BOARDS_H

#define BOARD_UNKNOWN -1

#ifndef __SAM3X8E__
 #error Oops!  Make sure you have 'Arduino Due' selected from the 'Tools -> Boards' menu.
#endif

#define BOARD_RADDS			402  // RADDS
#define BOARD_RAMPS_FDV1	403  // RAMPS-FD V1
#define BOARD_RAMPS_FDV2	404  // RAMPS-FD V2

#define MB(board) (MOTHERBOARD==BOARD_##board)

#endif //__BOARDS_H
