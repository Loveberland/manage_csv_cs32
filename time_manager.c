#include <time.h>
#include <locale.h>

#include "time_manager.h"

void get_current_time(char *buffer, size_t size) {
	setlocale(LC_ALL, "");	// Change locale same as OS
	time_t raw_time;
	time(&raw_time);
	struct tm *time_info = localtime(&raw_time);
	strftime(buffer, size, "%c", time_info);
}
