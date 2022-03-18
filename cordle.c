#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define FILE_LENGTH 8007    // line count

char *get_random_word() {
	FILE *w = fopen("words", "r");
	char *l;
	size_t size = 0;
	char *final = malloc(sizeof(char) * 6);
	// seed for random generator
	srand(time(0));
	int random = (rand()%(FILE_LENGTH));
	int c = 0;
	/*
	scans each line until it gets 
	to the random word
	*/
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

bool is_in_word(char *a, char h, int curr, int target) {
	for(int g = curr; g < strlen(a); g++) {
		if(a[g] == h && g == target) {
			return true;
		}

	}
	return false;

}

void show_progress(char *answer, char t[6]) {
	for(int i = 0; i < strlen(t); i++) {
		for(int j = 0; j < strlen(answer); j++) {
			if(t[i] == answer[j]) {		
				if(i == j || is_in_word(answer, t[i], j+1, i)) {
					
					// letter is in the right position, highlight green
					write(STDOUT_FILENO, "\e[1;30;22;42m", 14);	
					break;
				} else {
					// letter exists in word, highlight yellow/orange
					write(STDOUT_FILENO, "\e[1;30;22;43m", 14);
					break;
					
				}
				
			} else {
				// letter doesn't exist, highlight white
				write(STDOUT_FILENO, "\e[1;30;22;47m", 14);
			}
		}
		// prints input char-by-char
		write(STDOUT_FILENO, (void *) &t[i], 1);
		// resets all text formatting from previous letter
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
		// limits characters read at once
		scanf("%5s", guess);
		guess[6] = '\0';
		/*
		prevents input from overflowing,
		since scanf ignores characters past the 5-char limit
		*/
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
			memset(&guess, 0, sizeof(guess));

		}
		
	}
	

}
