#include "../includes/lem_in.h"

t_room	*map_adj(t_room **q, t_room *room, t_farm *farm)
{
	int	i;
	int	r_r_bfs_cap;

	i = -1;
	r_r_bfs_cap = get_cap(room, room->bfs_parent);
	while (++i < room->links)
	{
		if (room->child && room->capacity[i]
			&& get_cap(room->linked[i], room)
			&& r_r_bfs_cap)
			continue;
		if (room->linked[i]->state == 'u'
		&& room->capacity[i] == 1)
		{
			enqueue(q, room->linked[i]);
			room->linked[i]->bfs_parent = room;
			room->linked[i]->state = 'd';
		}
	}
	return (0);
}

t_room	*find_start(t_room *tmp, t_farm *farm)
{
	while (1)
	{
		if (tmp->bfs_parent->idx == farm->start->idx)
		{
			tmp->parent = tmp->bfs_parent;
			set_cap(farm->start, tmp, 0);
			break ;
		}
		if (tmp->parent
			&& get_cap(tmp->bfs_parent, tmp) && get_cap(tmp, tmp->bfs_parent)
			&& get_cap(tmp->parent, tmp) == 0)
		{
			tmp->parent = tmp->bfs_parent;
			tmp->parent->child = tmp;
		}
		set_cap(tmp->bfs_parent, tmp, 0);
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
		set_cap(farm->start, farm->finish, 0);
		room->child = 0;
		farm->finish->path_len = 1;
		return (tmp);
	}
	set_cap(tmp->bfs_parent, tmp, 0);
	tmp->bfs_parent->child = tmp;
	tmp = tmp->bfs_parent;
	tmp = find_start(tmp, farm);
	tmp->path_len = tmp->child->path_len + 1;
	tmp->path_len += 1;
	return (tmp);
}

t_room	**make_paths(t_room *list, t_farm *farm)
{
	int		i;
	int		tmp_step;
	t_room	*ret;

	i = -1;
	tmp_step = MAXINT;
	init_capacity(list, farm);
	while (ret = bfs(list, farm))
	{
		++i;
		if (i >= farm->start->links)
			break ;
		ret = traverse_path(ret, farm);
		measure_paths(farm->start, farm);
		right_path_len(farm);
		ants_way(farm);
		clear_state(list, farm, farm->step < tmp_step ? 1 : 0);
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
	while (q)
	{
		tmp = dequeue(&q);
		if (tmp->idx == farm->finish->idx)
			return (tmp);
		tmp->state = 'p';
		map_adj(&q, tmp, farm);
	}
	return (0);
}
