#include <stdio.h>
#include "books.h"
#include "stack.h"
#include <string.h>

/******************** PR2 - EX4B ********************/
void bookStack_create(tBookStack *stack) {
	stack->size=0;
}

/******************** PR2 - EX4C ********************/
tBoolean bookStack_empty(tBookStack stack) {	
	if(stack.size == 0)
		return TRUE;
	else
		return FALSE;
}

/******************** PR2 - EX4D ********************/
tError bookStack_push(tBookStack *stack, tBook newElement) {
	tError retVal = OK;
	int i;
	int pos = 1;

	//Error stack full
	if(stack->size >=MAX_BOOKS){
		retVal = ERR_MEMORY;
	
	//Move all elements one position
	}else if(stack->size > 0){

		for(i=0;i<stack->size; i++) {		
			book_cpy(&(stack->pile[stack->size-i]), stack->pile[stack->size-pos]);
			pos++;
		}
	}
	
	//Add element at the first position
	book_cpy(&(stack->pile[0]), newElement);
	stack->size++;

	return retVal;
}

/******************** PR2 - EX4E ********************/
tError bookStack_pop (tBookStack *stack, tBook *element) {
    tError retVal = OK;
	int i;
	
	book_cpy(element,stack->pile[0]);
	
	//Empty stack
	if(stack->size ==0){
		retVal = ERROR;
	
	//Move all elements one position
	}else {
		for(i=0;i<stack->size; i++) {		
			book_cpy(&(stack->pile[i]), stack->pile[i+1]);			
		}
		stack->size=stack->size-1;	
	}
	
	return retVal;
}

/******************** PR2 - EX5A ********************/
void bookStack_transfer(tBookStack *stack_dest, tBookStack *stack){
	tBook book;

	while (stack->size>0){
		//Remove element from source
		bookStack_pop(stack, &book);
		//Add element to destination
		bookStack_push(stack_dest,book);
	}	
}

/******************** PR2 - EX5B ********************/
tError bookStack_search(tBookStack *stack, char *ISBN, tBook *book){
	tError retVal = OK;
	int found = 0;
	int i;
	int j;


	for(i=0;i<stack->size; i++) {
		//If the ISBN is found 
		if(strcmp(stack->pile[i].ISBN, ISBN)== 0){
			found++;
			book_cpy(book, stack->pile[i]);
			stack->size=stack->size-1;	
			//Move books one position
			for(j=i;j<stack->size; j++) {
				book_cpy(&(stack->pile[j]), stack->pile[j+1]);
			}
		}			
	}
	
	if(found == 0) retVal=ERR_ENTRY_NOT_FOUND;
	return retVal;
}
