#include "../includes/lem_in.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_farm	*farm;
	farm = input_parse();
	printf("%d\n", farm->ants);
	return 0;
}