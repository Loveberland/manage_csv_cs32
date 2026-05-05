#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "choice.h"

int main() {
	const char *modes[] = {"input", "delete", "display", "exit"};
	for (int i = 0; i < 4; i++) {
		assert(i == input_mode_handler());
		fprintf(stdout, "input_mode_handler return: %s\n", modes[i]);
	}

	const char *choices_csv[] = {"old", "young", "back"};
	for (int i = 0; i < 3; i++) {
		assert(i == input_choice_csv_handler());
		fprintf(stdout, "input_choice_csv_handler return: %s\n", choices_csv[i]);
	}

	assert(strcmp("1234567890", input_id_handler()) == 0);
	fprintf(stdout, "input_id_handler return: 1234567890\n");

	const char *choice_display[] = {"all", "one", "back"};
	for (int i = 0; i < 3; i++) {
		assert(i == input_mode_display_handler());
		fprintf(stdout, "input_mode_display_handler return: %s\n", choice_display[i]);
	}

	fprintf(stdout, "If nothing happend test is success!!\n");
	return (0);
}

