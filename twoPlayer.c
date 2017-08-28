
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>


static void count_neighbors(Cell cell , int * p1, int* p2);



Element copy_two_player_cell(Element element)
{
	Cell new_cell = create_empty_cell();
	new_cell->cellState = ((Cell)element)->cellState;
	int i;
	for(i=0 ; i < 8; i++){
		new_cell->neighbors[i] = ((Cell)element)->neighbors[i];
	}
	return new_cell;
}

void free_two_player_cell(Element element)
{
	Cell cell = element;
	if(cell == 0)
		return;

	free(cell);
}

void print_two_player_cell(Element element)
{
	Cell cell = element;
	switch(cell->cellState){
		case DEAD :
			printf(". ");
			break;
		case P1 :
			printf("X ");
			break;
		case P2 :
			printf("Y ");
			break;
		case BLANK :
		    printf(". ");
			break;
	}
}

Element evolve_two_player_cell(Element element)
{
	Cell cell = (Cell)element;
	int p1 = 0 ,p2 = 0;
	count_neighbors(cell, &p1 ,&p2);

	if(p1 + p2 <= 1 || p1 + p2 > 3){
		cell->cellState = DEAD;
	}
	else if(cell->cellState == DEAD && p1 + p2 == 3)
	{
		State state;
		if(p1 > p2)
		    state = P1;
		else
		    state = P2;
		cell->cellState = state;
	}
	else	
	{
		if(cell->cellState == P1 && p2 >= 2 && p2 <= 3)
		    cell->cellState = P2;
		if(cell->cellState == P2 && p1 >= 2 && p1 <= 3)
		    cell->cellState = P1;		
	}
	return cell;
}

static void count_neighbors(Cell cell, int * p1, int* p2)
{
	int i =0;
	State temp_cell=DEAD;
	for(i=0 ; i < 8; i++){
		temp_cell = cell->neighbors[i];
		if(temp_cell == P1)
			*p1 = *p1+1;
		if(temp_cell == P2)
			*p2 = *p2+1;
	}
}


