#include "../includes/lem_in.h"

int 	error(t_farm	*farm)
{
	free(farm);
	ft_putstr("ERROR");
	return 0;
}

t_farm	*input_parse(void)
{
	t_farm	*farm;
	t_room	*room;
	char 	*line;
	int 	flag;

	flag = 0;
	if (!(farm = ft_memalloc(sizeof(t_farm))))
		return 0;
	if (get_next_line(0, &line) &&
		!(farm->n = ft_atoi(line))
		return error(farm));
	if (get_next_line(0, &line) &&
		!ft_strcmp(line, "# rooms"))
		return error(farm);
	while (get_next_line(0, &line))
	{
		if (!ft_strcmp(line, "##start"))
			flag = 1;
		else if (!ft_strcmp(line, "##end"))
			flag = 2;
		else
		{

		}
	}
}