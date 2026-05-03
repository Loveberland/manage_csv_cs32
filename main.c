#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>

#include "inputHandler.h"

#define SIZ 1024
#define TSIZ 256

int main(void) {
	setlocale(LC_ALL, "");	// Set locale same as OS

	time_t  rawTime; time(&rawTime);	// Get current raw time
	struct tm *timeInfo = localtime(&rawTime);	// Convert raw time to local time
	char tOut[TSIZ]; strftime(tOut, sizeof(tOut), "%c", timeInfo);	// Auto format

	// Open logs.txt file and check error	
	FILE *logs = fopen("logs.txt", "a+");
	if (logs == NULL) {
		fprintf(stderr, "%s: error can't open logs.txt\n", tOut);
		return (1);
	}
	fprintf(logs, "%s: opend logs.txt\n", tOut);

	int tmp = getInput(logs, tOut);

	return (0);
}

