#include "decs.h"

int get_num10(FILE *fp);

void get_init_posi(FILE *fp)
{
	int i;
	Coordinatetype p;
	int l;

	ch = ' ';

	for(i = 0; i < total_item; i++){
		while(1){
			fprintf(stderr,"input position of item %d:\n", i);
			fprintf(stderr,"  x = ");
			p.x = get_num10(fp);
			fprintf(stderr,"  y = ");
			p.y = get_num10(fp);

			if(map[p.x][p.y].floor_kind == Shelf)
				break;
			else
				fprintf(stderr,"(%d, %d) is aisle\n", p.x, p.y);
		}

		item_info[i].position = p;

		fprintf(stderr,"input box level of item %d ", i);
		fprintf(stderr,"(0 to %d): ", n_box - 1);
		l = get_num10(fp);

		item_info[i].box_level = l;
		map[p.x][p.y].n_empty--;
		map[p.x][p.y].box[l] = i;
	}
}

void set_rand_posi(void)
{
	int i;
	Coordinatetype p;
	int l;

	for(i = 0; i < total_item; i++){
		while(1){
			p.x = rand() % floor_width;
			p.y = rand() % floor_height;

			if(map[p.x][p.y].floor_kind == Shelf &&
				map[p.x][p.y].n_empty > 0)
				break;
		}

		item_info[i].position = p;

/*
		while(1){
			l = rand() % n_box;

			if(map[p.x][p.y].box[l] == Empty)
				break;
		}
*/
l = 0;

		item_info[i].box_level = l;
		map[p.x][p.y].n_empty--;
		map[p.x][p.y].box[l] = i;
	}
}

void initial_setting(void)
{
	int seed;

	if(option == Input){
		get_init_posi(stdin);
		return;
	}

	seed = time(NULL);

	if(option == Seed){
		fprintf(stderr,"seed = ");
		fscanf(stdin, "%d", &seed);
		seed++;
	}

	srand(seed);
	set_rand_posi();
}
