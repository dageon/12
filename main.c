#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

#define MAX_CHARNAME	300
#define N_PLAYER		3
#define MAX_DIE			6

#define PLAYERSTATUS_LIVE	0
#define PLAYERSTATUS_DIE	1
#define PLAYERSTATUS_END	2

int player_position[N_PLAYER];
char player_name[N_PLAYER][MAX_CHARNAME];
int player_coin[N_PLAYER];
int player_status[N_PLAYER];
char player_statusString[3][MAX_CHARNAME] = {"LIVE", "DIE", "END"};

void opening(void)
{
	printf("==============================================================\n");
	printf("**********                 SHARK GAME               **********\n");
	printf("==============================================================\n");
}

int rolldie(void)
{
	return rand()%MAX_DIE+1;
}

void printPlayerPosition(int player)
{
	int i;
	for(i=0;i<N_BOARD;i++)
	{
		printf("|");
		if (player_position[player] == i)
			printf("%c", player_name[player][0]);
		else
		{
			if (board_getBoardStatus(i) == BOARDSTATUS_NOK)
				printf("X");
			else	
				printf(" ");
		}
	}
	printf("|\n");
}

void printPlayerStatus(void)
{
	int i;
	printf("player status ---\n");
	for (i=0;i<N_PLAYER;i++)
	{
		printf("%s : pos %i, coin %i, status %s\n", player_name[i], player_position[i], player_coin[i], player_statusString[player_status[i]]);
		printPlayerPosition(i);
	}
	printf("-----------------\n");
}

void checkDie(void)
{
	int i;
	for (i=0;i<N_PLAYER;i++)
		if (board_getBoardStatus(player_position[i]) == BOARDSTATUS_NOK)
			player_status[i] = PLAYERSTATUS_DIE;
}

int game_end(void)
{
	int i;
	int flag_end = 1;
	
	//if all the players are died?
	for (i=0;i<N_PLAYER;i++)
	{
		if (player_status[i] == PLAYERSTATUS_LIVE)
		{
			flag_end = 0;
			break;
		}
	}
	
	return flag_end;
}

int getAlivePlayer(void)
{
	int i;
	int cnt=0;
	for (i=0;i<N_PLAYER;i++)
	{
		if (player_status[i] != PLAYERSTATUS_DIE)
			cnt++;
	}
	
	return cnt;
}

int getWinner(void)
{
	int i;
	int winner=0;
	int max_coin=-1;
	
	for(i=0;i<N_PLAYER;i++)
	{
		if (player_coin[i] > max_coin)
		{
			max_coin = player_coin[i];
			winner = i;
		}
	}
	
	return winner;
}

int main(int argc, char *argv[])
{	
	int pos = 0;
	int i = 0;
	int turn = 0;
	
	srand((unsigned)time(NULL));
	
	//0. opening
	opening();
	
	//1-1. board init.
	board_initBoard();
	//1-2. player init.
	for (i=0;i<N_PLAYER;i++)
	{
		player_position[i] = 0;
		player_coin[i]=0;
		player_status[i] = PLAYERSTATUS_LIVE;
		printf("Player %i's name: ", i);
		scanf("%s", player_name[i]);
	}
	
	//2. game loop (플레이어 턴)
	do{
		int step;
		int coinResult;
		char c;
		
		if(player_status[turn] != PLAYERSTATUS_LIVE)
		{
			turn = (turn + 1)%N_PLAYER;
			continue;
		}
		
		//2-1. board & player status printing
		board_printBoardStatus();
		//for (i=0;i<N_PLAYER;i++)
		//	printPlayerPosition(i);
		printPlayerStatus();
		
		//2-2. roll dice
		printf("%s turn!!", player_name[turn]);
		printf("press any key to roll a dice.\n");
		scanf("%d", &c);
		fflush(stdin);
		step = rolldie();
		
		//2-3. moving
		player_position[turn] += step;
		
		if (player_position[turn] >= N_BOARD-1)
			player_position[turn] = N_BOARD-1;

		if(player_position[turn] == N_BOARD-1)
			player_status[turn] = PLAYERSTATUS_END;
			
		printf("Die result : %d, %s moved to %i!\n", step, player_name[turn], player_position[turn]); //주사위 결과 출력 
		if(player_status[turn] == PLAYERSTATUS_END)
			printf("%s reached to the end!! (coin : %i)\n", player_name[turn], player_coin[turn]); //끝에 도달한 player 결과 출력
		
		//2-4. get coin
		coinResult = board_getBoardCoin(pos);
		player_coin[turn] += coinResult;
		
		if(coinResult>0)
			printf("   -> Lucky! %s got %d coins!\n", player_name[turn], coinResult);
		
		//2-5. next turn
		turn = (turn + 1)%N_PLAYER; //wrap around
		
		//2-6. if (조건:모든 플레이어가 한번씩 턴을 돔)
		if (turn == 0)
		{
			//shark action 
			int shark_pos = board_stepShark();
			printf("Shark moved to %i\n", shark_pos);
			checkDie();
		}
		
		
		int k = 0;
		for(k=0;k<N_PLAYER;k++)
			if(player_status[k] == PLAYERSTATUS_DIE)
				printf("%s in pos %i has died!! (coin %i)\n", player_name[k], player_position[k], player_coin[k]); //상어에게 잡힌 player 결과 출력
	
	} while(!game_end());
	
	//3. 정리 (승자 계산, 출력 등) 
	printf("GAME END!!\n");
	printf("%d players are alive! winner is %s", getAlivePlayer(), player_name[getWinner()]);
	
	return 0;
}
