#include <stdio.h>
#include <time.h>
#include <locale.h>

#include "choice.h"
#include "input.h"

#define TIMESIZ 32

int main(void) {
	setlocale(LC_ALL, "");	// Set locale same as OS
	time_t raw_time; time(&raw_time);
	struct tm *time_info = localtime(&raw_time);
	char t_out[TIMESIZ]; strftime(t_out, sizeof(t_out), "%c", time_info);
	
	FILE *logs = fopen("logs.txt", "a+");
	if (logs == NULL) {
		fprintf(stderr, "%s: can't open logs.txt file\n", t_out);
		return (1);
	}
	fprintf(logs, "%s: opened program\n", t_out);

	while (1) {
		int status = 0;
		fprintf(logs, "%s: call input_mode_handler\n", t_out);
		int choice = input_mode_handler();	
		if (choice == 0) {
			status = input(logs, &t_out[0]);	
		}
		else if (choice == 1) {
			fprintf(logs, "%s: call edit\n", &t_out[0]);
			status = 0;
			fprintf(logs, "%s: edit function finished executing\n", t_out);
		}
		else if (choice == 2) {
			fprintf(logs, "%s: call delete\n", &t_out[0]);
			status = 0;	
			fprintf(logs, "%s: delete function finished executing\n", t_out);
		}
		else if (choice == 3) {
			fprintf(logs, "%s: call display\n", &t_out[0]);
			status = 0;	
			fprintf(logs, "%s: display function finished executing\n", t_out);
		}
		else if (choice == 4) {
			fprintf(logs, "%s: call exit\n", &t_out[0]);
			break;	
		}
		if (status) return (1);
	}

	fclose(logs);
	fprintf(logs, "%s: closing program\n", t_out);
	
	return (0);	
}

