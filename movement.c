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
				game->player_x = x * 48;
				game->player_y = y * 48;
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

	y = (game->player_y + game->move_y) / 48;
	x = (game->player_x + game->move_x) / 48;
	if (++character_speed < 5)
		return ;
	character_speed = 0;
	if (game->inputs.W_pressed && game->map.map[(game->player_y + game->move_y - 1) / 48][x] != '1')
		game->move_y--;
	if (game->inputs.A_pressed && game->map.map[y][(game->player_x + game->move_x - 1) / 48] != '1')
		game->move_x--;
	if (game->inputs.S_pressed && game->map.map[y+1][x] != '1')
		game->move_y++;
	if (game->inputs.D_pressed && game->map.map[y][x+1] != '1')
		game->move_x++;
}
void get_border(t_data *game, t_frames *border)
{	
	malloc_img(border, 2);
	*border->images = mlx_new_image(game->mlx, game->map.size_x * 48, game->map.size_y * 48);
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
	while (++y < game->window_y + game->player_y)
	{
		x = game->player_x + game->window_x - 1;
		while (++x > game->window_x + game->player_x && x < upper_multiple_of_48(game->window_x + game->player_x))
		{
			dst = *border->addr + (y * *border->line_size + x * (*border->bits_per_pixel / 8));
			*(unsigned int*)dst = 0xFF000000;
		}
	}
	y = game->player_y + game->window_y - 1;
	while (++y > game->window_y + game->player_y && x < upper_multiple_of_48(game->window_y + game->player_y))
	{
		x = -1;
		while (++x < game->window_y + game->player_y)
		{
			dst = *border->addr + (y * *border->line_size + x * (*border->bits_per_pixel / 8));
			*(unsigned int*)dst = 0xFF000000;
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, *border->images, 0, 0);
}
