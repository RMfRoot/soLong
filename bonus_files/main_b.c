/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:28:31 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/31 23:14:48 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_b.h"

bool	no_c_left(t_data *game)
{
	int	y;
	int	x;

	y = -1;
	while (game->map.map[++y])
	{
		x = -1;
		while (game->map.map[y][++x])
			if (game->map.map[y][x] == 'C')
				return (false);
	}
	return (true);
}

void	collectible_interaction(t_data *game)
{
	if (game->map.map[(game->y.player + game->y.move) / 48]
		[(game->x.player + game->x.move + 18) / 48] == 'C')
	{
		game->map.map[(game->y.player + game->y.move) / 48]
		[(game->x.player + game->x.move + 18) / 48] = '0';
		if (no_c_left(game))
			game->teleporter_on = true;
		print_grass(game);
		parcour_map(game);
		write_step_count(game);
		player_to_window(game, game->player_imgs.get_collectible, true);
		game->sleep = true;
	}
}

int	render_next_frame(t_data *game)
{
	if (game->game_end)
	{
		exit_interaction(game);
		return (0);
	}
	if (game->sleep)
		sleep(1);
	game->sleep = false;
	mlx_hook(game->mlx_win, 17, 0L, end_game, game);
	mlx_hook(game->mlx_win, 2, 1L << 0, keypress, game);
	mlx_key_hook(game->mlx_win, keyrelease, game);
	get_movement(game);
	print_grass(game);
	parcour_map(game);
	write_step_count(game);
	player_animation(game);
	collectible_interaction(game);
	exit_interaction(game);
	return (0);
}

void	struct_default(t_data *game)
{
	game->inputs.w_pressed = false;
	game->inputs.a_pressed = false;
	game->inputs.s_pressed = false;
	game->inputs.d_pressed = false;
	game->x.w = 600;
	game->y.w = 600;
	if (game->y.m_len * 48 < 600)
		game->y.w = game->y.m_len * 48;
	if (game->x.m_len * 48 < 600)
		game->x.w = game->x.m_len * 48;
	game->player_imgs.last_direction = game->player_imgs.stand_s;
	game->player_imgs.last_frame = game->player_imgs.stand_s;
	game->x.move = 0;
	game->y.move = 0;
	game->step_count = 0;
	game->teleporter_on = false;
	game->sleep = false;
	game->game_end = false;
	start_position(game);
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
	{
		ft_printf("Invalid number of arguments");
		return (1);
	}
	is_map_valid(&game, argv[1]);
	game.mlx = mlx_init();
	if (!game.mlx)
		return (1);
	get_images(&game);
	struct_default(&game);
	game.mlx_win = mlx_new_window(game.mlx, game.x.w, game.y.w,
			"The legend of Zelda : a link to the past");
	render_next_frame(&game);
	mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);
}
