#include "decs.h"

int get_num10(FILE *fp);

void read_map(FILE *fp)
{
	int i, j;
	int x, y, w, h, y_init;

	ch = fgetc(fp);

	floor_width = get_num10(fp);
	floor_height = get_num10(fp);

	map = (MAPtype **)malloc(floor_width * sizeof(MAPtype *));
	if(map == NULL){
		fprintf(stderr,"memory allocation failed!\n");
		exit(1);
	}

	for(i = 0; i < floor_width; i++){
		map[i] = (MAPtype *)malloc(floor_height * sizeof(MAPtype));
		if(map[i] == NULL){
			fprintf(stderr,"memory allocation failed!\n");
			exit(1);
		}

		for(j = 0; j < floor_height; j++){
			map[i][j].floor_kind = Aisle;
			map[i][j].time_stamp = Empty;
		}
	}

	n_block = get_num10(fp);
	n_box = get_num10(fp);

	for(i = 0; i < n_block; i++){
		x = get_num10(fp);
		y_init = get_num10(fp);
		w = x + get_num10(fp);
		h = y_init + get_num10(fp);

		while(x < w){
			for(y = y_init; y < h; y++){
				map[x][y].floor_kind = Shelf;
				map[x][y].n_empty = n_box;
				map[x][y].box = (int *)malloc(n_box * sizeof(int));
				if(map[x][y].box == NULL){
					fprintf(stderr,"memory allocation failed!\n");
					exit(1);
				}

				for(j = 0; j < n_box; j++)
					map[x][y].box[j] = Empty;
			}
			x++;
		}
	}

	start_point.x = get_num10(fp);
	start_point.y = get_num10(fp);
	goal_point.x = get_num10(fp);
	goal_point.y = get_num10(fp);
	delivery_entrance.x = get_num10(fp);
	delivery_entrance.y = get_num10(fp);
}
