#include "decs.h"

int maze(Coordinatetype from, Coordinatetype to);

double cal_all_dist(void)
{
	int i, j;
	int item_id, prev_id;

	all_replenish = 0.0;
	expected_replenish_value = 0.0;
	all_distance = 0.0;
	expected_value = 0.0;
	cost = 0.0;

	for(i = 0; i < n_product; i++){
		item_id = product_info[i].item_order[0].item_id;
		product_info[i].item_order[0].dist_from_prev = maze(start_point, item_info[item_id].position);
		product_info[i].distance = product_info[i].item_order[0].dist_from_prev;
		prev_id = item_id;

		for(j = 1; j < product_info[i].n_item; j++){
			item_id = product_info[i].item_order[j].item_id;
			product_info[i].item_order[j].dist_from_prev = maze(item_info[prev_id].position, item_info[item_id].position);
			product_info[i].distance += product_info[i].item_order[j].dist_from_prev;
			prev_id = item_id;
		}

		product_info[i].item_order[j].dist_from_prev = maze(item_info[prev_id].position, goal_point);
		product_info[i].distance += product_info[i].item_order[j].dist_from_prev;

		all_distance += product_info[i].distance; //総距離
		expected_value += product_info[i].distance * product_info[i].p_rate; //期待値
	}

	for(i = 0; i < total_item; i++){
		item_info[i].dist_from_entrance = maze(delivery_entrance, item_info[i].position);
		all_replenish += item_info[i].dist_from_entrance;
		expected_replenish_value += item_info[i].dist_from_entrance * (double)item_info[i].freq/100; 
	}

	for(i = 0; i < total_item; i++){
        weight_priority += (item_info[i].weight * para[item_info[i].box_level]);
    }

	cost = all_distance + CostParamR * expected_replenish_value + CostParamW * weight_priority;

	return cost;
}
