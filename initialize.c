#include "decs.h"

void allocate(void)
{
	char fail_flag;
	int i;
	int size;

	fail_flag = 0;
	size = floor_width * floor_height;

	cur_front = (Coordinatetype *)malloc(size * sizeof(Coordinatetype));
	if(cur_front == NULL)fail_flag = 1;

	next_front = (Coordinatetype *)malloc(size * sizeof(Coordinatetype));
	if(next_front == NULL)fail_flag = 1;

	for(i = 0; i < total_item; i++){
		size = item_info[i].n_use;
		item_info[i].used_product = (int *)malloc(size * sizeof(int));
		if(item_info[i].used_product == NULL)fail_flag = 1;
	}

	if(fail_flag == 1){
		fprintf(stderr,"memory allocate failed!\n");
		exit(1);
	}
}

void init_variable(void)
{
	time_count = 0;
	all_distance = 0; //総距離
	expected_value = 0.0; //期待値
	all_replenish = 0; //補充口からの総距離
	expected_replenish_value = 0.0; //補充口からの距離の期待値
	weight_priority = 0.0; //重さによる優先度
	cost = 0.0; //コスト関数
}

void init_table(void)
{
	int i, j, k;
	int id;

	for(i = 0; i < total_item; i++)
		item_info[i].n_use = 0;

	for(i = 0; i < n_product; i++){
		for(j = 0; j < product_info[i].n_item; j++){
			id = product_info[i].item_order[j].item_id;
			k = item_info[id].n_use;
			item_info[id].used_product[k] = i;
			item_info[id].n_use++;
		}
	}
}

void initialize(void)
{
	allocate();
	init_variable();
	init_table();
}
