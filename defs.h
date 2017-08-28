

#ifndef DEFS_H_
#define DEFS_H_
#include <stdlib.h>
#include <stdio.h>
/*
 * Basic definitions
 */
typedef void * Element;
typedef Element (*CopyFunction)(Element);
typedef void (*FreeFunction)(Element);
typedef void (*PrintFunction)(Element);
typedef Element (*EvolveFunction)(Element);

/*
 * Structs and enums
 */
typedef enum e_state {
	DEAD, P1, P2, BLANK
} State;

struct t_cell {
    State cellState;
    State neighbors[8];
};
typedef struct t_cell * Cell;


typedef struct t_array * Array;

/*
 * Function Decleration
 */
Array createArray(int _size, CopyFunction _copy, FreeFunction _free,
		PrintFunction _print, EvolveFunction _evolve);
void destroyArray(Element element);
void set(Array array, int i, Element element);		//assigns array[i]=element;
Element get(Array array, int i);					//returns array[i]

void printArray(Element element);
Element copyArray(Element element);
Element evolveArray(Element element);

Cell create_empty_cell();
Element copy_two_player_cell(Element element);
void free_two_player_cell(Element element);
void print_two_player_cell(Element element);
Element evolve_two_player_cell(Element element);

Element copy_player_cell_G(Element element);
void free_player_cell_G(Element element);
void print_player_cell_G(Element element);
Element evolve_player_cell_G(Element element);

Array read_board(FILE * board , int board_size,int game_type);
void fill_neighbors_in_board(Array board , int board_size);
void print_board(Array board);
Array evolve_board(Array board ,int board_size);

void make_kill_move(Array board,int board_size ,State player);
void make_create_move(Array board,int board_size ,State player);

/*
 *  Macro declarations
 */
#define ALLOCATE(var,type,num) \
		{if((var = (type*)malloc((num)*sizeof(type))) == 0) \
		{ fprintf(stderr,"Cannot allocate\n"); exit(1); }}\


#endif /* DEFS_H_ */
