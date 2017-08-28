
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

static State get_cell_state(char *state);
static void set_cell(Cell cell ,State state);
static Cell get_cell_at_location(Array board , int row,int col);
static void get_input(int *row,int *col,int size);
static Array create_board_2_dim_array(int board_size,int game_type);


Array read_board(FILE * board_file , int board_size,int game_type)
{
	Array board,board_row;
	Cell curent_Cell;

	board = create_board_2_dim_array(board_size,game_type);
	char *row;
	ALLOCATE(row,char,board_size*2+2);
	int i;
	int file_row = 0;
	while(!feof(board_file) && file_row < board_size){
		board_row = get(board,file_row);
		fgets(row,board_size*2+2,board_file);
		for(i = 0 ; i < board_size*2; i=i+2)
		{
			curent_Cell = get(board_row,i/2);
			curent_Cell->cellState = get_cell_state(row + i);			
		}
		file_row++;		
	}
	free(row);
	fill_neighbors_in_board(board,board_size);
	return board;
}

static Array create_board_2_dim_array(int board_size,int game_type)
{
	Array board, row_of_cells_array;
	Cell cell;
	board = createArray(board_size, copyArray,destroyArray,printArray,evolveArray);
	int i,j;
	for(i = 0;i < board_size;i++)
	{
//          need to put cell functions
		if(game_type ==2){
            row_of_cells_array = createArray(board_size, copy_two_player_cell,free_two_player_cell
                            ,print_two_player_cell,evolve_two_player_cell);
		}
		else{
			row_of_cells_array = createArray(board_size, copy_player_cell_G,free_player_cell_G,print_player_cell_G,evolve_player_cell_G);
		}
		for(j = 0;j < board_size;j++)
		{
				cell = create_empty_cell();
				set(row_of_cells_array,j,cell);
				if(game_type ==2)
					free_two_player_cell(cell);
				else
					free_player_cell_G(cell);
		}
		set(board ,i,row_of_cells_array);
		destroyArray(row_of_cells_array);
    }
	return board;
}

static State get_cell_state(char *state)
{
	if(*state == '.')
		return DEAD;
	if(*state == 'X')
		return P1;
	if(*state == 'Y')
		return P2;
	else
		return BLANK;
}



void fill_neighbors_in_board(Array board , int board_size){
	int i,j,size = board_size;
	Array row,down_Array, top_array;;
	Cell curent_Cell;
	Cell top_cell, top_left_cell, top_right_cell, right_cell;
	Cell left_cell, down_cell, down_left_cell, down_right_cell;
	for(i = 0;i < size;i++){
		row = get(board,i);
		for(j = 0;j < size ;j++){
			curent_Cell = get(row,j);
			if(j < size-1){
				right_cell = get(row,j+1);
				curent_Cell->neighbors[0] = right_cell->cellState; //right cell 0
				if(0 < i){
					top_array = get(board,i-1);
					top_right_cell = get(top_array,j+1);
					curent_Cell->neighbors[7] = top_right_cell->cellState; //top_right_cell 7
					top_cell = get(top_array,j);
					curent_Cell->neighbors[6] = top_cell->cellState; //top_cell 6
				}
				if(i < size-1){
					down_Array = get(board,i+1);
					down_cell = get(down_Array,j);
					curent_Cell->neighbors[2] = down_cell->cellState; //down cell 2
					down_right_cell = get(down_Array,j+1);
					curent_Cell->neighbors[1] = down_right_cell->cellState; //right down cell 1
				}
			}
			if(0 < j){
				left_cell = get(row,j-1);
				curent_Cell->neighbors[4] = left_cell->cellState; //left cell 4
				if(0 < i){
					top_array = get(board,i-1);
					top_cell = get(top_array,j);
					curent_Cell->neighbors[6] = top_cell->cellState;
					top_left_cell = get(top_array,j-1);
					curent_Cell->neighbors[5] = top_left_cell->cellState; //top_left_cell 5
				}
				if(i < size-1){
					down_Array = get(board,i+1);
					down_cell = get(down_Array,j);
					curent_Cell->neighbors[2] = down_cell->cellState;
					down_left_cell = get(down_Array,j-1);
					curent_Cell->neighbors[3] = down_left_cell->cellState; //down left cell 3
				}
			}
		}
	}

}

void print_board(Array board){
	printArray(board);
}

Array evolve_board(Array board ,int board_size){
    board = evolveArray(board);
    fill_neighbors_in_board(board,board_size);
    return board;
}
static void get_input(int *row,int *col,int size){
    printf("enter row: ");
    scanf("%d",row);
    printf("enter col: ");
    scanf("%d",col);
    while((0 > *row && *row >= size) || (0 > *col && *col >= size)){
        printf("location should be between 0 and %d",size);
        printf("enter location(row/col)");
        scanf("%d",row);
        scanf("%d",col);
    }
}

static Cell get_cell_at_location(Array board , int row,int col)
{
    Array board_row = get(board,row);
    Cell cell_at_location = get(board_row,col);
    return cell_at_location;
}

static void set_cell(Cell cell ,State state)
{
    cell->cellState = state;

}

void make_kill_move(Array board,int board_size ,State player){
    int row , col , size = 0;
    printf("enter location(row/col) for kill move \n");
	get_input(&row,&col,size);
	Cell cell_at_location = get_cell_at_location(board,row,col);
	while(cell_at_location->cellState == player || cell_at_location->cellState == DEAD)
	{
		printf("you have to choose a location of the other player \n");
		get_input(&row,&col,size);
		cell_at_location = get_cell_at_location(board,row,col);
	}
    set_cell(cell_at_location ,DEAD);
    fill_neighbors_in_board(board,board_size);
}

void make_create_move(Array board,int board_size ,State player){
    int row =0 , col = 0, size = 0;
    printf("enter location(row/col) for create move \n");
	Array board_row = get(board,row);
    	get_input(&row,&col,size);
	Cell cell_at_location = get_cell_at_location(board,row,col);
	while(cell_at_location->cellState != DEAD)
	{
		printf("you have to choose an empty location \n");
		get_input(&row,&col,size);
		cell_at_location = get_cell_at_location(board,row,col);
	}
    set_cell(cell_at_location ,player);
    fill_neighbors_in_board(board,board_size);
}
