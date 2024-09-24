#include "decs.h"

void close_files(void)
{
	fclose(list_file);
	fclose(map_file);
}
