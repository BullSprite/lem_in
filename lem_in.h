#include "libft/libft.h"

typedef struct		s_room
{
	char			*name;
	int				x;
	int 			y;
	char			type;
	char			state;
	int				level;
	int 			output_count;
	int 			input_count;
	struct s_room	*next;
	struct s_room	*next_q;
	int 			q_len;
}					t_room;