#include <stdio.h>
#include <string.h>

#include "choice.h"

int display_all() {
	char line[4096], n_line[4096], p_title[4096], n_title[4096];
	char p_title_copy[4096], n_title_copy[4096], p_id_copy[16];
	char *saveptr1, *saveptr2;

	FILE *p_file = fopen("p_data.csv", "r");
	if (p_file == NULL) {
		fprintf(stderr, "can't open p_data.csv\n");
		return (1);
	}

	FILE *n_file = fopen("n_data.csv", "r");
	if (n_file == NULL) {
		fprintf(stderr, "can't open n_data.csv\n");
		fclose(p_file);
		return (1);
	}

	fgets(p_title, sizeof(p_title), p_file);
	p_title[strcspn(p_title, "\n")] = '\0';
	fgets(n_title, sizeof(n_title), n_file);
	n_title[strcspn(n_title, "\n")] = '\0';

	int is_p_print = 0, is_n_print = 0;

	while (fgets(line, sizeof(line), p_file)) {
		is_p_print = is_n_print = 0;
		line[strcspn(line, "\n")] = '\0';
		char *token = strtok_r(line, ",", &saveptr1);
		if (token == NULL) continue;
		
		strcpy(p_title_copy, p_title);
		char *p_token = strtok_r(p_title_copy, ",", &saveptr2);
		if (!is_p_print) {
			int tmp = 0;
			while (p_token != NULL) {
				if (tmp) fprintf(stdout, ", ");
				fprintf(stdout, "%s", p_token);
				tmp = 1;
				p_token = strtok_r(NULL, ",", &saveptr2);
			}
			is_p_print = 1;
		}
		putchar('\n');

		strcpy(p_id_copy, token);
		int tmp = 0;
		while (token != NULL) {
			if (tmp) fprintf(stdout, ", ");
			fprintf(stdout, "%s", token);
			tmp = 1;
			token = strtok_r(NULL, ",", &saveptr1);
		}
		putchar('\t');	

		fseek(n_file, 0, SEEK_SET);
		fgets(n_line, sizeof(n_line), n_file);
		while (fgets(n_line, sizeof(n_line), n_file)) {
			n_line[strcspn(n_line, "\n")] = '\0';
			char *link = strrchr(n_line, ',');

			if (link == NULL) continue;
			link++;
			while (*link == ' ') link++;
			char *cr = strchr(link, '\r');
			if (cr != NULL) *cr = '\0';
			if (strcmp(p_id_copy, link) != 0) continue;
			if (!is_n_print) {
				strcpy(n_title_copy, n_title);
				char *n_token = strtok_r(n_title_copy, ",", &saveptr2);
				fprintf(stdout, "\n\t");
				int tmp0 = 0;
				while (n_token != NULL) {
					if (tmp0) fprintf(stdout, ", ");
					fprintf(stdout, "%s", n_token);
					tmp0 = 1;
					n_token = strtok_r(NULL, ",", &saveptr2);
				}
				is_n_print = 1;
				putchar('\n');
			}
			putchar('\t');
			char *n = strtok_r(n_line, ",", &saveptr2);
			int tmp0 = 0;
			while (n != NULL) {
				if (tmp0) fprintf(stdout, ", ");
				fprintf(stdout, "%s", n);
				tmp0 = 1;
				n = strtok_r(NULL, ",", &saveptr2);
			}
			putchar('\n');
		}	
			fprintf(stdout, "\n\n\n\n\n");
	}

	fclose(p_file);
	fclose(n_file);

	return (0);
}

