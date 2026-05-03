#include <stdio.h>

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

typedef struct {
	char id[16];
	char firstName[32];
	char lastName[32];
	char disease[128];
	char foodAllergy[128];
	char durgAllergy[128];
	char linkedId[16];
} personData;

int getInput(FILE *logs, const char *tOut);

#endif

