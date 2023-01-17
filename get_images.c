/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:04:29 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/17 21:32:47 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "solong.h"

void malloc_img(t_frames *frames, int i)
{
	frames->images = malloc(sizeof(void *) * i);
	frames->height = malloc(sizeof(int) * i);
	frames->frame_iteration = 0;
	frames->animation_speed = 0;
}
static void get_img(t_data *game, t_frames *frames, void *mlx, char *sprite_name)
{
	void *buff;
	char *pathstr;
	int i;
	int j;

	i = -1;
	j = 0;
	buff = (void *)1;
	while (buff)
	{
		pathstr = file_path(sprite_name, ++i);
		buff = mlx_xpm_file_to_image(mlx, pathstr, &frames->width, &j);
		if (buff)
			mlx_destroy_image(game->mlx, buff);
		free(pathstr);
	}
	malloc_img(frames, i);
	j = -1;
	while (++j < i)
	{
		pathstr = file_path(sprite_name, j);
		frames->images[j] = mlx_xpm_file_to_image(mlx, pathstr, &frames->width, &frames->height[j]);
		free(pathstr);
	}
	frames->max_frame = j - 1;
}

void get_images(t_data *game)
{
	get_img(game, &game->player_imgs.stand_S, game->mlx, "stand_S");
	get_img(game, &game->player_imgs.stand_E, game->mlx, "stand_E");
	get_img(game, &game->player_imgs.stand_W, game->mlx, "stand_W");
	get_img(game, &game->player_imgs.stand_N, game->mlx, "stand_N");
	get_img(game, &game->player_imgs.walk_S, game->mlx, "walk_S");
	get_img(game, &game->player_imgs.walk_E, game->mlx, "walk_E");
	get_img(game, &game->player_imgs.walk_W, game->mlx, "walk_W");
	get_img(game, &game->player_imgs.walk_N, game->mlx, "walk_N");
	get_img(game, &game->player_imgs.get_collectible, game->mlx, "get_collectible_");
	get_img(game, &game->player_imgs.shadow, game->mlx, "shadow");
	get_img(game, &game->map.collectible, game->mlx, "collectible_");
	get_img(game, &game->map.grass, game->mlx, "grass_common");
	get_img(game, &game->map.barrier_stick, game->mlx, "wood_stick");
	get_img(game, &game->map.barrier, game->mlx, "wood_barrier");
	get_img(game, &game->map.vertical_barrier, game->mlx, "wood_Nbarrier");
	get_img(game, &game->map.teleport_off, game->mlx, "teleport_off");
	get_img(game, &game->map.teleport_on, game->mlx, "teleport_on");
}
