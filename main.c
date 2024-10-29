#define MAIN

#include "decs.h"

void check_arguments(int argc, char *argv[]);
void read_list(FILE *fp);
void read_map(FILE *fp);
void initial_setting(void);
void initialize(void);
void SA(void);
void print(void);
void close_files(void);


int main(int argc, char *argv[])
{
	check_arguments(argc, argv);

	read_list(list_file);
	read_map(map_file);
	initial_setting();
	initialize();

	start_time = clock();
	SA();
	end_time = clock();

	print();
	close_files();

	return 0;
}
