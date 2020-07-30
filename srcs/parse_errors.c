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