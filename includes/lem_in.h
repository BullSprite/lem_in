#ifndef LEM_IN_H
#define LEN_IN_H

#include "../libft/libft.h"

typedef struct 		s_room
{
	int		idx;
	int		name;
}			t_room;

typedef struct		s_farm
{
	int		n;
	t_room	start;
	t_room	finish;
	int		**farm;
}			t_farm;

void	lem_in(void);
#endif