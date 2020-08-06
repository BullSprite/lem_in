/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:12:15 by swynona           #+#    #+#             */
/*   Updated: 2020/08/06 22:12:15 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		error_farm(t_farm *farm)
{
	t_command	*command;

	while (farm->commands)
	{
		command = farm->commands->next;
		free(farm->commands->line);
		free(farm->commands);
		farm->commands = command;
	}
	free(farm);
	ft_putstr("ERROR\n");
	exit(1);
}

int		error_rooms(t_farm *farm, char *line)
{
	t_room *room;

	if (line)
		free(line);
	while (farm->rooms)
	{
		room = farm->rooms->next;
		if (farm->rooms->name)
			free(farm->rooms->name);
		if (farm->rooms->linked)
			free(farm->rooms->linked);
		if (farm->rooms->capacity)
			free(farm->rooms->capacity);
		free(farm->rooms);
		farm->rooms = room;
	}
	return (error_farm(farm));
}

int		error_links(t_farm *farm, char *line, char *room1, char *room2)
{
	t_link	*link;

	if (line)
	{
		free(line);
		line = NULL;
	}
	if (room1)
		free(room1);
	if (room2)
		free(room2);
	while (farm->links)
	{
		link = farm->links->next;
		free(farm->links);
		farm->links = link;
	}
	return (error_rooms(farm, line));
}
