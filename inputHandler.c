#include <stdio.h>
#include <string.h>

#include "inputHandler.h"
	
/**
  * Show what you should put
  * get input
  * remove null character
  */
personData getInputFromUser() {
	personData p;
	
	fprintf(stdout, "ID: ");
	fgets(p.id, sizeof(p.id), stdin);	
	p.id[strcspn(p.id, "\n")] = 0;

	fprintf(stdout, "First Name: ");
	fgets(p.firstName, sizeof(p.firstName), stdin);
	p.firstName[strcspn(p.firstName, "\n")] = 0;
	
	fprintf(stdout, "Last Name: ");
	fgets(p.lastName, sizeof(p.lastName), stdin);
	p.lastName[strcspn(p.lastName, "\n")] = 0;

	fprintf(stdout, "Disease: ");
	fgets(p.disease, sizeof(p.disease), stdin);
	p.disease[strcspn(p.disease, "\n")] = 0;

	fprintf(stdout, "Food allergy: ");
	fgets(p.foodAllergy, sizeof(p.foodAllergy), stdin);
	p.foodAllergy[strcspn(p.foodAllergy, "\n")] = 0;

	fprintf(stdout, "Durg allergy: ");
	fgets(p.durgAllergy, sizeof(p.durgAllergy), stdin);
	p.durgAllergy[strcspn(p.durgAllergy, "\n")] = 0;

	fprintf(stdout, "Linked ID: ");
	fgets(p.linkedId, sizeof(p.linkedId), stdin);
	p.linkedId[strcspn(p.linkedId, "\n")] = 0;

	return p;
}

void writeToFile(FILE *file, personData p) {
	fprintf(file, "%s, ", p.id);
	fprintf(file, "%s, ", p.firstName);	
	fprintf(file, "%s, ", p.lastName);	
	fprintf(file, "%s, ", p.disease);	
	fprintf(file, "%s, ", p.foodAllergy);	
	fprintf(file, "%s, ", p.durgAllergy);	
	fprintf(file, "%s\n", p.linkedId);	
}

int getInput(FILE *logs, const char *tOut) {
	char s[8];
	fprintf(stdout, "Pdata or Ndata:\n");	
	fgets(s, sizeof(s), stdin);
	
	personData p;

	if (strcmp("Pdata\n", s) == 0) {
		// Open Pdata.csv file and check error	
		FILE *pFile = fopen("Pdata.csv", "a+");
		if (pFile == NULL) {
			fprintf(logs, "%s: error can't open Pdata.csv\n", tOut);
			return (1);
		}
		fprintf(logs, "%s: opened Pdata.csv\n", tOut);
		p = getInputFromUser();
		writeToFile(pFile, p);
		fprintf(logs, "%s: writed data to Pdata.csv file\n", tOut);
		fclose(pFile);	
		fprintf(logs, "%s: closed Pdata.csv\n", tOut);
	} else if (strcmp("Ndata\n", s) == 0) {
		// Open Ndata.csv file and check error	
		FILE *nFile = fopen("Ndata.csv", "a+");		
		if (nFile == NULL) {
			fprintf(logs, "%s: error can't open Ndata.csv\n", tOut);
			return (1);	
		}
		fprintf(logs, "%s: opened Ndata.csv\n", tOut);
		p = getInputFromUser();
		writeToFile(nFile, p);
		fprintf(logs, "%s: writed data to Ndata.csv file\n", tOut);
		fclose(nFile);
		fprintf(logs, "%s: closed Pdata.csv\n", tOut);
	} else {
		fprintf(logs, "%s: wrong command \n", tOut);
		fprintf(stderr, "wrong command\n");
	}

	return 0;
}

