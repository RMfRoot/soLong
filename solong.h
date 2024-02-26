/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:15:20 by egeorgel          #+#    #+#             */
/*   Updated: 2024/02/26 21:18:04 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H
# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <mlx.h>
# include "libft/libft.h"

typedef struct s_case{
	int	x;
	int	y;
}	t_case;

typedef struct s_frames{
	void	**img;
	int		width;
	int		*h;
	int		frame_i;
	int		animation_speed;
	int		max_frame;
}	t_frames;

typedef struct s_player{
	t_frames	walk_s;
	t_frames	walk_e;
	t_frames	walk_w;
	t_frames	walk_n;
	t_frames	stand_s;
	t_frames	stand_e;
	t_frames	stand_w;
	t_frames	stand_n;
	t_frames	get_collectible;
	t_frames	last_direction;
	t_frames	last_frame;
}	t_player;

typedef struct s_map{
	char		**map;
	bool		**tried;
	int			collectibles_nbr;
	t_frames	grass;
	t_frames	barrier;
	t_frames	vertical_barrier;
	t_frames	barrier_stick;
	t_frames	teleport_off;
	t_frames	teleport_on;
	t_frames	collectible;
	t_frames	border;
}	t_map;

typedef struct s_input{
	bool	w_pressed;
	bool	a_pressed;
	bool	s_pressed;
	bool	d_pressed;
}	t_input;

typedef struct s_axis{
	int		m_len;
	int		w;
	int		player;
	int		move;
}	t_axis;

typedef struct s_data {
	t_input			inputs;
	t_player		player_imgs;
	t_map			map;
	t_axis			x;
	t_axis			y;
	void			*mlx;
	void			*mlx_win;
	unsigned long	step_count;
	bool			teleporter_on;
	bool			game_end;
	bool			sleep;
}	t_data;

char	*my_strjoin(char *s1, char *s2, bool free_s1, bool free_s2);
char	*file_path(char *sprite_name, int iteration);
void	get_images(t_data *game);
int		check_file_type(const char *haystack, const char *needle);
void	is_map_valid(t_data *game, char *map_path);
char	*get_next_line(int fd);
void	parsing_error(char **map, int x, int y);
void	check_path(t_data *game, t_map *map);
void	screen_border(t_data *game, t_frames *border);
void	malloc_img(t_frames *frames, int i);
void	get_movement(t_data *game);
void	start_position(t_data *game);
void	map_to_window(t_data *game, t_frames *frame, double x, double y);
int		end_game(t_data *game);
int		keyrelease(int keycode, t_data *game);
int		keypress(int keycode, t_data *game);
void	print_default(t_data *game, t_frames *frame, double x, double y);
void	print_left_side(t_data *game, t_frames *frame, double x, double y);
void	print_right_side(t_data *game, t_frames *frame, double x, double y);
void	print_top_side(t_data *game, t_frames *frame, double x, double y);
void	print_down_side(t_data *game, t_frames *frame, double x, double y);
void	player_to_window(t_data *g, t_frames f, bool newframe);
void	parcour_map(t_data *game);
void	write_step_count(t_data *game);
void	print_down_left_corner(t_data *g, t_frames *f, double x, double y);
void	exit_interaction(t_data *game);
void	print_grass(t_data *game);
void	player_animation(t_data *game);
void	fill_start(t_case *start, t_map *map, int x, int y);
void	fill_dest(t_case *dest, t_map *map, int x, int y);

#endif
