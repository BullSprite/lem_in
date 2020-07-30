#include "../includes/lem_in.h"

int 	is_int(char **parts, int id)
{
	int		i;

	i = -1;
	if (parts[id][0] == '-')
		i++;
	while (parts[id][++i])
		if (!ft_isdigit(parts[id][i]))
		{
			free(parts[0]);
			free(parts[1]);
			free(parts[2]);
			free(parts);
			return (0);
		}
	return (1);
}

int 	parts_len(char **parts)
{
	int i;

	i = 0;
	while (parts[i])
		i++;
	return (i);
}