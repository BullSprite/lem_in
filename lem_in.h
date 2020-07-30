#include "libft/libft.h"

typedef struct		s_room
{
	char 			*name;
	int				x;
	int 			y;
	struct s_room	*next;
	struct s_room	**linked;
	struct s_room	*parent;
	struct s_room	*next_q;
	struct s_room	*child;
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
}					t_room;

void	init_queue(t_room **start);
void	enqueue(t_room **start,t_room *r);
t_room	*dequeue(t_room **start);
t_room	*bfs(t_room *list, int *info);