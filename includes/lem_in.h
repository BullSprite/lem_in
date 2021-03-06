/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swynona <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:12:15 by swynona           #+#    #+#             */
/*   Updated: 2020/08/06 22:12:15 by swynona          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/libft.h"

# define MAXINT (1U << 31U) - 1

typedef enum
{
	START,
	INNER,
	END
}	t_type;

typedef struct			s_room
{
	char				*name;
	int					x;
	int					y;
	int					best_path_len;
	struct s_room		*best_child;
	struct s_room		*best_parent;
	struct s_room		*next;
	struct s_room		**linked;
	struct s_room		*parent;
	struct s_room		*bfs_parent;
	struct s_room		*next_q;
	struct s_room		*child;
	struct s_room		*ant_queue;
	int					path_len;
	char				type;
	char				state;
	int					links;
	int					real_len;
	int					idx;
	int					ant;
	int					step;
	int					*capacity;
}						t_room;

typedef struct			s_link
{
	t_room				*from;
	t_room				*where;
	struct s_link		*next;
}						t_link;

typedef struct			s_command
{
	char				*line;
	struct s_command	*next;
}						t_command;

typedef struct			s_farm
{
	int					ants;
	int					ants_at_start;
	int					ants_at_finish;
	int					print;
	int					step;
	t_room				*start;
	t_room				*finish;
	t_room				*rooms;
	t_link				*links;
	t_command			*commands;
}						t_farm;

void					lem_in(void);
t_farm					*input_parse(void);
int						parse_rooms(t_farm *farm, char **line);
int						error_farm(t_farm	*farm);
int						error_rooms(t_farm *farm, char *line);
int						is_int(char **parts, int id);
int						parts_len(char **parts);
int						parse_links(t_farm *farm, char *line, int mode);
int						error_links(t_farm *farm, char *line,
									char *room1, char *room2);
int						make_connections(t_farm *farm);
void					enqueue(t_room **start, t_room *r);
t_room					*dequeue(t_room **start);
t_room					*bfs(t_room *list, t_farm *farm);
t_room					**make_paths(t_room *list, t_farm *farm);
int						string_type(t_farm *farm, char *line);
int						parse_room(t_farm *farm, char *line, int flag);
int						get_cap(t_room *r1, t_room *r2);
int						set_cap(t_room *r1, t_room *r2, int cap);
void					ants_way(t_farm *farm);
void					right_path_len(t_farm *farm);
void					measure_paths(t_room *start, t_farm *farm);
int						get_cap(t_room *r1, t_room *r2);
int						set_cap(t_room *r1, t_room *r2, int cap);
void					clear_state(t_room *l, int flag);
void					init_capacity(t_room *l);
void					print_map(t_command *command);
void					room_init_additional(t_room *room);
#endif
