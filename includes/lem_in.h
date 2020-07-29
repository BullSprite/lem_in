#ifndef LEM_IN_H
#define LEN_IN_H

#include "../libft/libft.h"

typedef 			enum
{
					START,
					INNER,
					END
}					t_type;

typedef struct 		s_room
{
	char 			*name;
	int				x;
	int 			y;
	t_type			type;
	int 			bfs_lvl;
	int 			input_links;
	int 			output_links;
	int				links;
	int 			ants;
	struct s_room	*next;
	struct s_room	**linked;
}					t_room;

typedef struct	s_link
{
	t_room			*from;
	t_room			*where;
	struct s_link	*prev;
	struct s_link	*next;
}				t_link;

typedef struct		s_farm
{
	int		ants;
	int 	ants_at_start;
	int 	ants_at_finish;
	t_room	*start;
	t_room	*finish;
	t_room 	*rooms;
	t_link	*links;
}			t_farm;

void	lem_in(void);
t_farm	*input_parse(void);
#endif