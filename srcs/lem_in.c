#include "../includes/lem_in.h"

void	right_path_len(t_farm *farm)
{
	int		i;
	int 	j;
	t_room	*tmp;
	int		tmp1;

	i = -1;
	while ((farm->start->linked)[++i] && ((j = i) == j))
	{
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
	i = -1;
	while ((farm->start->linked)[++i] && (j = -1))
	{
		if ((farm->start->linked)[i]->path_len == 2147483647) {
			(farm->start->linked)[i]->real_len = MAXINT;
			return;
		}
		while (++j < i)
			(farm->start->linked)[i]->real_len +=
					(farm->start->linked)[i]->path_len -
					(farm->start->linked)[j]->path_len;
	}
}

void		farm_delition(t_farm *farm)
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
		free(farm->rooms->name);
		free(farm->rooms->capacity);
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
			while(tmp->child != 0)
			{
				path_len++;
				tmp = tmp->child;
			}
			if (tmp->idx == farm->finish->idx)
				start->linked[i]->path_len = path_len;
			//else
				//start->linked[i]->path_len = MAXINT;
		}
	}
}

void	print_paths(t_room *start, t_farm *farm, int flag)
{
	int		i;
	t_room	*tmp;

	i = -1;
	while (++i < start->links)
	{
		tmp = start->linked[i];
		if (tmp)
		{
			if (flag ? tmp->best_path_len : tmp->path_len != MAXINT)
			{
				printf("|%d| ", flag ? tmp->best_path_len : tmp->path_len);
				while(tmp)
				{
					printf("%d ", tmp->idx);
					tmp = flag ? tmp->best_child : tmp->child;
				}
				printf("\n");
			}
		}
	}
}

int 	main(int argc, char **argv)
{
	t_room **paths;
	t_farm	*farm;

	farm = input_parse();

	farm->print = 0;
	farm->finish->path_len = 0;
	if(!make_paths(farm->rooms, farm))
	{
		printf("what?");
		return (0);
	}
	//farm->print = 1;

	ants_way(farm);
	//ants_way(farm);
	//ft_putchar('\n');
	farm_delition(farm);
	ft_putnbr(farm->step);
	ft_putchar('\n');
	//measure_paths(farm->start, farm);
	//right_path_len(farm);
	//print_paths(farm->start, farm);

	//ants_way(farm);
	//farm_delition(farm);
	//ft_putnbr(farm->step);
	//ft_putchar('\n');
	return 0;
}
