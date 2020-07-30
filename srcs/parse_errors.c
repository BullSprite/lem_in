#include "../includes/lem_in.h"

int 	error_farm(t_farm	*farm)
{
	free(farm);
	ft_putstr("ERROR\n");
	exit(1);
}

int 	error_rooms(t_farm *farm, char *line)
{
	t_room *room;

	if (line)
		free(line);
	while(farm->rooms)
	{
		room = farm->rooms->next;
		free(farm->rooms->name);
		free(farm->rooms);
		farm->rooms = room;
	}
	return (error_farm(farm));
}

int		error_links(t_farm *farm, char *line, char *room1, char *room2)
{
	t_link	*link;

	if (line)
	{
		free(line);
		line = NULL;
	}
	if (room1)
		free(room1);
	if (room2)
		free(room2);
	while(farm->links)
	{
		link = farm->links->next;
		free(farm->links);
		farm->links = link;
	}
	return (error_rooms(farm, line));
}