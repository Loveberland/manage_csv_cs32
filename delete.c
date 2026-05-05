#include <stdio.h>
#include <string.h>

#include "delete.h"
#include "choice.h"
#include "time_manager.h"

FILE *tmp;
int init_tmp() {
	tmp = fopen("tmp.csv", "w");
	if (tmp == NULL) {
		fprintf(stderr, "can't create temp.csv\n");
		return (1);
	}
	return(0);
}

int delete(FILE *logs, const char *filename) {
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		fprintf(stderr, "can't open %s\n", filename);
		return (1);
	}

	char *id = input_id_handler();
	char t_out[TIMESIZE];
	char line[4096], line_copy[4096];
	int delete_count = 0;

	while (fgets(line, sizeof(line), file)) {
		strcpy(line_copy, line);
		char *token = strtok(line_copy, ",");
		if (token != NULL && strcmp(token, id) == 0) {
			get_current_time(t_out, sizeof(t_out));
			fprintf(logs, "%s: delete data id[%s]\n", t_out, id);
			delete_count++;
			continue;
		}
		fputs(line, tmp);
	}

	fclose(tmp);
	fclose(file);

	if (delete_count == 0) {
		fprintf(logs, "id[%s] not found, no delete\n", id);
		remove("tmp.csv");
		return (0);
	}

	remove(filename);
	rename("tmp.csv", filename);

	return (0);
}

int init_delete(FILE *logs) {
	int status = 0;
	status = init_tmp();
	if (status) return (status);
	int choice = input_choice_csv_handler();
	if (choice == 0) {
		status = delete(logs, "p_data.csv");
	} else if (choice == 1) {
		status = delete(logs, "n_data.csv");
	} else if (choice == 2) {
		fclose(tmp);
		remove("tmp.csv");
	} else {
		fclose(tmp);
		remove("tmp.csv");
		status = 1;
	}

	return status;
}

