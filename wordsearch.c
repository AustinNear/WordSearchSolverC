#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);
void searchWord(int j, int k, int gridsize, char** arr, char** list, int listPos);

int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-2) = '\0';	
	}
	
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}

void printPuzzle(char** arr, int n){
	for(int i = 0; i < n; i++){
		printf("\n");
		for(int j = 0; j < 15; j++){
			printf("%c ", *(*(arr+i)+j));
		}
	}
}

void searchPuzzle(char** arr, int n, char** list, int listSize){
	for(int i = 0; i < listSize; i++){ //to iterate through list of words
		for(int j = 0; j < 15; j++){  //iterates through y "axis" of the grid of characters
			for(int k = 0; k < 15; k++){ //iterates through x "axis" of the grid of characters
					searchWord(j, k, 15, arr, list, i); //therefore this searches from every point with each word
				}
			}

		}

}


void searchWord(int j, int k, int gridsize, char** arr, char** list, int listPos){
	int wordlength = strlen(*(list+listPos));
	if(gridsize - wordlength >= k){ //Horizontal
		int i = 0;
		while(i < wordlength && toupper(*(*(arr+j)+(k+i))) ==toupper(*(*(list+listPos)+i))){
			i++;
		}


		if(i == wordlength){
			while(i > 0){
			i--;
			*(*(arr+j)+(k+i)) = tolower(*(*(arr+j)+(k+i)));
			}
			printf("Word found: ");
			for(i = 0; i < wordlength; i++)
				printf("%c", *(*(list+listPos)+i));
			printf("\n");

		}
	}

	if(gridsize - wordlength >= j){ //Vertical
		int i = 0;

		while(i < wordlength && toupper(*(*(arr+(j+i))+k)) == toupper(*(*(list+listPos)+i))){
			i++;

		}

		if(i == wordlength){
			while(i > 0){
			i--;
			*(*(arr+(j+i))+k) = tolower(*(*(arr+(j+i))+k));
			}
			printf("Word found: ");
			for(i = 0; i < wordlength; i++){
				printf("%c", *(*(list+listPos)+i));
			}
			printf("\n");

		}
	}

	if(gridsize - wordlength >= j && gridsize - wordlength >= k){ //Diagonal, down/right
		int i = 0;
		while(i < wordlength && toupper(*(*(arr+(j+i))+(k+i))) == toupper(*(*(list+listPos)+i))){
			i++;
		}
		if(i == wordlength){
			while(i > 0){
			i--;
			*(*(arr+(j+i))+(k+i)) = tolower(*(*(arr+(j+i))+(k+i)));
			}
			printf("Word found: ");
			for(i = 0; i < wordlength; i++)
				printf("%c", *(*(list+listPos)+i));
			printf("\n");

		}
	}

	if(j - wordlength >= 0 && gridsize - wordlength >= k){ //Diagonal, up/right
		int i = 0;
		while(i < wordlength && toupper(*(*(arr+(j-i))+(k+i))) == toupper(*(*(list+listPos)+i))){
			i++;
		}
		if(i == wordlength){
			while(i > 0 ){
			i--;
			*(*(arr+(j-i))+(k+i)) = tolower(*(*(arr+(j-i))+(k+i)));
			}
			printf("Word found: ");
			for(i = 0; i < wordlength; i++)
				printf("%c", *(*(list+listPos)+i));
			printf("\n");

		}
	}


}