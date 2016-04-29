

#include <stdlib.h>

#include <stdio.h>

#include <stdint.h>


//malloc
//LOGO
void init_array(char heap[]){
	//Set the metadata at the end and beg

	
uint64_t x = 2496;
	
uint64_t* ptr64 = heap;
	ptr64[0] = x;

ptr64[1249] = x;
}


//Allocate requested memory
char *my_malloc(char heap[], int numbytes) {
	//	printf("My malloc called\n");

	/*****************************

	YOUR CODE GOES HERE

	*****************************/
	int64_t* tempPtr64;
	int32_t* tempPtr32;
	int8_t* tempPtr8;

	int64_t currSize;
	int64_t tempVal64;
	int32_t tempVal32;
	int8_t tempVal8;

	int64_t val64;
	int32_t val32;
	int8_t val8;
	int8_t* currentPtr = &heap[9992];

	int64_t* ptr64 = currentPtr;
	int32_t* ptr32 = &heap[9992];
	val64 = *ptr64;
	val32 = *ptr32;
	int control = 1;
	int filled = 0; //has a space been occupied

	if (numbytes < 0){
		printf("The number of bytes requested is negative.\n");
		return NULL;
	}
	else if (numbytes == 0){
		printf("The number of bytes requested is zero.\n");
		return NULL;
	}
	else if (numbytes > 10000){
		printf("The number of bytes requested is too large.\n");
		return NULL;
	}
	else{
		//finding space
		currSize = *ptr64;

		while (control == 1){
			currSize = *ptr64;
			val64 = *ptr64;
			if (val64 > 0){//found a positive area
				
				if ( (numbytes / 4) <= val64 ){//can fit! Swap.
					if ( val64 == (numbytes/4) ){ //the value will occupy the whole free block
						*ptr64 = (-1) * val64;
						while (val64 != 0){ //go to other part of metadata
							--ptr32;
							val64 = val64 - 1;
						}
						--ptr32;
						--ptr32;
						ptr64 = ptr32; //Arrived at top of metadata
						val64 = *ptr64;
						*ptr64 = (-1) * val64; //invert the value
						++ptr32;
						++ptr32;
						currentPtr = ptr32;
						control = 0;
						filled = 1;
						return currentPtr;
					}
					else{//area is smaller than available
						val64 = numbytes / 4;
						filled = 1;
						control = 0;
						if ((numbytes % 4) != 0){
							val64 = val64 + 1;
						}
						tempVal64 = val64;
						*ptr64 = (-1) * val64;

						while (tempVal64 != 0){//go to next metadata
							--ptr32;
							tempVal64 = tempVal64 - 1;
						}
						currentPtr = ptr32;
						--ptr32;
						--ptr32;
						ptr64 = ptr32; //Arrived at top of metadata
						*ptr64 = (-1) * val64;  //filled new value

						//Check above blocks to make sure they are correct
						if (ptr64 == &heap[0]){
							return currentPtr;
							filled = 1;
							control = 0;
						}
						//not end, lets fix the above blocks
						else {
							currSize = currSize - 4;
							currSize = currSize - numbytes / 4;
							if (numbytes % 4 != 0){
								currSize = currSize - 1;
							}

							if (currSize > 4){ //enough for metadata
								--ptr32;
								--ptr32; //create next meta data
								ptr64 = ptr32;
								*ptr64 = currSize;
								tempVal64 = currSize;

								while (tempVal64 != 0){//go to next metadata
									--ptr32;
									tempVal64 = tempVal64 - 1;
								}
								--ptr32;
								--ptr32;
								ptr64 = ptr32; //Arrived at top of metadata
								*ptr64 = currSize;
								control = 0;
								filled = 1;
								return currentPtr;
							}
							else if (currSize == 4){
								currSize = currSize - 4;
								--ptr32;
								--ptr32;
								ptr64 = ptr32;
								*ptr64 = currSize;
								--ptr32;
								--ptr32;
								ptr64 = ptr32;
								*ptr64 = currSize;
								control = 0;
								filled = 1;
								return currentPtr;
							}
							else{
								control = 0;
								filled = 1;
								return currentPtr;
							}
						
						}
						
					}//end of smaller than available
				}//end of good fit

				else{//can't fit
					val64 = *ptr64;
					while (val64 != 0){
						--ptr32;
						val64 = val64 - 1;
					}
					--ptr32;
					--ptr32;
					ptr64 = ptr32; //Arrived at top of metadata

					if (ptr64 == &heap[0]){//have we arrived at end of heap
						control = 0;
						if (filled == 0){
							printf("No space is available.\n");
							return NULL;
						}
					}
					else{//didnt arrive at end, lets get next metadata
						--ptr32;
						--ptr32;
						ptr64 = ptr32;
					}
				
				}

			}//end of positive
			
			else{//negative occupied area!
				if (val64 < 0){
					val64 = val64 * (-1);
				}
				while (val64 != 0){
					--ptr32;
					val64 = val64 - 1;
				}
				--ptr32;
				--ptr32;
				ptr64 = ptr32; //Arrived at top of metadata

				if (ptr64 == &heap[0]){//have we arrived at end of heap
					control = 0;
					if (filled == 0){
						printf("No space is available.\n");
						return NULL;
					}
				}
				else{//didnt arrive at end, lets get next metadata
					--ptr32;
					--ptr32;
					ptr64 = ptr32;
				}
			}//end of else negative statement


		}

	}//finding space end

}//end of malloc

