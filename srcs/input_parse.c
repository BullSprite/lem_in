#include "../includes/lem_in.h"

int 	error(t_farm	*farm)
{
	free(farm);
	ft_putstr("ERROR");
	return 0;
}

t_farm 	*init_farm(void)
{
	t_farm	*farm;

	if (!(farm = ft_memalloc(sizeof(t_farm*))))
		return (error(farm));
	farm->ants = 0;
	farm->ants_at_finish = 0;
	farm->ants_at_start = 0;
	farm->finish = NULL;
	farm->start = NULL;
	farm->rooms = NULL;
	farm->links = NULL;
	return (farm);
}

int parse_ants(t_farm *farm)
{
	char	*line;
	int 	i;

	if (!get_next_line(0, &line))
		return (error(farm));
	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
		{
			free(line);
			return (error(farm));
		}
	farm->ants = ft_atoi(line);
	free(line);
	return (1);
}

t_farm	*input_parse(void)
{
	t_farm	*farm;
	char	*line;

	if (!(farm = init_farm()) || !parse_ants(farm))
		return (0);
	return (farm);
}