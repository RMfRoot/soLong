/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcour_map_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:29:00 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/22 16:56:31 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_b.h"

static void	fill_parcour_map(t_data *game, int x, int y)
{
	if (game->map.map[y][x] == '1')
	{
		map_to_window(game, &game->map.barrier_stick, (double)x + 0.25, y);
		if (game->map.map[y][x + 1] == '1')
			map_to_window(game, &game->map.barrier, (double)x + (double)
				((double)game->map.barrier_stick.width / 48) + 0.25, y);
		if (game->map.map[y + 1] && game->map.map[y + 1][x] == '1')
			map_to_window(game, &game->map.vertical_barrier, x + 0.25, (double)y
				+ (double)((double)game->map.barrier_stick.width / 48));
	}
	else if (game->map.map[y][x] == 'E')
	{
		if (game->teleporter_on)
			map_to_window(game, &game->map.teleport_on, x, y);
		else
			map_to_window(game, &game->map.teleport_off, x, y);
	}
	else if (game->map.map[y][x] == 'C')
		map_to_window(game, &game->map.collectible, (double)x + 0.2, y);
}

void	parcour_map(t_data *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map.map[++y])
	{
		x = -1;
		while (game->map.map[y][++x])
			fill_parcour_map(game, x, y);
	}
}

void	print_grass(t_data *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map.map[++y])
	{
		x = -1;
		while (game->map.map[y][++x])
			map_to_window(game, &game->map.grass, x, y);
	}
}

void	print_down_left_corner(t_data *g, t_frames *f, double x, double y)
{
	if (x * 48 > g->x.w
		|| y * 48 < g->y.m_len * 48 - g->y.w - 48)
		return ;
	mlx_put_image_to_window(g->mlx, g->mlx_win, f->img[f->frame_i],
		x * 48, y * 48 - (g->y.m_len * 48 - g->y.w));
}
