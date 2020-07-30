#include "../includes/lem_in.h"

t_room	*find_room(t_farm * farm, char *name)
{
	t_room	*tmp;

	tmp = farm->rooms;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

t_link 	*init_link(t_farm *farm, char *line, t_room *from, t_room *where)
{
	t_link	*link;

	if (!(link = ft_memalloc(sizeof(link))))
		error_links(farm, line, NULL, NULL);
	link->from = from;
	link->where = where;
	link->next = NULL;
	from->links += 1;
	where->links += 1;
	return (link);
}

void 	set_link(t_farm *farm, char *line, t_room *from, t_room *where)
{
	t_link	*link;
	t_link	*tmp;

	if ((link = init_link(farm, line, from, where)) && !(farm->links))
		farm->links = link;
	else if ((tmp = farm->links))
	{
		while (tmp->next)
		{
			if ((tmp->from == link->from && tmp->where == link->where) ||
				(tmp->where == link->from && tmp->from == link->where))
			{
				free(link);
				error_links(farm, line, NULL, NULL);
			}
			tmp = tmp->next;
		}
		if ((tmp->from == link->from && tmp->where == link->where) ||
			(tmp->where == link->from && tmp->from == link->where))
		{
			free(link);
			error_links(farm, line, NULL, NULL);
		}
		tmp->next = link;
	}
}

int 	create_links(t_farm *farm, char *line)
{
	char	*dash;
	char	*from_name;
	char	*where_name;
	t_room	*where;
	t_room	*from;

	dash = line;
	where_name = 0;
	while ((dash = ft_strchr(dash + 1, '-')))
	{
		if (!(from_name = ft_strsub(line, 0, dash - line)) ||
			!(where_name = ft_strsub(dash + 1, 0, ft_strlen(dash + 1))))
			error_links(farm, line, from_name, where_name);
		from = find_room(farm, from_name);
		where = find_room(farm, where_name);
		free(from_name);
		free(where_name);
		if (from && where)
		{
			set_link(farm, line, from, where);
			return (1);
		}
	}
	return (0);
}

int 	parse_links(t_farm *farm, char *line)
{
	while (get_next_line(0, &line))
	{
		if (!create_links(farm, line))
			error_links(farm, line, NULL, NULL);
	}
	if (!(farm->finish->links) || !(farm->start->links))
		error_links(farm, line, NULL, NULL);
	free(line);
	return (1);
}