#include "../includes/lem_in.h"

t_farm 	*init_farm(void)
{
	t_farm	*farm;

	if (!(farm = ft_memalloc(sizeof(t_farm))))
		return ((t_farm *)error_farm(farm));
	farm->ants = 0;
	farm->ants_at_finish = 0;
	farm->ants_at_start = 0;
	farm->step = 0;
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

int 	string_type(char *line)
{
	int len;

	len = ft_strlen(line);
	if (len > 1 && line[0] == '#' && line[1] == '#')
		return (1);
	else if (len > 0 && line[0] == '#')
		return (3);
	else if (ft_strchr(line, ' '))
		return (1);
	else
		return (2);
}

int		parse_rooms(t_farm *farm, char *line)
{
	int	flag;
	int	stype;

	flag = 0;
	while (get_next_line(0, &line))
	{
		if ((stype = string_type(line)) == 3)
			continue;
		if (stype == 2)
		{
			if (flag || !(farm->start) || !(farm->finish))
				return (error_rooms(farm, line));
			return (parse_links(farm, line, 1));
		}
		flag = parse_room(farm, line, flag);
	}
	return (0);
}

t_farm	*input_parse(void)
{
	t_farm	*farm;
	char	*line;

	if (!(farm = init_farm()) || !parse_ants(farm))
		return (0);
	if (!parse_rooms(farm, line) || !make_connections(farm))
	{
		free(line);
		return ((t_farm *)error_farm(farm));
	}
	return (farm);
}