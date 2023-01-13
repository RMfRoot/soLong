/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:15:20 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/13 19:47:39 by egeorgel         ###   ########.fr       */
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

typedef struct s_frames{
	void **images;
	void **addr;
	int *bits_per_pixel;
	int *line_size;
	int *endian;
	int width;
	int *height;
	int	frame_iteration;
	int animation_speed;
	int max_frame;
} 	t_frames;

typedef struct s_player{
	t_frames walk_S;
	t_frames walk_E;
	t_frames walk_W;
	t_frames walk_N;
	t_frames stand_S;
	t_frames stand_E;
	t_frames stand_W;
	t_frames stand_N;
	t_frames shadow;
	t_frames last_direction;
	t_frames last_frame;
} 	t_player;

typedef struct s_map{
	char **map;
	bool **tried;
	int collectibles_nbr;
	t_frames grass;
	t_frames barrier;
	t_frames vertical_barrier;
	t_frames barrier_stick;
	t_frames teleport_off;
	t_frames teleport_on;
	t_frames collectible;
	t_frames border;
}	t_map;

typedef struct s_input{
    bool W_pressed;
    bool A_pressed;
    bool S_pressed;
    bool D_pressed;
}	t_input;

typedef struct s_axis{
	int map_size;
	int window;
	int player;
	int move;
}	t_axis;

typedef struct s_data {
	t_input inputs;
    t_player player_imgs;
	t_map map;
	t_axis	x;
	t_axis	y;
    void *mlx;
    void *mlx_win;
	bool teleporter_on;
}   t_data;

char *my_strjoin(char *s1, char *s2, bool free_s1, bool free_s2);
char *file_path(char *sprite_name, int iteration);
void get_images(t_data *game);
int	check_file_type(const char *haystack, const char *needle);
void is_map_valid(t_data *game, char *map_path);
char	*get_next_line(int fd);
void	parsing_error(char **map, int x, int y);
void	check_path(t_data *game, t_map *map);
void screen_border(t_data *game, t_frames *border);
void malloc_img(t_frames *frames, int i);
void free_img(t_frames *frames);
int	upper_multiple_of_48(int nbr);
void get_movement(t_data *game);
void start_position(t_data *game);
void map_to_window(t_data *game, t_frames *frame, double x, double y);

#endif
