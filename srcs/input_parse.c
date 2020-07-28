#include "../includes/lem_in.h"

int 	error(t_farm	*farm)
{
	free(farm);
	ft_putstr("ERROR");
	return 0;
}

int 	*room_parse(char *line, t_room **rooms, int flag)
{
	int		name;
	int		x;
	int		y;
	char	**parts;
	t_room 	*room;

	if (!(parts = ft_strsplit(line, ' ')))
		return 0;
	if (ft_strlen(parts) == 3)
	{
		name = ft_atoi(parts[0]);
		x = ft_atoi((parts[1]));
		y = ft_atoi(parts[2]);
		room = *rooms;
		while (room->next)
			if (room->name == name || room->x == x || room->y = y)
				break;
			else
				room = room->next;
		if (!(room->next = ft_memalloc(sizeof(t_room*))))
			break;
		room->next->next = 0;
		room->next->name = name;
		room->next->x = x;
		room->next->y = y;
		room->next->ants = 0;
		room->next->bfs_lvl = -1;
		room->next->input_links = 0;
		room->next->output_links = 0;
		if (flag)
			room->next->type = (flag == 1 ? START : END);
		else
			room->next->type = INNER;
	}
	x = -1;
	while (parts[++x])
		free(parts[x]);
	free(parts);
	return 1;
}

int 	*link_parse(char *line, t_link **links)
{
	int 	from;
	int 	where;
	t_link	*link;
	char 	**parts;

	if (!(parts = ft_strsplit(line, '-')))
		return (0);
	if (ft_strlen(parts) == 2)
	{
		from = ft_atoi(parts[0]);
		where = ft_atoi(parts[1]);
		link = *links;
		while (link->next)
			if (link->from->name == from || link->where->name == where ||
				(link->from->name == where && link->where->name == from))
				break;
			else
				link = link->next;
		if (!(link->next == ft_memalloc(sizeof(t_link*))))
			break;
	}
}

t_farm	*input_parse(void)
{
	t_farm	*farm;
	t_room	*room;
	char 	*line;
	int 	flag;

	flag = 0;
	if (!(farm = ft_memalloc(sizeof(t_farm))))
		return (0);
	if (get_next_line(0, &line) &&
		(farm->ants = ft_atoi(line) > 0 &&
		(farm->ants_at_start = farm->ants))
		return error(farm));
	if (get_next_line(0, &line) &&
		!ft_strcmp(line, "# rooms"))
		return error(farm);
	if (!(farm->rooms = ft_memalloc(sizeof(t_room*))))
		return (error(farm))
	while (get_next_line(0, &line) && !ft_strcmp(line, "# links"))
		if (!ft_strcmp(line, "##start"))
			flag = 1;
		else if (!ft_strcmp(line, "##end"))
			flag = 2;
		else if (!room_parse(line, &(farm->rooms), flag))
			return (error(farm));
		else
			free(line);
	if (ft_strcmp(line, "# links"))
		return (error(farm));
	while (get_next_line(0, &line))

}