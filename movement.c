/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:50:38 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/01 14:50:41 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "solong.h"

void start_position(t_data *game)
{
	int y;
	int x;

	y = -1;
	while (game->map.map[++y])
	{
		x = -1;
		while (game->map.map[y][++x])
		{
			if (game->map.map[y][x] == 'P')
			{
				game->x.player = x * 48;
				game->y.player = y * 48;
				return ;
			}
		}
		
	}
}

void get_movement(t_data *game)
{
	static int character_speed = 0;
	int y;
	int x;

	y = (game->y.player + game->y.move) / 48;
	x = (game->x.player + game->x.move) / 48;
	if (++character_speed < 5)
		return ;
	character_speed = 0;
	if (game->inputs.W_pressed && game->map.map[(game->y.player + game->y.move - 1) / 48][x] != '1')
		game->y.move--;
	if (game->inputs.A_pressed && game->map.map[y][(game->x.player + game->x.move - 1) / 48] != '1')
		game->x.move--;
	if (game->inputs.S_pressed && game->map.map[y+1][x] != '1')
		game->y.move++;
	if (game->inputs.D_pressed && game->map.map[y][x+1] != '1')
		game->x.move++;
}
//fix x++ on map.ber, if 1 pixel higher, will walk on barrier.
void get_border(t_data *game, t_frames *border)
{	
	malloc_img(border, 2);
	*border->images = mlx_new_image(game->mlx, game->x.map_size * 48, game->y.map_size * 48);
	*border->addr = mlx_get_data_addr(*border->images, border->bits_per_pixel, border->line_size, border->endian);
}
void screen_border(t_data *game, t_frames *border)
{
	static bool first = true;
	int y;
	int x;
	char	*dst;

	y = -1;
	if (first)
	{
		get_border(game, border);
		first = false;
	}
	while (++y < game->y.window + game->y.player)
	{
		x = game->x.player + game->x.window - 1;
		while (++x > game->x.window + game->x.player && x < upper_multiple_of_48(game->x.window + game->x.player))
		{
			dst = *border->addr + (y * *border->line_size + x * (*border->bits_per_pixel / 8));
			*(unsigned int*)dst = 0xFF000000;
		}
	}
	y = game->y.player + game->y.window - 1;
	while (++y > game->y.window + game->y.player && x < upper_multiple_of_48(game->y.window + game->y.player))
	{
		x = -1;
		while (++x < game->y.window + game->y.player)
		{
			dst = *border->addr + (y * *border->line_size + x * (*border->bits_per_pixel / 8));
			*(unsigned int*)dst = 0xFF000000;
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, *border->images, 0, 0);
}
