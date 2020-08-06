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
	farm->commands = NULL;
	return (farm);
}

int parse_ants(t_farm *farm)
{
	char		*line;
	int 		i;

	if (!(get_next_line(0, &line)))
		return (error_farm(farm));
	i = -1;
	while (line[++i])
		if (!ft_isdigit(line[i]))
		{
			ft_strdel(&line);
			return (error_farm(farm));
		}
	if ((farm->ants = ft_atoi(line)) < 1)
	{
		ft_strdel(&line);
		return (error_farm(farm));
	}
	farm->ants_at_start = farm->ants;
	if (!(farm->commands = ft_memalloc(sizeof(t_command))) ||
		!(farm->commands->line = ft_strdup(line)))
		error_farm(farm);
	farm->commands->next = NULL;
	ft_strdel(&line);
	return (1);
}

int 	string_type(t_farm *farm, char *line)
{
	t_command	*command;

	if (!(ft_strncmp(line, "##", 2)) && !(!ft_strcmp(line, "##start") || !ft_strcmp(line, "##end")))
		return (3);
	if (!(command = ft_memalloc(sizeof(t_command))) ||
		!(command->line = ft_strdup(line)))
		error_links(farm, line, NULL, NULL);
	command->next = farm->commands;
	farm->commands = command;
	if (line[0] == '#' && !(!ft_strcmp(line, "##start") ||
							!ft_strcmp(line, "##end")))
		return (3);
	if (line[0] == '#')
		return (1);
	else if (ft_strchr(line, ' '))
		return (1);
	else
		return (2);
}

int		parse_rooms(t_farm *farm, char **line)
{
	int	flag;
	int	stype;

	flag = 0;
	while (get_next_line(0, line))
	{
		if ((stype = string_type(farm, *line)) != 3)
		{
			if (stype == 2)
			{
				if (flag || !(farm->start) || !(farm->finish))
					return (error_rooms(farm, *line));
				return (parse_links(farm, *line, 1));
			}
			flag = parse_room(farm, *line, flag);
		}
		ft_strdel(line);
	}
	return (0);
}

t_farm	*input_parse(void)
{
	t_farm	*farm;
	char	*line;

	line = NULL;
	if (!(farm = init_farm()) || !parse_ants(farm))
		return (0);
	if (!parse_rooms(farm, &line) || !make_connections(farm))
		error_links(farm, line, NULL, NULL);
	return (farm);
}
