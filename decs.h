#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef	MAIN
#define	EXDEF
#else
#define	EXDEF extern
#endif

#define	MaxFile	2
#define	MinFile	2

#define LIST	1
#define MAP	2
#define Unknown	0

#define Input	1
#define Seed	2
#define Default	0

#define StringEnd	'\0'

#define Same		0
#define Different	1

#define Goal	-1

#define Aisle	0
#define Shelf	1

#define Empty	-1

#define Processing	0
#define Reached		1

#define Unavailable	0
#define Available	1

#define True 1
#define False 0

#define CoolingRate 0.95 //or 0.95, 0.99
#define InitialTemperature 2.0
#define FinalTemp 0.11
#define InnerLoopCount 100000

#define CostParamR 0.0
#define CostParamW 0.0

#define Upper 1
#define Middle 1
#define Lower 3

typedef struct Coordinate {
	int x;
	int y;
} Coordinatetype;

typedef struct ITEM {
	int weight;
	int box_level;
	int freq;
	int n_use;
	Coordinatetype position;
	int *used_product;
	int dist_from_entrance;
} ITEMtype;

typedef struct ORD {
	int item_id;
	int dist_from_prev;
} ORDtype;

typedef struct PROD {//product
	int n_item;
	int distance;
	double p_rate;
	ORDtype *item_order;
} PRODtype;

typedef struct FloorMap {
	int floor_kind;
	int n_empty;
	int time_stamp;
	int *box;
} MAPtype;

typedef struct Swap {
	Coordinatetype p;
	Coordinatetype q;
	int level_p;
	int level_q;
} SWAPtype;

/* variable declarations */
EXDEF FILE *list_file;
EXDEF FILE *map_file;

EXDEF int total_item;
EXDEF int n_product;
EXDEF int floor_width;
EXDEF int floor_height;
EXDEF int n_block;
EXDEF int n_box;
EXDEF int time_count;
EXDEF int all_distance; //総距離
EXDEF double expected_value; //期待値
EXDEF int all_replenish;  //補充口からの総距離
EXDEF double expected_replenish_value; //補充口からの距離の期待値
//EXDEF int box_level; //何段目に格納するか
EXDEF int para[3]; //棚の段数によるパラメータ
EXDEF double weight_priority; //重さによる優先度
EXDEF double cost; //コスト関数
EXDEF double new_cost;
EXDEF double old_cost; 
EXDEF double diff_cost;
EXDEF int count; //試行回数
EXDEF int accept_count; //受理回数
EXDEF int not_accept; //却下回数
EXDEF int inner_count; //温度変更回数

EXDEF clock_t start_time;
EXDEF clock_t end_time;

EXDEF char option;
EXDEF char ch;

EXDEF Coordinatetype start_point;
EXDEF Coordinatetype goal_point;
EXDEF Coordinatetype delivery_entrance;

EXDEF Coordinatetype *cur_front;
EXDEF Coordinatetype *next_front;
EXDEF ITEMtype *item_info;
EXDEF PRODtype *product_info;

EXDEF MAPtype **map;
