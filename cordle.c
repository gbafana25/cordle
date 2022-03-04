#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define FILE_LENGTH 85166

char *get_random_word() {
	FILE *w = fopen("words", "r");
	char *l;
	size_t size = 0;
	char *final = malloc(sizeof(char) * 6);
	srand(time(0));
	int random = (rand()%(FILE_LENGTH));
	int c = 0;
	while(getline(&l, &size, w) != -1) {
		if(c == random) {
			// avoid proper nouns/names
			if(strlen(l) == 6 && l[0] > 'Z') {
				break;
			}
		} else {
			c++;
		}
	}
	strncpy(final, l, 5);
	final[6] = '\0';
	return final;
		

}

void show_progress(char *answer, char t[5]) {

	for(int i = 0; i < strlen(t); i++) {
		for(int j = 0; j < strlen(answer); j++) {
			if(t[i] == answer[j]) {
				if(i == j) {
					write(STDOUT_FILENO, "\e[1;30;2;42m", 13);
					break;
				} else {
					write(STDOUT_FILENO, "\e[1;30;2;43m", 13);
					break;
				}
			} else {
				write(STDOUT_FILENO, "\e[1;30;2;47m", 13);
				//break;
			}
		}
		write(STDOUT_FILENO, (void *) &t[i], 1);
		write(STDOUT_FILENO, "\e[0m", 5);
		
	}
	printf("\n");

}


int main() {
	char *ran = get_random_word();
	char guess[6];
	int turn = 1;
	printf("\e[1;33mCordle - wordle in C\e[0m\n");

	// input loop
	while(true) {
		// quit if out of turns
		if(turn > 6) {
			printf("Out of turns, word was %s\n", ran);
			break;
		}
		printf("Guess a 5-letter word (Turn %d/6): ", turn);
		// `5s` prevents buffer overflows
		scanf("%5s", guess);	
		guess[6] = '\0';
		if(strlen(guess) != 5) {
			printf("Invalid Length! Try again\n");
			memset(&guess, 0, sizeof(guess));
		} else {
	
			int result = strncmp(guess, ran, 5);
			if(result == 0) {
				printf("You win\n");
				break;
			} else {
				show_progress(ran, guess);
				turn++;
			}

		}
		
	}
	

}
