#include "lem_in.h"

void	init_queue(t_room **start)
{
	(*start)->q_len = 0;
}

void	enqueue(t_room **start,t_room *r)
{
	t_room *node;
	if (start && r)
	{
		if (!(*start))
		{
			*start = r;
			(*start)->next_q = 0;
			(*start)->q_len = 1;
			return ;
		}
		if ((*r)->)
		node = *start;
		while (node->next_q)
			node = node->next_q;
		node->next_q = r;
		r->next_q = 0;
		(*start)->q_len += 1;
	}
}

t_room	*dequeue(t_room **start)
{
	t_room	*tmp;

	tmp = start;
	if (!start || !*start || (*start)->q_len == 0)
		return (0);
	*start = (*start)->next_q;
	(*start)->q_len -= 1;
	return (tmp);
}