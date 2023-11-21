#include <stdio.h>
#include <stdlib.h>
#include "board.h" 

#define N_BOARD			15
#define N_COINPOS		12
#define MAX_COIN		4


static int board_status[N_BOARD];
static int board_coin[N_BOARD];

static int board_sharkPosition;

int board_initBoard(void)
{
	int i;
	for (i=0;i<N_BOARD;i++)
	{
		board_status[i] = BOARDSTATUS_OK;
		board_coin[i] = 0;
	}
	
	for (i=0;i<N_COINPOS;i++)
	{
		int flag = 0;
		while(flag == 0)
		{
			int allocPos = rand()%N_BOARD;
			if(board_coin[allocPos] == 0)
			{
				board_coin[allocPos] = rand()%MAX_COIN+1;
				flag = 1;
			}
		}
	}
	
	return 0;
}

void board_printBoardStatus(void)
{
	int i;
	
	printf("-------------------- BOARD STATUS --------------------\n");
	for (i=0;i<N_BOARD;i++)
	{
		printf("|");
		if(board_status[i] == BOARDSTATUS_NOK)
			printf("X");
		else
			printf("O");
	}
	printf("|\n");
	printf("------------------------------------------------------\n");
}

int board_getBoardStatus(int pos)
{
	return board_status[pos];
}

int board_getBoardCoin(int pos)
{
	int coin = board_coin[pos];
	board_coin[pos] = 0;
	return coin;
}

//int board_getSharkPosition(void);
//int board_stepShark(void);

