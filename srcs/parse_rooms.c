/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:12:15 by swynona           #+#    #+#             */
/*   Updated: 2020/08/06 22:12:15 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

t_room	*room_init(char **parts, t_type type)
{
	t_room	*room;
	int		i;

	i = -1;
	if (!(room = ft_memalloc(sizeof(t_room))))
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
	room_init_additional(room);
	free(parts[1]);
	free(parts[2]);
	free(parts);
	return (room);
}

int		room_set(t_farm *farm, char **parts, t_type type)
{
	t_room	*room;
	t_room	*tmp;

	tmp = farm->rooms;
	if (!(room = room_init(parts, type)) ||
		(!tmp && (farm->rooms = room)))
		return (1);
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->name, room->name))
		{
			free(room);
			return (0);
		}
		tmp = tmp->next;
	}
	if (!ft_strcmp(tmp->name, room->name))
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
	int		len;
	char	**parts;

	if ((i = -1) && (line[0] == 'L' || line[0] == '#' ||
		!(parts = ft_strsplit(line, ' '))))
		error_rooms(farm, line);
	i = -1;
	if (((len = parts_len(parts)) != 3))
	{
		while (++i < len)
			free(parts[i]);
		free(parts);
		error_rooms(farm, line);
	}
	if (!is_int(parts, 1) || !is_int(parts, 2) || !room_set(farm, parts, type))
		error_rooms(farm, line);
}

void	make_start_or_finish(t_farm *farm, char *line, t_type type)
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

int		parse_room(t_farm *farm, char *line, int flag)
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
	return (flag);
}
