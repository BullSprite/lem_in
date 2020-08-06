#include "../includes/lem_in.h"

int		get_capacity(t_room *r1, t_room *r2)
{
	int i;

	i = -1;

	if (!r1 || !r2)
		return (-1);
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

t_room	*map_adj(t_room **q, t_room *room, t_farm *farm)
{
	int i;
	int r_r_bfs_cap;

	i = -1;

	r_r_bfs_cap = get_capacity(room, room->bfs_parent);
	t_room *tt;
	while (++i < room->links)
	{

		if (room->child && room->capacity[i]
		&& get_capacity(room->linked[i], room)
		&& r_r_bfs_cap)
			continue;
		if(room->linked[i]->state == 'u'
		&& room->capacity[i] == 1)
		{
			enqueue(q,room->linked[i]);
			room->linked[i]->bfs_parent = room;
			room->linked[i]->state = 'd';
		}
	}
	return (0);
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
	while(tmp)
	{
		tmp->capacity = (int *)ft_memalloc(sizeof(int) * tmp->links);
		i = -1;
		if(tmp->idx == farm->start->idx)
			tmp->is_linked_with_start = 1;
		while (++i < tmp->links)
		{
			tmp->capacity[i] = 1;
			if(tmp->linked[i]->idx == farm->start->idx)
				tmp->is_linked_with_start = 1;
		}

		tmp = tmp->next;
	}
}

t_room	*find_start(t_room *tmp, t_farm *farm)
{
	while(1)
	{
		if(tmp->bfs_parent->idx == farm->start->idx)
		{
			tmp->parent = tmp->bfs_parent;
			set_capacity(farm->start, tmp, 0);
			break ;
		}
		if(tmp->parent
		   && get_capacity(tmp->bfs_parent, tmp)
		   && get_capacity(tmp, tmp->bfs_parent) && get_capacity(tmp->parent, tmp) == 0)
		{
			tmp->parent = tmp->bfs_parent;
			tmp->parent->child = tmp;
		}
		set_capacity(tmp->bfs_parent, tmp, 0);
		if (tmp->parent == 0)
		{
			tmp->parent = tmp->bfs_parent;
			tmp->parent->child = tmp;
		}
		tmp->path_len = tmp->child->path_len + 1;
		tmp = tmp->bfs_parent;
	}
	return (tmp);
}

t_room	*traverse_path(t_room *room, t_farm *farm)
{
	t_room	*tmp;

	tmp = room;
	if (tmp->bfs_parent->idx == farm->start->idx)
	{
		set_capacity(farm->start,farm->finish, 0);
		room->child = 0;
		farm->finish->path_len = 1;
		return (tmp);
	}
	set_capacity(tmp->bfs_parent, tmp, 0);
	tmp->bfs_parent->child = tmp;
	tmp = tmp->bfs_parent;
	tmp = find_start(tmp, farm);
	tmp->path_len = tmp->child->path_len + 1;
	tmp->path_len += 1;
	return (tmp);
}

t_room	**make_paths(t_room *list, t_farm *farm)
{
	int 	i;
	int tmp_step;
	t_room	*ret;

	i = -1;
	tmp_step = MAXINT;
	init_capacity(list, farm);
	while(ret = bfs(list, farm))
	{
		++i;
		if (i >= farm->start->links)
			break;
		ret = traverse_path(ret,farm);
		measure_paths(farm->start, farm);
		right_path_len(farm);
		ants_way(farm);
		clear_state(list, farm->step < tmp_step ? 1  : 0);
		if (farm->step < tmp_step)
			tmp_step = farm->step;
	}
	clear_state(list, farm, 2);
	right_path_len(farm);
	if (i == -1)
		return (0);
	return (farm->start->linked);
}


t_room	*bfs(t_room *list, t_farm *farm)
{
	t_room	*q;
	t_room	*tmp;

	q = list;
	while (q->idx != farm->start->idx)
		q = q->next;
	enqueue(&q, q);
	q->state = 'd';
	while(q)
	{
		tmp = dequeue(&q);
		if (tmp->idx == farm->finish->idx)
			return (tmp);
		tmp->state = 'p';
		map_adj(&q, tmp, farm);

	}
	return (0);
}

