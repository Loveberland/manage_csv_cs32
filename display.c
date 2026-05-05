#include <stdio.h>

#include "choice.h"
#include "time_manager.h"

int search_display(int mode, const char *id) {
	if (!mode) {	// P

	} else {	// N

	{
}

int display_all(FILE *logs) {
	return (0);
}

int display_one(FILE *logs) {
	char *id = input_id_handler();
	if (id[1] == '8') {
		search_display(0, &id[0]);	
	} else if (id[1] == '9') {		
		search_display(1, &id[0]);	
	} else {
		fprintf(stderr, "ID not found\n");
		return (1);
	}
	return (0);	
}

int display(FILE *logs) {

}
