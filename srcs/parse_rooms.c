#include "../includes/lem_in.h"

int 	is_int(char **parts, int id)
{
	int		i;

	i = -1;
	while (parts[id][++i])
		if (!ft_isdigit(parts[1][i]))
		{
			free(parts[0]);
			free(parts[1]);
			free(parts[2]);
			free(parts);
			return (0);
		}
	return (1);
}

int 	parts_len(char **parts)
{
	int i;

	i = 0;
	while (parts[i])
		i++;
	return (i);
}

t_room	*room_init(char **parts, t_type type)
{
	t_room	*room;
	int		i;

	if ((i = -1) && !(room = ft_memalloc(sizeof(t_room))))
	{
		while (++i < 3)
			free(parts[i]);
		free(parts);
		return (0);
	}
	room->name = parts[0];
	room->x = ft_atoi(parts[1]);
	room->y = ft_atoi(parts[2]);
	room->type = type;
	room->idx = 0;
	room->bfs_lvl = 0;
	room->input_links = 0;
	room->output_links = 0;
	room->links = 0;
	room->ants  =0;
	room->next = NULL;
	room->linked = NULL;
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (room);
}

int 	room_set(t_farm *farm, char **parts, t_type type)
{
	t_room	*room;
	t_room	*tmp;

	if (!(room = room_init(parts, type)))
		return (1);
	tmp = farm->rooms;
	if (!tmp && (farm->rooms = room))
		return (1);
	while (tmp->next)
	{
		if (tmp->x == room->x && tmp->y == room->y)
		{
			free(room);
			return (0);
		}
		tmp = tmp->next;
	}
	if (tmp->x == room->x && tmp->y == room->y)
	{
		free(room);
		return (0);
	}
	tmp->next = room;
	room->idx = tmp->idx + 1;
	return (1);
}

void	make_room(t_farm *farm, char *line, t_type type)
{
	int		i;
	int 	len;
	char	**parts;

	if ((i = -1) && (line[0] == 'L' || line[0] == '#'  ||
		!(parts = ft_strsplit(line, ' '))))
		error_rooms(farm, line);
	if ((i = -1) && ((len = parts_len(parts)) != 3))
	{
		while (++i < len)
			free(parts[i]);
		free(parts);
		error_rooms(farm, line);
	}
	if (!is_int(parts, 1) || !is_int(parts, 2) || !room_set(farm, parts, type))
		error_rooms(farm, line);
}

void 	make_start_or_finish(t_farm *farm, char *line, t_type type)
{
	t_room	*tmp;

	if ((type == START && farm->start) || (type == END && farm->finish))
		error_rooms(farm, line);
	make_room(farm, line, type);
	tmp = farm->rooms;
	while (tmp->next)
		tmp = tmp->next;
	if (type == START)
		farm->start = tmp;
	else
		farm->finish = tmp;
}

int		parse_rooms(t_farm *farm, char *line)
{
	int	flag;

	flag = 0;
	while (get_next_line(0, &line) && ft_strcmp(line, "# links"))
	{
		if (!flag)
		{
			if (!ft_strcmp(line, "##start"))
				flag = 1;
			else if (!ft_strcmp(line, "##end"))
				flag = 2;
			else
				make_room(farm, line, INNER);
		}
		else
		{
			make_start_or_finish(farm, line, (flag == 1 ? START : END));
			flag = 0;
		}
	}
	if (ft_strcmp(line, "# links"))
		return (error_rooms(farm, line));
	return (1);
}