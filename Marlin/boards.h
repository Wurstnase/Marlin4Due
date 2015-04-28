#ifndef BOARDS_H
#define BOARDS_H

#define BOARD_UNKNOWN -1

#ifndef __SAM3X8E__
 #error Oops!  Make sure you have 'Arduino Due' selected from the 'Tools -> Boards' menu.
#endif

#define BOARD_RADDS			402  // RADDS
#define BOARD_RAMPS_FD_V1	403  // RAMPS-FD V1
#define BOARD_RAMPS_FD_V2	404  // RAMPS-FD V2
#define BOARD_RAMPS4DUE     433  // RAMPS4DUE with AndrewBCN's RAMPS mods (http://forums.reprap.org/read.php?219,479626,page=1)
#define BOARD_DAVINCI       500  //Davinci 1.0 2.0 1.0A 2.0A 

#define MB(board) (MOTHERBOARD==BOARD_##board)

#endif //__BOARDS_H
