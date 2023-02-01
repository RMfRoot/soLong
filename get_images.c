/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:04:29 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/31 23:39:23 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	malloc_img(t_frames *frames, int i)
{
	frames->img = malloc(sizeof(void *) * i);
	frames->h = malloc(sizeof(int) * i);
	frames->frame_i = 0;
	frames->animation_speed = 0;
	frames->max_frame = i - 1;
}

static void	get_img(t_data *game, t_frames *f, void *mlx, char *sprite_name)
{
	void	*buff;
	char	*p;
	int		i;
	int		j;

	i = -1;
	buff = (void *)1;
	while (buff)
	{
		p = file_path(sprite_name, ++i);
		buff = mlx_xpm_file_to_image(mlx, p, &f->width, &j);
		if (buff)
			mlx_destroy_image(game->mlx, buff);
		free(p);
	}
	if (i == 0)
		parsing_error(game->map.map, -1, -1);
	malloc_img(f, i);
	j = -1;
	while (++j < i)
	{
		p = file_path(sprite_name, j);
		f->img[j] = mlx_xpm_file_to_image(mlx, p, &f->width, &f->h[j]);
		free(p);
	}
}

void	get_images(t_data *game)
{
	get_img(game, &game->player_imgs.stand_s, game->mlx, "stand_S");
	get_img(game, &game->player_imgs.stand_e, game->mlx, "stand_E");
	get_img(game, &game->player_imgs.stand_w, game->mlx, "stand_W");
	get_img(game, &game->player_imgs.stand_n, game->mlx, "stand_N");
	get_img(game, &game->player_imgs.walk_s, game->mlx, "walk_S");
	get_img(game, &game->player_imgs.walk_e, game->mlx, "walk_E");
	get_img(game, &game->player_imgs.walk_w, game->mlx, "walk_W");
	get_img(game, &game->player_imgs.walk_n, game->mlx, "walk_N");
	get_img(game, &game->player_imgs.get_collectible,
		game->mlx, "get_collectible_");
	get_img(game, &game->map.collectible, game->mlx, "collectible_");
	get_img(game, &game->map.grass, game->mlx, "grass_common");
	get_img(game, &game->map.barrier_stick, game->mlx, "wood_stick");
	get_img(game, &game->map.barrier, game->mlx, "wood_barrier");
	get_img(game, &game->map.vertical_barrier, game->mlx, "wood_Nbarrier");
	get_img(game, &game->map.teleport_off, game->mlx, "teleport_off");
	get_img(game, &game->map.teleport_on, game->mlx, "teleport_on");
}
