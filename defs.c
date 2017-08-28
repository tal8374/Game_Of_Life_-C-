
#include "defs.h"

struct t_array {
	int size;
	Element* elements;
	CopyFunction copyElement;
	FreeFunction freeElement;
	PrintFunction printElement;
	EvolveFunction evolveElement;
};




Array createArray(int _size, CopyFunction _copy, FreeFunction _free,
		PrintFunction _print, EvolveFunction _evolve) {
	Array arr;
	ALLOCATE(arr,struct t_array,1);
	ALLOCATE(arr->elements,Element,_size);
	arr->size = _size;
	arr->copyElement = _copy;
	arr->freeElement = _free;
	arr->printElement = _print;
	arr->evolveElement = _evolve;
	return arr;
}

void destroyArray(Element element) {
	Array array = element;
	if(array == 0)
		return;
	int size = array->size, i;
	for (i = 0; i < size; i++) {
            array->freeElement(array->elements[i]);
	}
	if(array->elements !=0)
		free(array->elements);
	free(array);
}

void set(Array array, int i, Element element) {
	int size = array->size;
	Element t_element = array->copyElement(element);
	if (i < size) {

		array->elements[i] = t_element;
	} else {
		printf("Array out of bounds size %d index %d", i, size);
                exit(1);
	}
}

Element get(Array array, int i) {
	int size = array->size;
	if (i >= size) {
            printf("Array out of bounds size %d index %d", i, size);
            exit(1);
	}
	return array->elements[i];
}

void printArray(Element element){
        Array array = element;
	int i, size = array->size;
	for (i = 0; i < size; i++) {
		array->printElement(get(array, i));
	}
	printf("\n");
}

Element copyArray(Element element){
        Array array_old = element;
	Array array = createArray(array_old->size,array_old->copyElement, array_old->freeElement,
			 array_old->printElement, array_old->evolveElement);
	int i, size = array->size;
	for (i = 0; i < size; i++) {
		Element e = array_old->elements[i];
		set(array,i,e);
	}
	return (Element)array;
}

Element evolveArray(Element element){
	Array array = element;
	Element e,temp;
	int i, size = array->size;
	for (i = 0; i < size; i++){
		e = get(array, i);
		temp = array->evolveElement(e);
		set(array,i,temp);
		array->freeElement(temp);
	}
	return (Element)array;
}

Cell create_empty_cell()
{
	Cell new_cell;
	ALLOCATE(new_cell,struct t_cell,1);
	new_cell->cellState = DEAD;
	int i;
	for (i = 0; i < 8; i++)
	{
		new_cell->neighbors[i] = DEAD;
	}
	return new_cell;
}
