/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:12:15 by swynona           #+#    #+#             */
/*   Updated: 2020/08/06 22:12:15 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lem_in.h"

void	enqueue(t_room **start, t_room *r)
{
	t_room	*node;

	if (start && r)
	{
		if (!(*start))
		{
			*start = r;
			(*start)->next_q = 0;
			return ;
		}
		node = *start;
		while (node->next_q)
			node = node->next_q;
		node->next_q = r;
		r->next_q = 0;
	}
}

t_room	*dequeue(t_room **start)
{
	t_room	*tmp;

	tmp = *start;
	if (!start || !(*start))
		return (0);
	*start = (*start)->next_q;
	return (tmp);
}
