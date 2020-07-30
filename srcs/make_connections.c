#include "../includes/lem_in.h"

int 	make_connections(t_farm *farm)
{
	t_room	*tmp;
	t_link	*tmpl;
	int		i;

	tmp = farm->rooms;
	while (tmp)
	{
		if (!(tmp->linked = ft_memalloc(sizeof(t_room *) *
			(tmp->links + 1))))
			error_links(farm, NULL, NULL, NULL);
		tmp = tmp->next;
	}
	tmpl = farm->links;
	while ((i = 0) || tmpl)
	{
		while ((tmpl->from->linked)[i])
			i++;
		(tmpl->from->linked)[i] = tmpl->where;
		i = 0;
		while ((tmpl->where->linked)[i])
			i++;
		(tmpl->where->linked)[i] = tmpl->from;
		tmpl = tmpl->next;
	}
	return (1);
}