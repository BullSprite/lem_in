#include "../includes/lem_in.h"

t_farm 	*init_farm(void)
{
	t_farm	*farm;

	if (!(farm = ft_memalloc(sizeof(t_farm))))
		return ((t_farm *)error_farm(farm));
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

	if (!(get_next_line(0, &line)))
		return (error_farm(farm));
	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
		{
			free(line);
			return (error_farm(farm));
		}
	if ((farm->ants = ft_atoi(line)) < 1)
	{
		free(line);
		return (error_farm(farm));
	}
	free(line);
	farm->ants_at_start = farm->ants;
	return (1);
}

t_farm	*input_parse(void)
{
	t_farm	*farm;
	char	*line;

	if (!(farm = init_farm()) || !parse_ants(farm))
		return (0);
	if (!get_next_line(0, &line) || ft_strcmp(line, "# rooms") ||
		!parse_rooms(farm, line) || !parse_links(farm, line))
	{
		free(line);
		return ((t_farm *)error_farm(farm));
	}
	return (farm);
}