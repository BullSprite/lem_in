/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   technical_funks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:12:15 by swynona           #+#    #+#             */
/*   Updated: 2020/08/06 22:12:15 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		is_int(char **parts, int id)
{
	int		i;

	i = -1;
	if (parts[id][0] == '-' && ft_strcmp(parts[id], "-"))
		i++;
	while (parts[id][++i])
		if (!ft_isdigit(parts[id][i]))
		{
			free(parts[0]);
			free(parts[1]);
			free(parts[2]);
			free(parts);
			return (0);
		}
	return (1);
}

int		parts_len(char **parts)
{
	int i;

	i = 0;
	while (parts[i])
		i++;
	return (i);
}

void	print_map(t_command *command)
{
	if (command == NULL)
		return ;
	print_map(command->next);
	ft_putstr(command->line);
	ft_putchar('\n');
	free(command->line);
	free(command);
}

void	room_init_additional(t_room *room)
{
	room->idx = 0;
	room->capacity = 0;
	room->links = 0;
	room->ant = -1;
	room->next = NULL;
	room->path_len = MAXINT;
	room->linked = NULL;
	room->state = 'u';
	room->parent = 0;
	room->child = 0;
	room->ant_queue = NULL;
	room->real_len = 0;
}
