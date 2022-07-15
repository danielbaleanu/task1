#include <stdio.h>

static const char INPUT_FILE_1[] = "text1.txt";
static const char INPUT_FILE_2[] = "text2.txt";

int TextProcessingFcn(int *lentxt1, int *matches, char *matchASCII);
void ResultPrintFcn(int *matches, int *lentxt1);

int main() {
	int lentxt1 = 0, matches = 0;
	char matchASCII[256] = { 0 };

	TextProcessingFcn(&lentxt1, &matches, matchASCII);
	ResultPrintFcn(&matches, &lentxt1);

	return 0;
}

int TextProcessingFcn(int *lentxt1, int *matches, char *matchASCII) {

	int c;
	FILE *text1 = fopen(INPUT_FILE_1, "r");
	FILE *text2 = fopen(INPUT_FILE_2, "r");

	if (text1 == NULL || text2 == NULL) {
		printf("Error.\n");
		return -1;
	}
	
	while ((c = getc(text2)) != EOF) {
		matchASCII[c] = 1;
	}

	while ((c = getc(text1)) != EOF) {
		*lentxt1 += 1;
		if (matchASCII[c] == 1) {
			*matches += 1;
		}
	}

	fclose(text1);
	fclose(text2);

	return 0;
}

// fcn for displaying results
void ResultPrintFcn(int *matches, int *lentxt1) {
	// calculating the percentage of text 1 that can be created using only chars from text 2
	double percentage = (double)(*matches * 100) / *lentxt1;

	// displaying the results after both texts have been processed
	printf("Matches: %d \n", (int) *matches);
	printf("Number of characters found in text 1: %d \n", *lentxt1);

	printf( "The percentage of text 1 that can be created using only characters from"
	        " text 2 is: %.2f%% \n", percentage);
}
