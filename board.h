
#define BOARDSTATUS_OK		1
#define BOARDSTATUS_NOK		0

int board_initBoard(void);
void board_printBoardStatus(void);

int board_getBoardStatus(int pos);
int board_getBoardCoin(int pos);

int board_getSharkPosition(void);
int board_stepShark(void);

