
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>


static void count_neighbors(Cell cell , int * p1);

Element copy_player_cell_G(Element element)
{
	Cell new_cell = create_empty_cell();
	new_cell->cellState = ((Cell)element)->cellState;
	int i;
	for(i=0 ; i < 8; i++){
		new_cell->neighbors[i] = ((Cell)element)->neighbors[i];
	}
	return new_cell;
}

void free_player_cell_G(Element element)
{
	Cell cell = element;
	if(cell == 0)
		return;

	free(cell);
}

void print_player_cell_G(Element element)
{
	Cell cell = element;
	switch(cell->cellState){
		case DEAD :
			printf(". ");
			break;
		case P1 :
			printf("X ");
			break;
		case BLANK :
		    printf(". ");
			break;
	}
}

Element evolve_player_cell_G(Element element)
{
	Cell cell = (Cell)element;

	int p1 = 0 ;
	count_neighbors(cell, &p1);
	if(p1 <= 1 || p1 > 3){
		cell->cellState = DEAD;
		return cell;
	}
	if( p1 == 3)
	{
		cell->cellState = P1;
	}

	return cell;
}

static void count_neighbors(Cell cell, int * p1)
{
	int i;
	State temp_cell=DEAD;
	for(i=0 ; i < 8; i++)
	{
		temp_cell = cell->neighbors[i];
		if(temp_cell == P1)
			*p1 = *p1+1;
	}
}
