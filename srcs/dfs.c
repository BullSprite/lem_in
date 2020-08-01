#include "../includes/lem_in.h"
//int start, int end, int rooms_count
int		get_capacity(t_room *r1, t_room *r2)
{
	int i;

	i = -1;
	while (++i < r1->links)
	{
		if(r1->linked[i]->idx == r2->idx)
			return (r1->capacity[i]);
	}
	return (-1);
}

int		set_capacity(t_room *r1, t_room *r2, int cap)
{
	int i;

	i = -1;
	while (++i < r1->links)
	{
		if(r1->linked[i]->idx == r2->idx)
		{
			r1->capacity[i] = cap;
			return (1);
		}
	}
	return (-1);
}

t_room	*find_room_with_capacity(t_room *r1, int cap)
{
	int i;

	i = -1;
	while (++i < r1->links)
	{
		if(get_capacity(r1->linked[i],r1) == cap)
			return (r1->linked[i]);
	}
	return (0);
}
t_room	*map_adj(t_room **q, t_room *room, t_farm *farm)
{
	int i;

	i = -1;
	if (room->idx != farm->start->idx && room->parent->idx != farm->start->idx && room->child)
	{
		enqueue(q,find_room_with_capacity(room, 0));
		return (0);
	}
	while (++i < room->links)
	{
		if(room->linked[i]->idx == farm->finish->idx)
		{
			room->child = farm->finish;
			return (room);
		}
		if(room->linked[i]->state == 'u'
		&& room->capacity[i] == 1
		&& room->linked[i]->idx != farm->start->idx)
		{
			enqueue(q,room->linked[i]);
			room->linked[i]->state = 'd';
			room->linked[i]->parent = room;
		}
	}
	return (0);
}

void	clear_state(t_room *l, t_farm *farm)
{
	t_room	*tmp;

	tmp = l;
	while (tmp)
	{
		if(tmp->idx != farm->start->idx
		&& tmp->idx != farm->finish->idx)
			tmp->state = 'u';
		tmp->bfs_lvl = 0;
		tmp->q_len = 0;
		tmp = tmp->next;
	}
}
int		init_capacity(t_room *l)
{
	t_room	*tmp;
	int		i;

	tmp = l;
	while(tmp)
	{
		tmp->capacity = (int *)ft_memalloc(sizeof(int) * tmp->links);
		i = -1;
		while (++i < tmp->links)
			tmp->capacity[i] = 1;
		tmp = tmp->next;
	}
}

int 	find_parent(t_room *r1)
{
	int i;

	i = -1;
	while (++i < r1->links)
	{
		if (get_capacity(r1->linked[i], r1) == 0
		&& get_capacity(r1, r1->linked[i]) == 1)
		{
			r1->parent = r1->linked[i];
			return (1);
		}
	}
	return (0);
}
t_room	*traverse_path(t_room *room, t_farm *farm)
{
	t_room	*tmp;
	int 	path_len;

	tmp = room;
	path_len = 0;
	while(1)
	{
		++path_len;
		if(tmp->parent->idx == farm->start->idx)
		{
			set_capacity(farm->start, tmp, 0);
			break;
		}
		if(get_capacity(tmp, tmp->parent) == 0)
		{
			set_capacity(tmp->parent, tmp, 0);
			find_parent(tmp);
		}
		set_capacity(tmp, tmp->child, 0);
		set_capacity(tmp->parent, tmp, 0);
		tmp->parent->child = tmp;
		tmp = tmp->parent;
	}
	tmp->path_len = path_len + 1;
	return (tmp);
}

t_room	**make_paths(t_room *list, t_farm *farm)
{
	t_room	**paths;
	int 	i;
	t_room	*ret;

	paths = (t_room **)ft_memalloc(sizeof(t_room *) * farm->start->links);
	i = -1;
	init_capacity(list);
	while(ret = bfs(list, farm))
	{
		++i;
		paths[i] = traverse_path(ret,farm);

		clear_state(list, farm);
	}

	return (i >= 0 ? paths : 0);
}


t_room	*bfs(t_room *list, t_farm *farm)
{
	t_room	*q;
	t_room	*tmp;
	t_room	*ret;

	q = list;
	while (list->idx != farm->start->idx)
		q = q->next;
	enqueue(&q, q);
	q->state = 'd';
	while(q && q->q_len)
	{
		tmp = dequeue(&q);
		tmp->state = 'p';
		if(tmp->idx == 4)
		{
			tmp->state = 'p';
		}
		if (ret = map_adj(&q, tmp, farm))
			return (ret);
	}
	return (0);
}

