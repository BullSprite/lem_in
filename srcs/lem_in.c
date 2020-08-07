/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:12:15 by swynona           #+#    #+#             */
/*   Updated: 2020/08/06 22:12:15 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	sort_paths(t_farm *farm)
{
	int		i;
	int		j;
	t_room	*tmp;
	int		tmp1;

	i = -1;
	while ((farm->start->linked)[++i])
	{
		j = i;
		while ((farm->start->linked)[++j])
		{
			if (((farm->start->linked)[i])->path_len >
				((farm->start->linked)[j])->path_len)
			{
				tmp = (farm->start->linked)[i];
				(farm->start->linked)[i] = (farm->start->linked)[j];
				(farm->start->linked)[j] = tmp;
				tmp1 = farm->start->capacity[i];
				(farm->start->capacity)[i] = (farm->start->capacity)[j];
				(farm->start->capacity)[j] = tmp1;
			}
		}
		(farm->start->linked)[i]->real_len = 0;
	}
}

void	right_path_len(t_farm *farm)
{
	int		i;
	int		j;

	sort_paths(farm);
	i = -1;
	while ((farm->start->linked)[++i] && (j = -1))
	{
		if ((farm->start->linked)[i]->path_len == 2147483647)
		{
			(farm->start->linked)[i]->real_len = MAXINT;
			return ;
		}
		while (++j < i)
			(farm->start->linked)[i]->real_len +=
					(farm->start->linked)[i]->path_len -
					(farm->start->linked)[j]->path_len;
	}
}

void	farm_delition(t_farm *farm)
{
	t_room	*tmpr;
	t_link	*tmpl;

	tmpl = farm->links;
	while (farm->links)
	{
		tmpl = farm->links->next;
		free(farm->links);
		farm->links = tmpl;
	}
	tmpr = farm->rooms;
	while (farm->rooms)
	{
		tmpr = farm->rooms->next;
		free(farm->rooms->linked);
		if (farm->rooms->capacity)
			free(farm->rooms->capacity);
		free(farm->rooms->name);
		free(farm->rooms);
		farm->rooms = tmpr;
	}
	free(farm);
}

void	measure_paths(t_room *start, t_farm *farm)
{
	int		i;
	int		path_len;
	t_room	*tmp;

	i = -1;
	while (++i < start->links)
	{
		tmp = start->linked[i];
		path_len = 1;
		if (tmp)
		{
			while (tmp->child != 0)
			{
				path_len++;
				tmp = tmp->child;
			}
			if (tmp->idx == farm->finish->idx)
				start->linked[i]->path_len = path_len;
		}
	}
}

int		main(void)
{
	t_farm	*farm;

	farm = input_parse();
	farm->print = 0;
	farm->finish->path_len = 0;
	if (!make_paths(farm->rooms, farm))
		error_links(farm, NULL, NULL, NULL);
	farm->print = 1;
	ants_way(farm);
	farm_delition(farm);
	return (0);
}
