/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:28:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/22 16:56:27 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_b.h"

void	start_position(t_data *game)
{
	int	y;
	int	x;

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

void	fill_get_movement(t_data *g, int x, int y)
{
	if (g->inputs.w_pressed
		&& g->map.map[(g->y.player + g->y.move - 2) / 48][x] != '1')
	{
		if (!((g->x.player + g->x.move) % 48 > 2
				&& g->map.map[(g->y.player + g->y.move - 2) / 48]
				[x + 1] == '1'))
			g->y.move -= 2;
	}
	if (g->inputs.a_pressed
		&& g->map.map[y][(g->x.player + g->x.move - 2) / 48] != '1')
	{
		if (!((g->y.player + g->y.move) % 48 > 2 && g->map.map[y + 1]
				[(g->x.player + g->x.move - 1) / 48] == '1'))
			g->x.move -= 2;
	}
}

void	get_movement(t_data *g)
{
	int	y;
	int	x;
	int	moved_x;
	int	moved_y;

	y = (g->y.player + g->y.move) / 48;
	x = (g->x.player + g->x.move) / 48;
	moved_x = g->x.move;
	moved_y = g->y.move;
	fill_get_movement(g, x, y);
	if (g->inputs.s_pressed && g->map.map[y + 1][x] != '1')
	{
		if (!((g->x.player + g->x.move) % 48 > 2
				&& g->map.map[y + 1][x + 1] == '1'))
			g->y.move += 2;
	}
	if (g->inputs.d_pressed && g->map.map[y][x + 1] != '1')
	{
		if (!((g->y.player + g->y.move) % 48 > 2
				&& g->map.map[y + 1][x + 1] == '1'))
			g->x.move += 2;
	}
	if (g->x.move != moved_x || g->y.move != moved_y)
		g->step_count++;
}
