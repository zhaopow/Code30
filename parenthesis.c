/*
Zhao Taylor
tz2857
15980
*/

//parenthesis stuff
//at here
//bud want to go????!
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // pulls in declaration of malloc, free
#include <string.h> // pulls in declaration for strlen.

static char cur[100000]; //array used to house parenthesis

bool isPalan(char a[], int index){
	int i, length;
	int flag = 0;
	length = strlen(a);
	for (i = 0; (i < length && i < index); i++){
		if (a[i] != a[index - i - 1]){
			flag = 1;
			break;
		}
	}
	if (flag){
		return 0;  //NOT A PALINDROME! RETURN 0
	}
	else{
		return 1;  //IS A PALINDROME! RETURN 1
	}
}


void pairs(int spot, int num, int op, int cl)
{//This is the recursive one, num represnets number of parenthesis
	//op stands for open brackets, cl stands for num of closed brackets
	//spot represents the current position in the string we will use
	if (cl == num) //we have finished the string and wish to print this result
	{
		printf("%s\n", cur);//Print that result!
		return;
	}
	else
	{
		if (op > cl){ //Open bracket without a closing one
			cur[spot] = ')'; //close the brackets
			pairs(spot + 1, num, op, cl + 1); //return to next position and add one closed bracket
		}
		if (op < num){ //Open brackets are not enough
			cur[spot] = '('; //Continue adding
			pairs(spot + 1, num, op + 1, cl); //
		}
	}
}

void generateAllMatchedParens(int n){
	//Function needs to generate all matched parens as described in the assignment
	if (n <= 0){ //value given is zero or negative, no parenthesis to print
		return;
	}
	else{
		pairs(0, n, 0, 0); //not a zero or negative, lets do all the pairs!
		memset(cur, 0, 100000); //erase the array data for next iteration
	}
}

void recursiveCall(char remain[], char toPrint[], int index, int flag){
	int length = strlen(remain);
	int ilength = strlen(toPrint);
	int sudo;
	sudo = length * 2 + 5;
	char *toPrint2 = (char*) malloc(sizeof(char) * sudo);
	char *remain2 = (char*) malloc(sizeof(char) * sudo);

	for (index = 1; index < (length + 1); ++index){
		strcpy(toPrint2, toPrint);
		strcpy(remain2, remain);

		if (flag == 0){
			if ((isPalan(remain2, index)) && (remain2 != "")){
				for (int i = 0; i < index; i++){
					toPrint2[i] = remain2[i];
				}
				toPrint2[index] = ' ';
				toPrint2[index + 1] = '\0';
				remain2 = remain2 + index;
				if ((remain2 == "") || (remain2[0] == '\0')) {
					toPrint2[index] = '\0';
					printf("%s\n", toPrint2);
				}
				else{
					recursiveCall(remain2, toPrint2, index, 1); //go to next instance!
				}
			}
		}
		else if (flag == 1){
			if ((isPalan(remain2, index)) && (remain2 != "")){
				char *x = &toPrint2[0];
				while (*x != '\0'){
					x++;  //Find the Null terminator!
				}

				for (int i = 0; i < index; i++){
					*x = remain2[i];
					x++;
				}
				*x = ' ';
				x++;
				*x = '\0';
				remain2 = remain2 + index;
				if ((remain2 == "") || (remain2[0] == '\0')) {
					x--;
					*x = '\0';
					printf("%s\n", toPrint2);
				}
				else{
					recursiveCall(remain2, toPrint2, index, 1); //go to next instance!
				}
			}
		}
	}
}

void generateAllPalindromicDecompositions(char str[]){
	if (str == ""){
		return;
	}
	else{
		int length;
		int index = 1;
		length = strlen(str);
		length = length * 2 + 5;
		char *toPrint = (char*) malloc(sizeof(char) * length);
		strcpy(toPrint, "");
		recursiveCall(str, toPrint, index, 0);
		return;
	}
}
//Final version
