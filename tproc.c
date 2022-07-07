#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *fh1, *fh2;

int i, j, n, lentxt, lentxt1, lentxt2, processing;

double matches, percentage;

char ASCII[256], matchASCII[256], c, repeat = 'y', error;

void var_init(), files(), file2(), file1(), searching(), matching(), progress(),
		error_check(), print_results(), error_print();

int main() {
	// repeating the main program body until (repeat != 'y')
	while (repeat == 'y') {
		var_init();
		files();
		error_check();
	}

	system("clear");
	return 0;
}

// fct for initialisation of array variables 
void var_init() {
	system("clear");

	for (i = 0; i < 256; i++) {
		ASCII[i] = '\0' + i;
	}

	for (i = 0; i < 256; i++) {
		matchASCII[i] = '\0';
	}
}

void files() {
	system("clear");

	error = '\0';

	file2();
	file1();
}

// fct for counting the number of characters inside of text2.txt & for calling 'searching()' fct
// executed inside of 'files()'
void file2() {

	j = 0;
	n = 0;
	lentxt2 = 0;

	fh1 = fopen("text1.txt", "r");
	fh2 = fopen("text2.txt", "r");
	if (fh1 != NULL && fh2 != NULL) {
		while (!feof(fh2)) {
			c = fgetc(fh2);
			lentxt2++;
		}

		fclose(fh1);
		fclose(fh2);

		searching();

	} else {
		error = 'e';
	}
}

// fct that looks for unique characters in text2 and stores them in 'matchASCII' array
// executed inside of file2()
void searching() {

	processing = 1;
	lentxt = lentxt2;

	fh2 = fopen("text2.txt", "r");

	while (!feof(fh2)) {
		c = fgetc(fh2);
		for (i = 0; i < 256; i++) {
			if (ASCII[i] == c && ASCII[i] != '\0') {
				matchASCII[n] = ASCII[i];
				ASCII[i] = '\0';
				n++;
			}
		}

		j++;

		if (lentxt >= 10000) {
			if (j % (lentxt / 100) == 0 && j < lentxt) {
				system("clear");
				printf("Processing (%d/2): %d%% \n", processing,
						j * 100 / lentxt);
			}
		}
	}

	fclose(fh2);
}

// fct for counting the number of characters inside of text1.txt & for calling 'matching()' fct
// executed inside of 'files()'
void file1() {

	j = 0;
	lentxt1 = -1;
	matches = -1;

	fh1 = fopen("text1.txt", "r");
	fh2 = fopen("text2.txt", "r");

	if (fh1 != NULL && fh2 != NULL) {
		while (!feof(fh1)) {
			c = fgetc(fh1);
			lentxt1++;
		}

		fclose(fh1);
		fclose(fh2);

		matching();

	} else {
		error = 'e';
	}
}

// fct that looks for matches between the unique chars found previously in text2.txt and chars of text1.txt 
// executed inside of 'files()' > 'file1()'
void matching() {

	processing += 1;
	lentxt = lentxt1;

	fh1 = fopen("text1.txt", "r");
	fh2 = fopen("text2.txt", "r");
	while (!feof(fh1)) {
		c = fgetc(fh1);
		for (i = 0; i < 256; i++) {
			if (matchASCII[i] == c && matchASCII[i] != '\0') {
				matches++;
			}
		}

		j++;

		progress();
	}

	fclose(fh1);
}

// fct for showing progress during processing
// executed inside of 'files()' > 'file2()' > 'searching()'
//								> 'file1()' > 'matching()'
void progress() {
	if (lentxt >= 10000) {
		if (j % (lentxt / 100) == 0 && j < lentxt) {
			system("clear");
			printf("Processing (%d/2): %d%% \n", processing, j * 100 / lentxt);
		}
	}
}

// fct for error check
void error_check() {
	if (error == '\0') {

		print_results();

	} else if (error == 'e') {

		error_print();
	}
}

// fct for displaying results
void print_results() {
	system("clear");

	// calculating the percentage of text 1 that can be created using only chars from text 2
	percentage = (matches * 100) / lentxt1;

	// displaying the results after both texts have been processed
	printf("Matches: %d \n", (int) matches);
	printf("Number of characters found in text 1: %d \n", lentxt1);

	if (((int) (percentage * 100)) % 100 == 0) {
		printf(
				"The percentage of text 1 that can be created using only characters from text 2 is: %d%% \n",
				(int) percentage);
	} else {
		printf(
				"The percentage of text 1 that can be created using only characters from text 2 is: %f%% \n",
				percentage);
	}
	printf("\n");
	printf("Do you wish to process another set of texts? (y/n) \n");
	printf("*if so, please enter 'y' for yes \n");
	printf(
			"*otherwise, please insert 'n' for no, in order to terminate the program \n");
	printf("\n");
	printf("Insert response: ");
	scanf(" %[^\n]%*c", &repeat);
}

// fct for guiding user in case of error
void error_print() {
	system("clear");

	printf("Error opening files. \nDo you wish to try again? (y/n) \n");
	printf(
			"*if you have checked the files, please enter 'y', in order to try again \n");
	printf(
			"*otherwise, please insert 'n' for no, in order to terminate the program \n");
	printf("\n");
	printf("Insert response: ");
	scanf(" %[^\n]%*c", &repeat);
}
