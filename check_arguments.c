#include "decs.h"

void usage_message(void)
{
	fprintf(stderr,"\n");
	fprintf(stderr,"################################################\n");
	fprintf(stderr,"Usage: cal_dist [-(options)] item_list floor_map\n");
	fprintf(stderr,"------------------------------------------------\n");
	fprintf(stderr,"<options>\n");
	fprintf(stderr,"i: input Initial position of each item\n");
	fprintf(stderr,"s: input Seed for random numbers\n");
	fprintf(stderr,"------------------------------------------------\n");
	fprintf(stderr,"item_list: file.list\n");
	fprintf(stderr,"floor_map: file.map\n");
	fprintf(stderr,"################################################\n");
	fprintf(stderr,"\n");
}

void check_option(char *string)
{
	string++;
	while(*string){
		switch(*string){
		case 'i':
			option = Input;
			break;
		case 's':
			option = Seed;
			break;
		default:
			usage_message();
			exit(1);
		}
		string++;
	}
}

char compare(char *p1, char *p2)
{
	while(*p1 == *p2){
		if(*p1 == StringEnd || *p2 == StringEnd)
			break;
		p1++;
		p2++;
	}

	if(*p1 == StringEnd && *p2 == StringEnd)
		return Same;

	return Different;
}

char check_extension(char *string)
{
	while(*string != '.' && *string != StringEnd)string++;
	if(*string == StringEnd)
		return Unknown;

	string++;
	switch(*string){
	case 'l':
		if(compare(string, "list") == Same)
			return LIST;
		return Unknown;
	case 'm':
		if(compare(string, "map") == Same)
			return MAP;
		return Unknown;
	default:
		return Unknown;
	}
}

void open_files(char *string)
{
	int file_kind;

	file_kind = check_extension(string);

	switch(file_kind){
	case LIST:
		list_file = fopen(string, "r");
		if(list_file == NULL){
			fprintf(stderr,"%s: open failed\n",string);
			exit(1);
		}

		break;
	case MAP:
		map_file = fopen(string, "r");
		if(map_file == NULL){
			fprintf(stderr,"%s: open failed\n",string);
			exit(1);
		}

		break;
	default:
		fprintf(stderr,"%s: file format is wrong\n\n",string);
		usage_message();
		exit(1);
	}
}

void check_arguments(int argc, char *argv[])
{
	int i;
	int file_count;

	if(argc < (MinFile + 1)){
		usage_message();
		exit(1);
	}

	option = Default;
	file_count = 0;

	for(i = 1;i < argc;i++){
		switch(argv[i][0]){
		case '-':
			check_option(argv[i]);
			break;
		default:
			if(file_count < MaxFile){
				open_files(argv[i]);
				file_count++;
			}
			else{
				usage_message();
				exit(1);
			}
		}
	}

	if(file_count < MinFile){
		usage_message();
		exit(1);
	}
}
