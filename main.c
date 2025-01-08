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
double cal_all_dist(void);


int main(int argc, char *argv[])
{
	double prev_cost = 0.0;
	double final_cost = 0.0;

	check_arguments(argc, argv);

	read_list(list_file);
	read_map(map_file);
	initial_setting();
	initialize();
	prev_cost = cal_all_dist();
	print();

	initialize();
	start_time = clock();
	SA();
	end_time = clock();

	final_cost = cost;

	print();
	close_files();

	printf("コストの差 : %lf\n", prev_cost - final_cost);
	
	printf("受理回数: %d\n", accept_count); //受理回数

	printf("却下回数: %d\n", not_accept); //却下回数

	printf("試行回数: %d\n", count); //試行回数

	printf("内部試行回数: %d\n", inner_count); //試行回数

	return 0;
}
