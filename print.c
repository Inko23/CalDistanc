#include "decs.h"

void print(void)
{
	int i, j;
	double cpu_time;
	int all_distance = 0; //総距離
	double expected_value = 0; //期待値

	for(i = 0; i < total_item; i++){
		printf("%d, %d, %d\t", i, item_info[i].weight, item_info[i].freq);
		printf("used product: ");
		for(j = 0; j < item_info[i].n_use; j++)
			printf("%d, ", item_info[i].used_product[j]);
		printf("\n");
	}
	printf("\n");

	for(i = 0; i < n_product; i++){
		printf("%d, %lf%%: ", i, product_info[i].p_rate * 100);

		for(j = 0; j < product_info[i].n_item; j++)
			printf("%d -> ", product_info[i].item_order[j].item_id);
		printf("\n");
	}
	printf("\n");

	printf("start: (%d, %d)\n", start_point.x, start_point.y);
	printf("goal: (%d, %d)\n", goal_point.x, goal_point.y);
	printf("entrance: (%d, %d)\n", delivery_entrance.x, delivery_entrance.y);
	for(j = 0; j < floor_height; j++){
		for(i = 0; i < floor_width; i++){
			if(map[i][j].floor_kind == Aisle){
				if(0 < j && j < floor_height - 1)
					printf(" | ");
				else
					printf("---");
			}
			else{
				if(map[i][j].n_empty == n_box)
					printf("   ");
				else
					printf(" %d ", map[i][j].box[0]);
			}
		}
		printf("\n");
	}
	printf("\n");

	for(i = 0; i < n_product; i++){
		printf("product %d:\n", i);
		printf(" total distance: %d\n", product_info[i].distance);
		printf(" from start to");
		for(j = 0; j < product_info[i].n_item; j++){
			printf(" item %d: ", product_info[i].item_order[j].item_id);
			printf("%d\n", product_info[i].item_order[j].dist_from_prev);
			printf(" from item %d to", product_info[i].item_order[j].item_id);
		}
		printf(" goal: ");
		printf("%d\n", product_info[i].item_order[j].dist_from_prev);
		printf("\n");

		all_distance += product_info[i].distance;
		expected_value += product_info[i].distance * product_info[i].p_rate; 
	}

	for(i = 0;i <total_item; i++){
		printf("replenish[%d]: %d",i , item_info[i].dist_from_entrance); //補充口からの距離
		printf("\n");
	}
	printf("all replenish: %d\n", all_replenish); //補充口からの距離
	printf("replenish expected value: %lf\n", expected_replenish_value); //期待値

	printf("all distance: %d\n", all_distance); //総距離
	printf("expected value: %lf\n", expected_value); //期待値


	cpu_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
	fprintf(stdout,"time: %lf sec\n",cpu_time);
}
