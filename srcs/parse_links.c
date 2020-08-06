/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:12:15 by swynona           #+#    #+#             */
/*   Updated: 2020/08/06 22:12:15 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room	*find_room(t_farm *farm, char *name)
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

t_link	*init_link(t_farm *farm, char *line, t_room *from, t_room *where)
{
	t_link	*link;

	if (!(link = ft_memalloc(sizeof(t_link))))
		error_links(farm, line, NULL, NULL);
	link->from = from;
	link->where = where;
	link->next = NULL;
	from->links += 1;
	where->links += 1;
	return (link);
}

void	set_link(t_farm *farm, char *line, t_room *from, t_room *where)
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
				from->links -= 1;
				where->links -= 1;
				free(link);
				return ;
			}
			tmp = tmp->next;
			if (!(tmp->next))
				break ;
		}
		tmp->next = link;
	}
}

int		create_links(t_farm *farm, char *line)
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

int		parse_links(t_farm *farm, char *line, int mode)
{
	if (mode && !create_links(farm, line))
		error_links(farm, line, NULL, NULL);
	ft_strdel(&line);
	while (get_next_line(0, &line))
	{
		if (string_type(farm, line) != 3)
			if (!create_links(farm, line))
				error_links(farm, line, NULL, NULL);
		ft_strdel(&line);
	}
	if (!(farm->finish->links) || !(farm->start->links))
		error_links(farm, line, NULL, NULL);
	ft_strdel(&line);
	return (1);
}
