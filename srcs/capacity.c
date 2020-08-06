/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capacity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:12:15 by swynona           #+#    #+#             */
/*   Updated: 2020/08/06 22:12:15 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

int		get_cap(t_room *r1, t_room *r2)
{
	int i;

	i = -1;
	if (!r1 || !r2)
		return (-1);
	while (++i < r1->links)
	{
		if (r1->linked[i]->idx == r2->idx)
			return (r1->capacity[i]);
	}
	return (-1);
}

int		set_cap(t_room *r1, t_room *r2, int cap)
{
	int i;

	i = -1;
	while (++i < r1->links)
	{
		if (r1->linked[i]->idx == r2->idx)
		{
			r1->capacity[i] = cap;
			return (1);
		}
	}
	return (-1);
}

void	clear_state(t_room *l, t_farm *farm, int flag)
{
	t_room	*tmp;

	tmp = l;
	while (tmp)
	{
		tmp->state = 'u';
		if (flag == 1)
		{
			tmp->best_child = tmp->child;
			tmp->best_parent = tmp->parent;
			tmp->best_path_len = tmp->path_len;
		}
		if (flag == 2)
		{
			tmp->child = tmp->best_child;
			tmp->parent = tmp->best_parent;
			tmp->path_len = tmp->best_path_len;
		}
		tmp->next_q = 0;
		tmp->bfs_parent = 0;
		tmp = tmp->next;
	}
}

int		init_capacity(t_room *l, t_farm *farm)
{
	t_room	*tmp;
	int		i;

	tmp = l;
	while (tmp)
	{
		tmp->capacity = (int *)ft_memalloc(sizeof(int) * tmp->links);
		i = -1;
		while (++i < tmp->links)
		{
			tmp->capacity[i] = 1;
		}
		tmp = tmp->next;
	}
}
