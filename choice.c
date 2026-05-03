#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <termios.h>
#include <unistd.h>

struct termios orig_termios;

void disable_raw_mode() {
	tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void enable_raw_mode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disable_raw_mode);

	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

int input_mode_handler() {
	enable_raw_mode();

	int choice = 0;
	const char *options_mode[] = {"input", "edit", "delete", "display", "exit"};
	char c;

	// Show option and get input
	while (1) {
		fprintf(stdout, "\033[H\033[J");	// ANSI escape code to clear terminal and move cursor to top
		// Show all options and highlight selected option
		for (int i = 0; i < 5; i++) {
			if (i == choice) fprintf(stdout, " -> \033[1;32m%s\033[0m \n", options_mode[i]);	// Highlight selected option
			else fprintf(stdout, "    %s \n", options_mode[i]);
		}
		
		read(STDIN_FILENO, &c, 1);	// Read 1 byte and keep into c

		// If c is arrow
		if (c == '\033') {
			char seq[3];	// Arrow character use 3 byte
			// If input is not arrow
			if (read(STDIN_FILENO, &seq[0], 1) == 0) continue;
			if (read(STDIN_FILENO, &seq[1], 1) == 0) continue;

			if (seq[0] == '[') {
				if (seq[1] == 'A') {	// Up arrow
					if (choice > 0) choice--;
				} else if (seq[1] == 'B') {	// Down arrow
					if (choice < 4) choice++;
				}
			}
		} else if (c == '\n') break;	// If enter key is pressed
	}

	fprintf(stdout, "\033[H\033[J");	// Clear terminal;

	disable_raw_mode();

	return choice;
}

int input_choice_csv_handler() {
	enable_raw_mode();

	int choice = 0;
	const char *options_csv[] = {"old", "young", "back"};
	char c;

	while (1) {
		fprintf(stdout, "\033[H\033[J");	// ANSI escape code to clear terminal and move cursor to top
		// Show all options and highlight selected option
		for (int i = 0; i < 3; i++) {
			if (i == choice) fprintf(stdout, " -> \033[1;32m%s\033[0m \n", options_csv[i]);	// Highlight selected option
			else fprintf(stdout, "    %s \n", options_csv[i]);
		}
		
		read(STDIN_FILENO, &c, 1);	// Read 1 byte and keep into c

		// If c is arrow
		if (c == '\033') {
			char seq[3];	// Arrow character use 3 byte
			// If input is not arrow
			if (read(STDIN_FILENO, &seq[0], 1) == 0) continue;
			if (read(STDIN_FILENO, &seq[1], 1) == 0) continue;

			if (seq[0] == '[') {
				if (seq[1] == 'A') {	// Up arrow
					if (choice > 0) choice--;
				} else if (seq[1] == 'B') {	// Down arrow
					if (choice < 2) choice++;
				}
			}
		} else if (c == '\n') break;	// If enter key is pressed
	}

	fprintf(stdout, "\033[H\033[J");

	disable_raw_mode();
	
	return choice;
}

char *input_id_handler() {
	static char s[16];
	fprintf(stdout, "ID: ");
	fgets(s, sizeof(s), stdin);
	s[strcspn(s, "\n")] = '\0';	

	return s;
}

