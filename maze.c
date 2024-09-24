#include "decs.h"

char check_map(Coordinatetype p)
{
	if(p.x < 0 || floor_width <= p.x)
		return Unavailable;

	if(p.y < 0 || floor_height <= p.y)
		return Unavailable;

	if(map[p.x][p.y].floor_kind == Shelf)
		return Unavailable;

	if(map[p.x][p.y].time_stamp == time_count)
		return Unavailable;

	return Available;
}

char put_next(Coordinatetype s, Coordinatetype g, int *next_size)
{
	Coordinatetype next_p;

	// left
	next_p.x = s.x - 1;
	next_p.y = s.y;
	if(next_p.x == g.x && next_p.y == g.y)
		return Reached;

	if(check_map(next_p) == Available){
		map[next_p.x][next_p.y].time_stamp = time_count;
		next_front[*next_size] = next_p;
		*next_size = *next_size + 1;
	}

	// right
	next_p.x = s.x + 1;
	next_p.y = s.y;
	if(next_p.x == g.x && next_p.y == g.y)
		return Reached;

	if(check_map(next_p) == Available){
		map[next_p.x][next_p.y].time_stamp = time_count;
		next_front[*next_size] = next_p;
		*next_size = *next_size + 1;
	}

	// up
	next_p.x = s.x;
	next_p.y = s.y - 1;
	if(next_p.x == g.x && next_p.y == g.y)
		return Reached;

	if(check_map(next_p) == Available){
		map[next_p.x][next_p.y].time_stamp = time_count;
		next_front[*next_size] = next_p;
		*next_size = *next_size + 1;
	}

	// down
	next_p.x = s.x;
	next_p.y = s.y + 1;
	if(next_p.x == g.x && next_p.y == g.y)
		return Reached;

	if(check_map(next_p) == Available){
		map[next_p.x][next_p.y].time_stamp = time_count;
		next_front[*next_size] = next_p;
		*next_size = *next_size + 1;
	}

	return Processing;
}

int maze(Coordinatetype from, Coordinatetype to)
{
	int d, i;
	int cur_size, next_size;
	char flag;
	Coordinatetype *tmp;

	flag = Processing;
	cur_front[0] = from;
	cur_size = 1;
	next_size = 0;

	for(d = 0; flag == Processing; d++){
		for(i = 0; i < cur_size; i++){
			flag = put_next(cur_front[i], to, &next_size);

			if(flag == Reached)
				break;
		}

		tmp = cur_front;
		cur_front = next_front;
		next_front = tmp;
		cur_size = next_size;
		next_size = 0;
	}

	time_count++;

	return d;
}
