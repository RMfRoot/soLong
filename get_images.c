/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:04:29 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/15 21:15:56 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "solong.h"

void malloc_img(t_frames *frames, int i)
{
	frames->images = malloc(sizeof(void *) * i);
	frames->height = malloc(sizeof(int) * i);
	frames->bits_per_pixel = malloc(sizeof(int) * i);
	frames->line_size = malloc(sizeof(int) * i);
	frames->endian = malloc(sizeof(int) * i);
	frames->addr = malloc(sizeof(void *) * i);
	frames->frame_iteration = 0;
	frames->animation_speed = 0;
}
static void get_img(t_frames *frames, void *mlx, char *sprite_name)
{
	void *buff;
	char *pathstr;
	int x;
	int i;
	int j;

	x = 0;
	i = 0;
	j = 0;
	buff = (void *)1;
	while (buff)
	{
		pathstr = file_path(sprite_name, i);
		buff = mlx_xpm_file_to_image(mlx, pathstr, &frames->width, &x);
		i++;
	}
	malloc_img(frames, i);
	while (j < i)
	{
		pathstr = file_path(sprite_name, j);
		frames->images[j] = mlx_xpm_file_to_image(mlx, pathstr, &frames->width, &frames->height[j]);
		j++;
	}
	frames->max_frame = j - 1;
}

void get_images(t_data *game)
{
	get_img(&game->player_imgs.stand_S, game->mlx, "stand_S");
	get_img(&game->player_imgs.stand_E, game->mlx, "stand_E");
	get_img(&game->player_imgs.stand_W, game->mlx, "stand_W");
	get_img(&game->player_imgs.stand_N, game->mlx, "stand_N");
	get_img(&game->player_imgs.walk_S, game->mlx, "walk_S");
	get_img(&game->player_imgs.walk_E, game->mlx, "walk_E");
	get_img(&game->player_imgs.walk_W, game->mlx, "walk_W");
	get_img(&game->player_imgs.walk_N, game->mlx, "walk_N");
	get_img(&game->player_imgs.shadow, game->mlx, "shadow");
	get_img(&game->map.collectible, game->mlx, "collectible_");
	get_img(&game->map.grass, game->mlx, "grass_common");
	get_img(&game->map.barrier_stick, game->mlx, "wood_stick");
	get_img(&game->map.barrier, game->mlx, "wood_barrier");
	get_img(&game->map.vertical_barrier, game->mlx, "wood_Nbarrier");
	get_img(&game->map.teleport_off, game->mlx, "teleport_off");
	get_img(&game->map.teleport_on, game->mlx, "teleport_on");
}
