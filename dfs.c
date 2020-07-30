#include "lem_in.h"
//int start, int end, int rooms_count
t_room	*map_adj(t_room **q, t_room *room, int *info)
{
	int i;

	i = -1;
	while (++i < room->links)
	{
		if (info[1] == (room->linked)[i]->id)
			return (room);
		if((room->linked)[i]->state == 'u')
		{
			enqueue(q,(room->linked)[i]);
			(room->linked)[i]->parent = room;
			if (room->id != info[0])
				room->child = (room->linked)[i];
			(room->linked)[i]->state = 'd';
		}
	}
	return (0);
}

t_room	*traverse_path(t_room *room)
{
	t_room	*tmp;
	int 	path_len;

	tmp = room;
	path_len = 0;
	while(tmp->bfs_lvl != 1)
	{
		tmp->path_len = ++path_len;
		tmp = tmp->parent;
	}
	return (tmp);
}

t_room	*bfs(t_room *list, int *info)
{
	t_room	*q;
	t_room	*tmp;
	int		length;
	int 	is_valid;

	q = list;
	length = 0;
	while (list->id != info[0])
		q = q->next;
	q->bfs_lvl = -1;
	init_queue(&q);
	enqueue(&q, q);
	q->state = 'd';
	while(q->q_len)
	{
		tmp = dequeue(&q);
		tmp->bfs_lvl += 1;
		tmp->state = 'p';
		if (tmp = map_adj(&q, tmp, info))
			return (traverse_path(tmp));
	}
	return (0);
}

