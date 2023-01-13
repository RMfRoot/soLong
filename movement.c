/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 14:50:38 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/13 19:12:26 by egeorgel         ###   ########.fr       */
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
	int y;
	int x;

	y = (game->y.player + game->y.move) / 48;
	x = (game->x.player + game->x.move) / 48;
	if (game->inputs.W_pressed && game->map.map[(game->y.player + game->y.move - 2) / 48][x] != '1')
	{
		if (!((game->x.player + game->x.move) % 48 > 2 && game->map.map[(game->y.player + game->y.move - 1) / 48][x+1] == '1'))
			game->y.move -= 2;
	}
	if (game->inputs.A_pressed && game->map.map[y][(game->x.player + game->x.move - 2) / 48] != '1')
	{
		if (!((game->y.player + game->y.move) % 48 > 2 && game->map.map[y+1][(game->x.player + game->x.move - 1) / 48] == '1'))
			game->x.move -= 2;
	}
	if (game->inputs.S_pressed && game->map.map[y+1][x] != '1')
	{
		if (!((game->x.player + game->x.move) % 48 > 2 && game->map.map[y+1][x+1] == '1'))
			game->y.move += 2;
	}
	if (game->inputs.D_pressed && game->map.map[y][x+1] != '1')
		if (!((game->y.player + game->y.move) % 48 > 2 && game->map.map[y+1][x+1] == '1'))
			game->x.move += 2;
}