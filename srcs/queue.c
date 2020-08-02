#include "../includes/lem_in.h"

void	init_queue(t_room **start)
{
	(*start)->q_len = 0;
}

void	enqueue(t_room **start,t_room *r)
{
	t_room *node;
	if (start && r)
	{
		if (!(*start) || (*start)->q_len == 0)
		{
			*start = r;
			(*start)->next_q = 0;
			(*start)->q_len = 1;
			return ;
		}
		(*start)->q_len += 1;
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
	int 	q_len;

	tmp = *start;
	q_len = (*start)->q_len;
	if (!start || !(*start) || (*start)->q_len == 0)
		return (0);
	if ((*start)->q_len == 1)
	{
		*start = 0;
		return (tmp);
	}
	*start = (*start)->next_q;
	(*start)->q_len = q_len - 1;
	return (tmp);
}
