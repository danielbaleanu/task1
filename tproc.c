#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

int main() {
	FILE *fh1, *fh2; // file handling 1, file handling 2

	int i;
	int j;
	int m;
	int read;

	double matches;
	double percentage;
	double complete;
	double lentxt1;
	double lentxt2;
	double len2txt1;
	double k;

	char txt1[1000000];
	char txt2[1000000];
	char ASCII[222];
	char matchtxt2[1000000];
	char repeat = 'y';
	char enter;
	char npc = (' ' - 1); // char out of working range different than null char

	// repeating the main program body until (repeat != 'y')
	while (repeat == 'y') {

		// non-array variables clearing
		m = 0;
		read = 0;
		matches = 0;
		percentage = 0;
		complete = 0;
		lentxt1 = -1;
		lentxt2 = 0;
		len2txt1 = 0;
		k = 0;
		enter = 0;

		// array variables clearing
		for (i = 0; i < 1000000; i++) {
			txt1[i] = 0;
			txt2[i] = 0;
			matchtxt2[i] = 0;
		}

		for (i = 0; i < 222; i++) {
			ASCII[i] = 0;
		}

		//importing text from text2.txt char by char to txt2 array
		fh2 = fopen("text2.txt", "r");

		printf(
				"Insert/update first and second text in the text files and press return. ");

		while (enter != '\r' && enter != '\n') {
			enter = getchar();
		}

		if (fh2 != NULL) {
			while (!feof(fh2)) {
				txt2[read] = fgetc(fh2);
				read++;
			}

			fclose(fh2);
		} else {
			printf("Error opening file. \n");
			return 0;
		}

		// making a char array containing all unique printable characters plus extended
		for (i = 0; i < 222; i++) {
			ASCII[i] = (' ' + i);
		}

		lentxt2 = strlen(txt2);

		for (j = 0; j < strlen(txt2); j++) {
			for (i = 0; i < 222; i++) {

				// if a char that is found in ASCII array corresponds to a char found in text1
				// it will be transfered to matchtxt1 array
				// the corresponding position of the ASCII array will be substituted with npc char
				if (ASCII[i] == txt2[j]) {
					matchtxt2[m] = ASCII[i];
					ASCII[i] = npc;
					m++;
				}
			}

			// if text1 has more than 10000 chars, percentage count will be initiated
			if (strlen(txt2) >= 10000) {
				while (complete <= j + 1) {
					if (fmod((complete + 1), (lentxt2 / 100)) <= 0.01) {
						printf(
								"Looking for unique characters in text 2: %lu%% \n",
								j * 100 / strlen(txt2));
					}
					complete += 0.01;
				}
			}
		}

		printf("\n");
		printf("The second text has been processed from file. \n");

		// counting the unique printable characters that were left in ASCII char
		for (i = 0; i < 95; i++) {
			if (ASCII[i] == npc) {
				k++;
			}
		}

		printf(
				"The percentage of unique printable characters that have been found in text 2 is: %f%% (%f/95) \n",
				(k * 100) / 95, k);
		printf("\n");

		// clearing some of the non-array variables for further use 
		m = 0;
		read = 0;
		complete = 0;
		lentxt1 = -1;
		k = 0;

		// matching characters from txt1 with characters from matchtxt2
		fh1 = fopen("text1.txt", "r");

		if (fh1 != NULL) {
			while (!feof(fh1)) {
				txt1[read] = fgetc(fh1);
				read++;
			}

			fclose(fh1);
		} else {
			printf("Error opening file. \n");
			return 0;
		}

		// remaking of the char array containing all unique printable characters plus ASCII extended
		for (i = 0; i < 222; i++) {
			ASCII[i] = (' ' + i);
		}

		for (j = 0; j < strlen(txt1); j++) {
			for (i = 0; i < strlen(matchtxt2); i++) {

				// if a char that is found in matchtxt2 array corresponds to a char found in text1
				// the number of matches will be incremented
				if (matchtxt2[i] == txt1[j]) {
					matches++;

					// if a char that is found in ASCII array corresponds to a char found in text1
					// that specific char will be removed from ASCII array by substituting it with npc
					// (non-printable character)
					if (ASCII[i] == txt1[j] && i < 222) {
						ASCII[i] = npc;
					}
				}

				else if (matchtxt2[i] != txt1[j]) {

					if (ASCII[i] == txt1[j] && i < 222) {
						ASCII[i] = npc;
					}
				}
			}

			len2txt1 = strlen(txt1); // will be used for float calculations in order to display the progress percentage 

			if (strlen(txt1) >= 100) // if text1 has more than 100 chars, percentage count will be initiated
					{
				while (complete <= j + 1) {
					if (fmod((complete + 1), (len2txt1 / 100)) <= 0.01) {
						printf("Checking for matches: %lu%% \n",
								j * 100 / strlen(txt1));
					}
					complete += 0.01;
				}

				if (txt1[j] != '\n') {
					lentxt1++;
				}
			}

			else if (strlen(txt1) < 100) {
				if (txt1[j] != '\n') {
					lentxt1++;
				}
			}
		}

		printf("\n");
		printf("The first text has been processed from file. \n");

		for (i = 0; i < 95; i++) {
			if (ASCII[i] == npc) // counting the unique printable characters that remained in ASCII char
					{
				k++;
			}
		}
		printf(
				"The percentage of unique printable characters that have been found in text 1 is: %f%% (%f/95) \n",
				(k * 100) / 95, k);

		// displaying the results after both texts have been processed
		printf("\n");
		printf("Matches: %f \n", matches);
		printf(
				"Number of characters found in text 1 (printable w/ extended): %f \n",
				lentxt1);
		percentage = ((matches * 100) / lentxt1);
		printf(
				"The percentage of text 1 that can be created using only characters from text 2 is: %f%% \n",
				percentage);
		printf("\n");
		printf("Do you wish to process another set of texts? (y/n) \n");
		printf("*if so, please enter 'y' for yes. \n");
		printf(
				"*otherwise, please insert 'n' for no, in order to terminate the program. \n");
		printf("\n");
		printf("Insert response: ");
		scanf(" %[^\n]%*c", &repeat);

	}

	return 0;
}
