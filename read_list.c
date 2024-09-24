#include "decs.h"

int get_num10(FILE *fp)
{
	int number;
	char signed_flag;

	number = 0;
	signed_flag = 0;
	while((ch < '0' || '9' < ch) && ch != '-')ch = fgetc(fp);
	while(('0' <= ch && ch <= '9') || ch == '-'){
		if(ch == '-')
			signed_flag = ~signed_flag;
		else
			number = 10 * number + (long double)(ch - '0');
		ch = fgetc(fp);
	}

	if(signed_flag != 0)
		number = -number;

	return number;
}

void read_list(FILE *fp)
{
	int i, j;
	int id, id2;
	int size;

	ch = fgetc(fp);
	total_item = get_num10(fp);

	item_info = (ITEMtype *)malloc(total_item * sizeof(ITEMtype));
	if(item_info == NULL){
		fprintf(stderr,"memory allocation failed!\n");
		exit(1);
	}

	for(i = 0; i < total_item; i++){
		id = get_num10(fp);
		item_info[id].weight = get_num10(fp);
		item_info[id].freq = get_num10(fp);
		item_info[id].n_use = 0;
	}

	n_product = get_num10(fp);

	product_info = (PRODtype *)malloc(n_product * sizeof(PRODtype));
	if(product_info == NULL){
		fprintf(stderr,"memory allocation failed!\n");
		exit(1);
	}

	for(i = 0; i < n_product; i++){
		id = get_num10(fp);
		product_info[id].p_rate = get_num10(fp) / 100.0;
		product_info[id].n_item = get_num10(fp);

		size = product_info[id].n_item + 1;
		product_info[id].item_order = (ORDtype *)malloc(size * sizeof(ORDtype));
		if(product_info[id].item_order == NULL){
			fprintf(stderr,"memory allocation failed!\n");
			exit(1);
		}

		for(j = 0; j < product_info[id].n_item; j++){
			id2 = get_num10(fp);
			product_info[id].item_order[j].item_id = id2;
			item_info[id2].n_use++;
		}
		product_info[id].item_order[j].item_id = Goal;
	}
}
