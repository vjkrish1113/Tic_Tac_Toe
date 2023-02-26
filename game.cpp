#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#define size 9
typedef int project(char [], char);
int win(char board[size], char player) 
{
	unsigned num[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
	int i;
	for(i = 0; i < 8; ++i)
	 {
		if(board[num[i][0]] != 0 && board[num[i][0]] == board[num[i][1]] && board[num[i][0]] == board[num[i][2]])
		 {
			if  (board[num[i][2]] == player)
				return 1;
			else if (board[num[i][2]] != player)
				return -1;
		}
	}
	return 0;
}
void drawmatch(char board[])
{
	int i;
	putchar('\n');
	for (i = 0; i < size; i+=3) 
	{
		printf(" %c | %c | %c \n", (board[i] == 0) ? ' ' : board[i],(board[i+1] == 0) ? ' ' : board[i+1], (board[i+2] == 0) ? ' ' : board[i+2]);
            if (i != 6)
			printf("---|---|---\n");
	}
	return;
}
void fillboard(char board[])
{
	int i;
	for (i = 0; i < size; ++i)
	{
		board[i] = 0;
	}
	return;
}
void copyuser(char from[], char to[])
{
	int i;
	for (i = 0; i < size; ++i) 
	{
		to[i] = from[i];
	}
	return;
}
int endgame(char board[], char player)
{
        if (win(board, player) != 0)
            return 1;
        else 
		{
		int i;
		for (i = 0; i < size; ++i) 
		{
		if (board[i] == 0) 
		{
		return 0;
		}
        }
        }
        return 1;
}
int validspace(char move)
{
        if (move == 0)
            return 1;
        else
            return 0;
}
int opponent(char player)
{
  return (player == 'x') ? 'o': 'x';
}
int minimax(char board[], char player) 
{
	if (endgame(board, player))
		return win(board, player);
	int i, score = 0, best_score = -1;
	char new_board[size];
	score = win(board, player);
	for (i = 0; i < size; ++i)
	 {
        copyuser(board, new_board);
		if (validspace(new_board[i]))
		 {
			new_board[i] = player;
			score = minimax(new_board, opponent(player)) * -1;
            if (score > best_score)
			{
			 best_score = score;
			}
		}
	}
	return best_score;	
}

int minimaxtechnique(char board[], char player)
{
	char new_board[size];
	int best_move, score = 0, best_score = -1, i;
	for (i = 0; i < size; ++i)
	{
        
		if (validspace(new_board[i]))
		 {
			new_board[i] = player;
			score = minimax(new_board, opponent(player)) * -1;
			if (score > best_score) 
			{
				best_score = score;
				best_move = i;
			}
		}
	}
	return best_move;	
}
int randommove(char board[], char player)
{
	int move = rand() % 9;
	while (!(validspace(board[move]))) 
	{
		move = rand() % 9;
	}
	return move;
}
int humanmove(char board[], char player)
{ 
printf("PLAYER\n");
printf("Enter 'O'\n");
printf("Enter the position: ");
	char move;
	move = getchar();
	while (!(isdigit(move)))
	{
		move = getchar();
	}
	return move -'0';
}
int tictactoe1(char board[], project strategy_x, project strategy_o)
{
	int player = 'x', move;
	fillboard(board);
	drawmatch(board);
	while (!(endgame(board, player)))
	{
		move = (player == 'x') ? strategy_x(board, player) : strategy_o(board, player);
		if ((move >= 0 && move <= 8) && (validspace(board[move])))
		{
			board[move] = player;
			drawmatch(board);
			player = opponent(player);
		}
	}
	int w = win (board, 'x');
        if (w == 1)
          puts ("\nX WIN\n");
        else if (w == -1)
          puts ("\nO WIN\n");
        else 
          puts ("\nDRAW\n");
	return win(board, player);
}
int main(void)
{
	system("color 4a");
	char board[size];
	srand(time(NULL));
	tictactoe1(board, minimaxtechnique, humanmove);
	return 0;
}	