int display_one() {
	char *id = input_id_handler();
	if (id[1] == '8') {
		char line[4096], n_line[4096], p_title[4096], n_title[4096];
		char p_title_copy[4096], n_title_copy[4096];
		char *saveptr1, *saveptr2;
	
		FILE *p_file = fopen("p_data.csv", "r");
		if (p_file == NULL) {
			fprintf(stderr, "can't open p_data.csv\n");
			return (1);
		}

		FILE *n_file = fopen("n_data.csv", "r");
		if (n_file == NULL) {
			fprintf(stderr, "n_data.csv");
			fclose(p_file);
			return (1);
		}
		
		fgets(p_title, sizeof(p_title), p_file);
		p_title[strcspn(p_title, "\n")] = '\0';
		fgets(n_title, sizeof(n_title), n_file);
		n_title[strcspn(n_title, "\n")] = '\0';

		int is_print = 0;

		while (fgets(line, sizeof(line), p_file)) {	// read file line in p_file.csv
			line[strcspn(line, "\n")] = '\0';
			char *token = strtok_r(line, ",", &saveptr1);
			if (token == NULL || strcmp(token, id) != 0) continue;

			strcpy(p_title_copy, p_title);
			char *p_token = strtok_r(p_title_copy, ",", &saveptr2);
			int tmp = 0;
			while (p_token != NULL) {
				if (tmp) fprintf(stdout, ", ");
				fprintf(stdout, "%s", p_token);
				tmp = 1;
				p_token = strtok_r(NULL, ",", &saveptr2);
			}
			putchar('\n');

			fprintf(stdout, "%s, ", token);

			// print p_data that match id
			token = strtok_r(NULL, ",", &saveptr1);
			int tmp0 = 0;
			while (token != NULL) {
				if (tmp0) fprintf(stdout, ", ");
				fprintf(stdout, "%s", token);
				tmp0 = 1;
				token = strtok_r(NULL, ",", &saveptr1);
			}

			fseek(n_file, 0, SEEK_SET);
			fgets(n_line, sizeof(n_line), n_file);
			while (fgets(n_line, sizeof(n_line), n_file)) {	// Find n
				n_line[strcspn(n_line, "\n")] = '\0';
				char *link = strrchr(n_line, ',');	// find last comma (find linked id)
				if (link == NULL) continue;
				link++;
				while (*link == ' ') link++;
				char *cr = strchr(link, '\r');
				if (cr != NULL) *cr = '\0';	
				if (strcmp(link, id) != 0) continue;
				if (!is_print) {
					strcpy(n_title_copy, n_title);
					char *n_token = strtok_r(n_title_copy, ",", &saveptr2);
					fprintf(stdout, "\n\t");
					int tmp1 = 0;
					while (n_token != NULL) {
						if (tmp1) fprintf(stdout, ", ");
						fprintf(stdout, "%s", n_token);
						n_token = strtok_r(NULL, ",", &saveptr2);		
					}
					is_print = 1;
					putchar('\n');
				}
				fprintf(stdout, "\t");
				char *n = strtok_r(n_line, ",", &saveptr2);
				int tmp1 = 0;
				while (n != NULL) {	// print
					if (tmp1) fprintf(stdout, ", ");
					fprintf(stdout, "%s", n);
					tmp1 = 1;
					n = strtok_r(NULL, ",", &saveptr2);
				}
				putchar('\n');
			}
			putchar('\n');
		}	
		fclose(p_file);
		fclose(n_file);	
	} else if (id[1] == '9') {				
		FILE *n_file = fopen("n_data.csv", "r");
		if (n_file == NULL) {
			fprintf(stderr, "n_data.csv");
			return (1);
		}

		char line[4096], title[4096], title_copy[4096];
		char *saveptr1, *saveptr2;

		fgets(title, sizeof(title), n_file);
		title[strcspn(title, "\n")] = '\0';

		while (fgets(line, sizeof(line), n_file)) {
			line[strcspn(line, "\n")] = '\0';
			char *token = strtok_r(line, ",", &saveptr1);
			if (token == NULL || strcmp(token, id) != 0) continue;
			strcpy(title_copy, title);
			char *tmp = strtok_r(title, ",", &saveptr2);
			int tmp0 = 0;
			while (tmp != NULL) {
				if (tmp0) fprintf(stdout, ", ");
				fprintf(stdout, "%s", tmp);
				tmp0 = 1;
				tmp = strtok_r(NULL, ",", &saveptr2);
			}
			putchar('\n');
			int tmp1 = 0;
			while (token != NULL) {
				if (tmp1) fprintf(stdout, ", ");
				fprintf(stdout, "%s", token);
				tmp1 = 1;
				token = strtok_r(NULL, ",", &saveptr1);
			}
			putchar('\n');
		}
			
	} else {
		fprintf(stderr, "ID not found\n");
		return (1);
	}
	return (0);	
}

int init_display() {
	int status = 0;
	int c = input_mode_display_handler();
	if (c == 0) {
		status = display_all();	
	} else if (c == 1) {
		status = display_one();
	} else if (c == 2) {
		return (0);
	} else return (1);
	return status;
}

