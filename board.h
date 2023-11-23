
#define N_BOARD			15

#define BOARDSTATUS_OK		1
#define BOARDSTATUS_NOK		0

int board_initBoard(void);
int board_printBoardStatus(void);

int board_getBoardStatus(int pos);
int board_getBoardCoin(int pos);

//int board_getSharkPosition(void);
int board_stepShark(void);

