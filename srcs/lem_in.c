#include "../includes/lem_in.h"

void	right_path_len(t_farm *farm)
{
	int		i;
	int 	j;
	int		len;
	t_room	*tmp;

	i = -1;
	while ((len = 1) && (tmp = (farm->start->linked)[++i]))
	{
		while (tmp != farm->finish)
		{
			len++;
			tmp = tmp->child;
		}
		((farm->start->linked)[i])->path_len = len;
	}
	i = -1;
	while ((farm->start->linked)[++i] && ((j = i) == j))
		while ((farm->start->linked)[++j])
			if (((farm->start->linked)[i])->path_len >
				((farm->start->linked)[j])->path_len)
			{
				tmp = (farm->start->linked)[i];
				(farm->start->linked)[i] = (farm->start->linked)[j];
				(farm->start->linked)[j] = tmp;
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

int 	main(int argc, char **argv)
{
	t_room **paths;
	t_farm	*farm;
	int 	*info;

	info = ft_memalloc(3*sizeof(int));
	farm = input_parse();
	info[0] = farm->start->idx;
	info[1] = farm->finish->idx;

	make_paths(farm->rooms, farm);
	right_path_len(farm);
	ants_way(farm);
	farm_delition(farm);
	return 0;
}