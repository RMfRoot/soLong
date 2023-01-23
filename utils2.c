/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:10:04 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/23 19:24:54 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	end_game(t_data *game)
{
	game->map.map[0][0] = '1';
	exit(EXIT_SUCCESS);
}

void	exit_interaction(t_data *game)
{
	if (game->map.map[(game->y.player + game->y.move + 25) / 48]
		[(game->x.player + game->x.move) / 48] == 'E' && game->teleporter_on)
	{
		print_grass(game);
		parcour_map(game);
		mlx_string_put(game->mlx, game->mlx_win, game->x.w / 2 - 50,
			game->y.w / 2 - 10, 0x00FFFFFF, "You Won !");
		if (game->x.w < (int)ft_strlen("Press Esc to quit") * 10)
		{
			mlx_string_put(game->mlx, game->mlx_win, game->x.w / 2 - 50,
				game->y.w / 2 + 10, 0x00FFFFFF, "Press Esc");
			mlx_string_put(game->mlx, game->mlx_win, game->x.w / 2 - 50,
				game->y.w / 2 + 30, 0x00FFFFFF, " to quit");
		}
		else
			mlx_string_put(game->mlx, game->mlx_win, game->x.w / 2 - 90,
				game->y.w / 2 + 10, 0x00FFFFFF, "Press Esc to quit");
		game->game_end = true;
	}
}
