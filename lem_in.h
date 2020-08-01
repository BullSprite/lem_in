#include "libft/libft.h"

typedef struct		s_room
{
	char 			*name;
	int				x;
	int 			y;
	int 			path_len;
	char			type;
	char			state;
	int				level;
	int 			output_count;
	int 			bfs_lvl;
	int 			input_links;
	int 			output_links;
	int				links;
	int 			input_count;
	int				id;
	int 			q_len;
	struct s_room	*next;
	struct s_room	**linked;
	struct s_room	*parent;
	struct s_room	*next_q;
	struct s_room	*child;
	int		str_p;
	int		rev_p;
	struct s_room	*from;
}					t_room;

typedef struct		s_path
{
	int		length;
	t_room	*path;
}					t_path;

typedef struct		s_farm
{
	int		ants;
	int 	ants_at_start;
	int 	ants_at_finish;
	t_room	*start;
	t_room	*finish;
	t_room 	*rooms;
}			t_farm;

void	init_queue(t_room **start);
void	enqueue(t_room **start,t_room *r);
t_room	*dequeue(t_room **start);
t_room	*bfs(t_room *list, int *info);