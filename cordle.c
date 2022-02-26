#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FILE_LENGTH 85166

char *get_random_word() {
	FILE *w = fopen("words", "r");
	char *l;
	size_t size = 0;
	//char final[6];
	char *final = malloc(sizeof(char) * 6);
	srand(time(NULL));
	int random = (rand()%(FILE_LENGTH/2));
	int c = 0;
	while(getline(&l, &size, w) != -1) {
		if(c == random) {
			//break;
			if(strlen(l) == 6) {
				break;
			}
		} else {
			c++;
		}
	}
	strncpy(final, l, 5);
	final[6] = '\0';
	return final;
	//printf("%s", final);
	//printf("%d\n", strlen(l));
		

}


int main() {
	char *ran = get_random_word();
	printf("%s\n", ran);

}
