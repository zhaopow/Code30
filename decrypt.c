/*
Zhao Taylor
*/

//bruh

#include <stdio.h>
#include <stdlib.h>
//here
//here
/*
* return 1 if the ASCII interpretation of
* c is an upper case letter.
* return 0 otherwise
*/
int isUpperCase(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1;
	}
	else {
		return 0;
	}
}

/*
* return 1 if the ASCII interpretation of
* c is a lower case letter.
* return 0 otherwise
*/
int isLowerCase(char c) {
	if (c >= 'a' && c <= 'z') {
		return 1;
	}
	else {
		return 0;
	}
}

/*
* return 1 c is an Alphabet.
* return 0 otherwise
*/
int isAlphabet(char c){
	return isUpperCase(c) || isLowerCase(c);
}

/*
* if the ASCII interpretation of c is a letter, then
* return a number between 0 and 25 indicating which letter of
* the alphabet c represents.  For example, if c is the ASCII
* encoding for 'A', then we should return 0.  If c is the
* ASCII encoding for 'e', then we should return 4.
* if the ASCII interpretation of c is not a letter, then
* return -1.
*/
int ASCII2Int(char c) {
	if (isUpperCase(c)) {
		return c - 'A';
	}
	else if (isLowerCase(c)) {
		return c - 'a';
	}
	else {
		return -1;
	}
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2UpperCase(int i){
	char c = 'A' + i;
	return c;
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2LowerCase(int i){
	char c = 'a' + i;
	return c;
}

/*
* This function takes in a message and computes the frequencies of all the alphabets
HistogramLength = 26, histogram is only words, but lower/cap don't matter (for chars)
*/
void buildHistogram(char message[], int messageLength, int histogram[], int histogramLength){
	int ABCplace;	/*The alphabetical position of the char*/
	for (int x = 0; x < histogramLength; x++){
		histogram[x] = 0;	/*Clear the values in the histogram (length is always 26 since we have 26 letters*/
	}

	for (int i = 0; i < messageLength; i++){
		if (isAlphabet(message[i]) == 1){
			ABCplace = ASCII2Int(message[i]);  /*Find the position of the letter in the alphabet*/
			histogram[ABCplace] = histogram[ABCplace] + 1; /*update one value into the histogram*/
		}
	}
}

/*
* This function computes the maximum value in an array and returns the index location\
* for which the maximum value occured
Only return most recent occurance?
*/

int maxIndex(int myArray[], int arrayLength){

	int maxLoc = 0;  /*Set the first term as beginning index*/
	int maxValue = myArray[0]; /*Load the value of the first term as the max*/
	for (int i = 0; i < arrayLength; i++){
		if (maxValue < myArray[i]){
			maxValue = myArray[i];  /*update new max*/
			maxLoc = i;  /*Update location of new index*/
		}
	}
	return maxLoc;

}

/*
* Encrypt the string s using the rotation cypher
* Each letter in s should be shifted "shift" letters to the
* right.  For example, if "shift" is 2, then "a zebra" should be
* changed to "c bgdtc".  Note that when shifting past the end
* of the alphabet, we wrap around again to a.
*
* Only change the letters in s.  Do not change spaces, punctuation
* or numbers in s.
* For full credit, you should keep upper case letters as
* upper case, and leave lower case letters as lower case.  So, if
* s had been the string "a ZeBra", you should change s to be
* "c BgDtc".
*/
void encrypt(char message[], int messageLength, int shift) {
	char newChar;  /*Encrypted Character*/
	int convChar;  /*Current Character that needs conversion*/
	for (int i = 0; i < messageLength; i++){
		if (isAlphabet(message[i]) == 1){

			if (isUpperCase(message[i]) == 1){  /*Lets look at the uppercase situation*/
				convChar = ASCII2Int(message[i]);
				convChar = convChar + shift % 26;  /*Implement the shift*/
				if (convChar > 25){  /*Account for wrap around if it occurs*/
					convChar = convChar - 26;  /*Wrap around to the beginning values if you go past Z*/
				}
				if (convChar < 0){
					convChar = convChar + 26;  /*In case it wraps around the other direction*/
				}
				newChar = int2UpperCase(convChar);  /*Convert int to ASCII value*/
				message[i] = newChar;  /*Put in new character! We are done!*/
			}

			if (isLowerCase(message[i]) == 1){  /*Lets look at the lowercase situation*/
				convChar = ASCII2Int(message[i]);
				convChar = convChar + shift % 26;  /*Implement the shift*/
				if (convChar > 25){  /*Account for wrap around if it occurs*/
					convChar = convChar - 26;  /*Wrap around to the beginning values if you go past z*/
				}
				if (convChar < 0){
					convChar = convChar + 26;  /*In case it wraps around the other direction*/
				}
				newChar = int2LowerCase(convChar);  /*Convert int to ASCII value*/
				message[i] = newChar;  /*Put in new character! We are done!*/
			}

		}
	}
}

/*
* return a number between 0 and 25 indicating which letter
* of the alphabet is most common in the string s
*/
int mostFrequentLetter(char message[], int messageLength) {
	/*
	* Build the histogram and get the index of most frequent alphabet
	*/
	int CurrFreq;  /*Current alphabet max freq*/
	int CurrAlphaValue;  /*Current alphabet ASCII value*/
	int MessagePosition = 0; /*Earliest value of Alphabet Value*/

	int ModeLoc;  /*Location of character Mode, alphabet value*/
	int graph[26]; /*The histogram we will use to measure number of occurances*/
	int graphLength = 26; /*number of letters in the alphabet*/
	buildHistogram(message, messageLength, graph, graphLength); /*Creating the histogram here*/
	ModeLoc = maxIndex(graph, graphLength);  /*Find the highest occurance of a certain number*/
	                                   /*The above only gets the lowest alphabet occurance*/
	CurrFreq = graph[ModeLoc];  /*Get freq value from current mode*/
	
	for (int j = 0; j < messageLength; j++){  /*find first max position*/
		if ( (message[j] == int2UpperCase(ModeLoc)) || (message[j] == int2LowerCase(ModeLoc))){
			MessagePosition = j;
			j = messageLength;
		}
	}

	for (int y = 0; y < 26; y++){  /*We need to find any abc char's that are both maxes.
								   Find most recent in message, y is used to index 
								   histogram*/
		for (int w = 0; w < messageLength; w++){ /*w indexes the message*/
			if ((graph[y] == CurrFreq) && (y != ModeLoc)){ /*if the current max is not equal to the prospective max.
														  And the frequency is equivalent, then we check for
														  how recent*/
				if ( (message[w] == int2UpperCase(y)) || ( message[w] == int2LowerCase(y) )){
					/*Check if the current message char is equal to our alphabet char*/
					if ( w < MessagePosition ){
						MessagePosition = w;  /*change out new message earliest occurance*/
						ModeLoc = y;  /*change out new alphabet early occurance*/
					}
				}
			}
		}
	}

	return ModeLoc;
}

/*
cypher is the encrypted message and int common is the common letter in the previous message
*/
void decrypt(char cypher[], int cypherLength, int common) {

	int commonCypher;  /*most common alphabet 0 - 25 in encripted message*/
	int shift;  /*The shift of the encryption*/
	commonCypher = mostFrequentLetter(cypher, cypherLength);
	shift = commonCypher - common;  /*Lets compute the shift, could be negative*/
	shift = shift * -1;  /*we have to invert it to get back to the original message*/
	encrypt(cypher, cypherLength, shift);  /*Reverse encryption*/

}