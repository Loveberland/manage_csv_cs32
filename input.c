#include <stdio.h>
#include <string.h>

#include "input.h"
#include "choice.h"

int input_p(FILE *logs, const char *t_out) {
	fprintf(logs, "%s: call input_p\n", t_out);

	char id[16], first_name[256], last_name[256], role[256], disease[512], durk_allergy[512], food[512], other[1024];

	FILE *p_file = fopen("p_data.csv", "a+");
	if (p_file == NULL) {
		fprintf(logs, "%s: can't open p_data.csv\n", t_out);
		return (1);
	}

	fprintf(stdout, "ID: ");
	fgets(id, sizeof(id), stdin);
	id[strcspn(id, "\n")] = '\0';

	fprintf(stdout, "First name: ");
	fgets(first_name, sizeof(first_name), stdin);
	first_name[strcspn(first_name, "\n")] = '\0';

	fprintf(stdout, "Last name: ");
	fgets(last_name, sizeof(last_name), stdin);
	last_name[strcspn(last_name, "\n")] = '\0';

	fprintf(stdout, "Role: ");
	fgets(role, sizeof(role), stdin);
	role[strcspn(role, "\n")] = '\0';

	fprintf(stdout, "Disease: ");
	fgets(disease, sizeof(disease), stdin);
	disease[strcspn(disease, "\n")] = '\0';

	fprintf(stdout, "Durk allergy: ");
	fgets(durk_allergy, sizeof(durk_allergy), stdin);
	durk_allergy[strcspn(durk_allergy, "\n")] = '\0';

	fprintf(stdout, "Food: ");
	fgets(food, sizeof(food), stdin);
	food[strcspn(food, "\n")] = '\0';

	fprintf(stdout, "Other: ");
	fgets(other, sizeof(other), stdin);
	other[strcspn(other, "\n")] = '\0';

	fprintf(p_file, "%s, ", id);
	fprintf(p_file, "%s, ", first_name);
	fprintf(p_file, "%s, ", last_name);
	fprintf(p_file, "%s, ", role);
	fprintf(p_file, "%s, ", disease);
	fprintf(p_file, "%s, ", durk_allergy);
	fprintf(p_file, "%s, ", food);
	fprintf(p_file, "%s\n", other);
	fprintf(logs, "%s: put %s, %s, %s, %s, %s, %s, %s, %s to p_data.csv\n", t_out, id, first_name, last_name, role, disease, durk_allergy, food, other);

	fprintf(logs, "%s: input_p function finished executing\n", t_out);

	return (0);
}

int input_n(FILE *logs, const char *t_out) {
	fprintf(logs, "%s: call input_n\n", t_out);

	char id[16], first_name[256], last_name[256], disease[512], durk_allergy[512], food[512], other[1024], linked_id[16];

	FILE *n_file = fopen("n_data.csv", "a+");
	if (n_file == NULL) {
		fprintf(logs, "%s: can't open n_data.csv\n", t_out);
		return (1);
	}

	fprintf(stdout, "ID: ");
	fgets(id, sizeof(id), stdin);
	id[strcspn(id, "\n")] = '\0';

	fprintf(stdout, "First name: ");
	fgets(first_name, sizeof(first_name), stdin);
	first_name[strcspn(first_name, "\n")] = '\0';

	fprintf(stdout, "Last name: ");
	fgets(last_name, sizeof(last_name), stdin);
	last_name[strcspn(last_name, "\n")] = '\0';

	fprintf(stdout, "Disease: ");
	fgets(disease, sizeof(disease), stdin);
	disease[strcspn(disease, "\n")] = '\0';

	fprintf(stdout, "Durk allergy: ");
	fgets(durk_allergy, sizeof(durk_allergy), stdin);
	durk_allergy[strcspn(durk_allergy, "\n")] = '\0';

	fprintf(stdout, "Food: ");
	fgets(food, sizeof(food), stdin);
	food[strcspn(food, "\n")] = '\0';

	fprintf(stdout, "Other: ");
	fgets(other, sizeof(other), stdin);
	other[strcspn(other, "\n")] = '\0';

	fprintf(stdout, "Linked ID: ");
	fgets(linked_id, sizeof(linked_id), stdin);
	linked_id[strcspn(linked_id, "\n")] = '\0';

	fprintf(n_file, "%s, ", id);
	fprintf(n_file, "%s, ", first_name);
	fprintf(n_file, "%s, ", last_name);
	fprintf(n_file, "%s, ", disease);
	fprintf(n_file, "%s, ", durk_allergy);
	fprintf(n_file, "%s, ", food);
	fprintf(n_file, "%s, ", other);
	fprintf(n_file, "%s\n", linked_id);
	fprintf(logs, "%s: put %s, %s, %s, %s, %s, %s, %s, %s to p_data.csv\n", t_out, id, first_name, last_name, disease, durk_allergy, food, other, linked_id);

	fprintf(logs, "%s: input_n function finished executing\n", t_out);

	return (0);
}

int input(FILE *logs, const char *t_out) {
	fprintf(logs, "%s: call input\n", t_out);

	while (1) {
		int status = 0;
		fprintf(logs, "%s: call input_choice_csv_handler\n", t_out);
		int choice = input_choice_csv_handler();
		if (choice == 0) {			
			status = input_p(logs, &t_out[0]);	
		} else if (choice == 1) {
			fprintf(logs, "%s: call input_n\n", t_out);
			status = input_n(logs, &t_out[0]);	
			fprintf(logs, "%s: input_n function finished executing\n", t_out);
		} else if (choice == 2) {
			fprintf(logs, "%s: call back\n", t_out);
			break;
		}
		if (status) return (1);
	}

	fprintf(logs, "%s: input function finished executing\n", t_out);

	return 0;
}

