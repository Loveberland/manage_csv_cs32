#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "time_manager.h"

int main() {
	char t_out[TIMESIZE];
	int count = 1;
	while (count <= 10) {
		get_current_time(t_out, sizeof(t_out));
		fprintf(stdout, "%s: %d seconds\n", t_out, count++);
		sleep(1);
	}

	fprintf(stdout, "test time success\n");

	return (0);
}