//Deallocate requested memory
void my_free(char slab[], char *p) {
	// printf("My free called\n");

	/*****************************

	YOUR CODE GOES HERE

	*****************************/
	int control = 1;
	int64_t tempJunk;
	int64_t tempValBot;
	int64_t tempValTop;
	int64_t* tempPtrTop64 = p;
	int64_t* tempPtrBot64 = p;
	int32_t* tempPtrTop32 = p;
	int32_t* tempPtrBot32 = p;
	int64_t valTop;
	int64_t valBot;

	int64_t* ptrTop64 = p;
	int32_t* ptrTop32 = p;
	int64_t* ptrBot64 = p;
	int32_t* ptrBot32 = p;
	int8_t*  ptr8;
	//Lets get to Metadata first at lower address first
	--ptrBot64;
	ptrBot32 = ptrBot64;
	if (*ptrBot64 < 0){
		*ptrBot64 = (*ptrBot64) * (-1); //invert the metadata
	}
	valBot = *ptrBot64;
	tempValBot = valBot;
	
	tempPtrBot32 = ptrBot64;
	while (tempValBot != 0){ //grab the top metadata
		++tempPtrBot32;
		tempValBot = tempValBot - 1;
	}
	++tempPtrBot32;
	++tempPtrBot32;
	ptrTop64 = tempPtrBot32;
	ptrTop32 = ptrTop64;
	*ptrTop64 = *ptrTop64 * (-1); //invert the metadata
	valTop = *ptrTop64;

	//increment pointers to potential metadata(not necessarily in bounds)
	++ptrTop32;
	++ptrTop32;
	--ptrBot32;
	--ptrBot32;
	tempPtrBot64 = ptrBot32; //used for comparison
	tempPtrTop64 = ptrTop32; //used for comparison
	tempPtrBot32 = ptrBot32; //used for comparison
	tempPtrTop32 = ptrTop32; //used for comparison

	//Lets take a look at the top first!
	while (control == 1){//inside the loop for checking
		if ( (&slab[9992] == ptrTop64) || (*tempPtrTop64 < 0) ){
			
			if ( (&slab[0] == ptrBot64) || (*tempPtrBot64 < 0) ){
				//do nothing since bounded on both sides
				control = 0;
			}
			else{

				tempValBot = *tempPtrBot64;
				tempJunk = tempValBot; //used as intermediate value to save metadata
				while (tempValBot != 0){ //grab the most bottom metadata
					--ptrBot32;
					tempValBot = tempValBot - 1;
				}
				--ptrBot32;
				--ptrBot32;
				ptrBot64 = ptrBot32;
				*ptrBot64 = *tempPtrBot64 + 4 + *ptrTop64;
				*ptrTop64 = *ptrBot64;  //transfer all values to metadata!
				control = 0;
			}
		}//check top first
		else{//the top is positive

			tempValTop = *tempPtrTop64;
			tempJunk = tempValTop; //used as intermediate value to save metadata
			while (tempValTop != 0){ //grab the most bottom metadata
				++ptrTop32;
				tempValTop = tempValTop - 1;
			}
			++ptrTop32;
			++ptrTop32;
			ptrTop64 = ptrTop32;
			*ptrTop64 = *tempPtrTop64 + 4 + *ptrBot64;
			*ptrBot64 = *ptrTop64;  //transfer all values to metadata!
			
			if (!((&slab[0] == ptrBot64) || (*tempPtrBot64 < 0))){
				tempValBot = *tempPtrBot64;
				tempJunk = tempValBot; //used as intermediate value to save metadata
				while (tempValBot != 0){ //grab the most bottom metadata
					--ptrBot32;
					tempValBot = tempValBot - 1;
				}
				--ptrBot32;
				--ptrBot32;
				ptrBot64 = ptrBot32;
				*ptrBot64 = *tempPtrBot64 + 4 + *ptrTop64;
				*ptrTop64 = *ptrBot64;  //transfer all values to metadata!
			}
			control = 0;

		}

	}//while loop
}

void printData(char heap[]){

	int x = 9992;
	int64_t val64;
	int32_t val32;
	int8_t val8;
	int8_t* currentPtr = &heap[x];
	
	int64_t* ptr64 = currentPtr;
	int32_t* ptr32 = &heap[x];
	int8_t* ptr8 = &heap[0];

	int control = 1;
	while (control == 1){

		val64 = *ptr64;
		printf("%ld\n", val64);
		if (val64 < 0){
			val64 = val64 * (-1);
		}
		while (val64 != 0){
			--ptr32;
			val64 = val64 - 1;
		}
		--ptr32;
		--ptr32;
		ptr64 = ptr32;
		
		val64 = *ptr64;
		printf("%ld\n", val64);

		currentPtr = ptr64;
		if (currentPtr == &heap[0]){
			control = 0;
		}
		else{
			--ptr32;
			--ptr32;
			ptr64 = ptr32;
		}

	}

}