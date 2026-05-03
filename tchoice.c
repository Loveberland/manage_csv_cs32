#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "choice.h"

int main() {
	const char *modes[] = {"input", "edit", "delete", "display", "exit"};
	for (int i = 0; i < 5; i++) {
		assert(i == input_mode_handler());
		fprintf(stdout, "input_mode_handler return: %s\n", modes[i]);
	}

	const char *choices_csv[] = {"old", "young"};
	for (int i = 0; i < 2; i++) {
		assert(i == input_choice_csv_handler());
		fprintf(stdout, "input_choice_csv_handler return: %s\n", choices_csv[i]);
	}

	assert(strcmp("1234567890", input_id_handler()) == 0);
	fprintf(stdout, "input_id_handler return: 1234567890\n");
}
