#include "../includes/lem_in.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_room **paths;
	t_farm	*farm;
	int 	*info;

	info = ft_memalloc(3*sizeof(int));
	farm = input_parse();
	info[0] = farm->start->idx;
	info[1] = farm->finish->idx;

	make_paths(farm->rooms, farm);
	printf("%d\n", farm->ants);
	return 0;
}