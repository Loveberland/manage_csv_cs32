#include <stdio.h>

#include "choice.h"
#include "input.h"
#include "time_manager.h"

int main(void) {
	char t_out[TIMESIZE];
	get_current_time(t_out, sizeof(t_out));

	FILE *logs = fopen("logs.txt", "a+");
	if (logs == NULL) {
		fprintf(stderr, "%s: can't open logs.txt file\n", t_out);
		return (1);
	}

	while (1) {
		int status = 0;
		int choice = input_mode_handler();	
		if (choice == 0) {
			status = input(logs);	
		}
		else if (choice == 1) {
			status = 0;
		}
		else if (choice == 2) {
			status = 0;	
		}
		else if (choice == 3) {
			status = 0;	
		}
		else if (choice == 4) {
			break;	
		}
		if (status) return (1);
	}

	fclose(logs);
	
	return (0);	
}

