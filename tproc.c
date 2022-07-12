#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

FILE *text1, *text2;

void ArrayInitFcn(int *i, char *ASCII), ResultPrintFcn(double *matches,
		double *percentage, int *lentxt1);
int TextProcessingFcn(int *i, int *n, int *lentxt1, double *matches, char *c,
		char *ASCII, char *matchASCII);

int main() {
	int i, n = 0, lentxt1 = -1;
	double matches = -1, percentage;
	char c, ASCII[256] = { 0 }, matchASCII[256] = { 0 };

	ArrayInitFcn(&i, ASCII);
	TextProcessingFcn(&i, &n, &lentxt1, &matches, &c, ASCII, matchASCII);
	ResultPrintFcn(&matches, &percentage, &lentxt1);

	return 0;
}

void ArrayInitFcn(int *i, char *ASCII) {
	for (*i = 0; *i < 256; *i += 1) {
		ASCII[*i] = CHAR_MIN + *i;
	}
}

int TextProcessingFcn(int *i, int *n, int *lentxt1, double *matches, char *c,
		char *ASCII, char *matchASCII) {

	text1 = fopen("text1.txt", "r");
	text2 = fopen("text2.txt", "r");

	if (text1 != NULL || text2 != NULL) {
		while (!feof(text2)) {
			*c = (char) getc(text2);
			for (*i = 0; *i < 256; *i += 1) {
				if (ASCII[*i] == *c && ASCII[*i] != 0) {
					matchASCII[*n] = ASCII[*i];
					ASCII[*i] = 0;
					*n += 1;
				}
			}
		}

		while (!feof(text1)) {
			*c = (char) getc(text1);
			*lentxt1 += 1;
			for (*i = 0; *i < 256; *i += 1) {
				if (matchASCII[*i] == *c && matchASCII[*i] != 0) {
					*matches += 1;
				}
			}
		}

		fclose(text1);
		fclose(text2);

		return 0;
	} else {
		printf("Error.\n");
		return 0;
	}
}

// fcn for displaying results
void ResultPrintFcn(double *matches, double *percentage, int *lentxt1) {
	// calculating the percentage of text 1 that can be created using only chars from text 2
	*percentage = (*matches * 100) / *lentxt1;

	// displaying the results after both texts have been processed
	printf("Matches: %d \n", (int) *matches);
	printf("Number of characters found in text 1: %d \n", *lentxt1);

	if (((int) (*percentage * 100)) % 100 == 0) {
		printf(
				"The percentage of text 1 that can be created using only characters from text 2 is: %d%% \n",
				(int) *percentage);
	} else {
		printf(
				"The percentage of text 1 that can be created using only characters from text 2 is: %.2f%% \n",
				*percentage);
	}
}
