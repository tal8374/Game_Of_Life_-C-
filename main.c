

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
/*
 *
 */
int main(int argc, char* argv[]) {	
    Array board = 0;
    int generations = atoi(argv[4]) ,board_size = atoi(argv[2]) , game_type = atoi(argv[1]);
    char *board_path= argv[3];
    FILE* fp = fopen(board_path,"r");
    board = read_board(fp,board_size,game_type);
    fclose(fp);
    if(generations > 0){
	    board = evolve_board(board,board_size);
	    if(game_type == 2)
	    	print_board(board);
	    State player = P1;

	    int i;    
	    for(i = 1;i < generations;i++)
	    {
	    	if(game_type == 2)
	    	{
	    		printf("Player%d turn\n",player);
	    		make_kill_move(board, board_size , player);    		
			make_create_move(board, board_size , player);		
			if(player == P1)
				player = P2;
			else
				player = P1;
	    	}
		board = evolve_board(board,board_size);
		if(game_type == 2)
			print_board(board);
	    }
	    if(game_type == 1)
		print_board(board);
	    destroyArray(board);
    }
    else
	print_board(board);
    
    return (EXIT_SUCCESS);
}

