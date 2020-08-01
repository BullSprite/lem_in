#include "../includes/lem_in.h"

void 	add_ant_queue(t_farm *farm, t_room *room_to_add)
{
	t_room	*tmp;

	if (room_to_add == farm->finish)
		return ;
	if (!(farm->start->ant_queue))
		farm->start->ant_queue = room_to_add;
	else
	{
		tmp = farm->start->ant_queue;
		while (tmp->ant_queue)
			tmp = tmp->ant_queue;
		tmp->ant_queue = room_to_add;
	}
	room_to_add->step = farm->step + 1;
}

void	print_move(t_room *where, int flag)
{
	if (!where)
	{
		ft_putchar('\n');
		return ;
	}
	if (flag)
		ft_putchar(' ');
	ft_putchar('L');
	ft_putnbr(where->ant);
	ft_putchar('-');
	ft_putstr(where->name);
}

int 	make_move(t_farm *farm, t_room *from, t_room *where, int flag)
{
	t_room *tmp;

	if (from == farm->start)
	{
		farm->ants_at_start--;
		where->ant = farm->ants - farm->ants_at_start;
	}
	else
	{
		where->ant = from->ant;
		from->ant = -1;
		tmp = farm->start->ant_queue;
		farm->start->ant_queue = tmp->ant_queue;
		tmp->ant_queue = NULL;
	}
	print_move(where, flag);
	add_ant_queue(farm, where);
	return (1);
}

void	move_ant_from_start(t_farm *farm, int flag)
{
	int i;

	i = -1;
	while((farm->start->linked)[++i])
	{
		if (farm->ants_at_start == 0)
			return ;
		if (((farm->start->linked)[i])->ant == -1)
		{
			if (i == 0)
				flag = make_move(farm, farm->start,
						  ((farm->start->linked)[i]), flag);
			else if (((farm->start->linked)[0])->child->path_len ==
						((farm->start->linked)[i])->child->path_len ||
						(farm->ants_at_start - 2 >=
						 ((farm->start->linked)[i])->child->path_len))
				flag = make_move(farm, farm->start, (farm->start->linked)[i],
				flag);
			else if (((farm->start->linked)[0])->child->path_len !=
					  ((farm->start->linked)[i])->child->path_len)
				return ;

		}
	}
}

void	ants_way(t_farm *farm)
{
	int flag;

	while ((farm->ants_at_start) || (farm->start->ant_queue))
	{
		flag = 0;
		while (farm->start->ant_queue && farm->start->ant_queue->step ==
				farm->step)
			flag = make_move(farm, farm->start->ant_queue,
			 farm->start->ant_queue->child, flag);
		move_ant_from_start(farm, flag);
		print_move(NULL, 0);
		farm->step++;
	}
}