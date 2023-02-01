/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_player_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:29:43 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/31 23:49:57 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_b.h"

bool	fill_player_to_window(t_data *g, t_frames f, int i)
{
	int			px;
	int			py;

	px = g->x.player + g->x.move;
	py = g->y.player + g->y.move;
	if (g->x.w / 2 > abs(g->x.m_len * 48 - px)
		&& g->y.w / 2 > abs(g->y.m_len * 48 - py))
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i], px - (g->x.m_len
				* 48 - g->x.w), py - (g->y.m_len * 48 - g->y.w)
			- (f.h[i] - 50));
	else if (g->x.w / 2 > abs(g->x.m_len * 48 - px) && py < g->y.w / 2)
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i], px - (g->x.m_len
				* 48 - g->x.w), py - (f.h[i] - 50));
	else if (px < g->x.w / 2 && py < g->y.w / 2)
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i], px, py
			- (f.h[i] - 50));
	else if (px < g->x.w / 2 && g->y.w / 2 > abs(g->y.m_len * 48 - py))
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i], px, py
			- (g->y.m_len * 48 - g->y.w) - (f.h[i] - 50));
	else if (g->x.w / 2 > abs(g->x.m_len * 48 - px))
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i], px
			- (g->x.m_len * 48 - g->x.w), g->y.w / 2 - (f.h[i] - 50));
	else
		return (true);
	return (false);
}

void	player_to_window(t_data *g, t_frames f, bool newframe)
{
	static int	i = 0;
	int			px;
	int			py;
	bool		b;

	px = g->x.player + g->x.move;
	py = g->y.player + g->y.move;
	if (i >= f.max_frame)
		i = 0;
	b = fill_player_to_window(g, f, i);
	if (b && px < g->x.w / 2)
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i],
			px, g->y.w / 2 - (f.h[i] - 50));
	else if (b && g->y.w / 2 > abs(g->y.m_len * 48 - py))
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i],
			g->x.w / 2, py - (g->y.m_len * 48 - g->y.w) - (f.h[i] - 50));
	else if (b && py < g->y.w / 2)
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i],
			g->x.w / 2, py - (f.h[i] - 50));
	else if (b)
		mlx_put_image_to_window(g->mlx, g->mlx_win, f.img[i],
			g->x.w / 2, g->y.w / 2 - (f.h[i] - 50));
	g->player_imgs.last_frame = f;
	if (newframe)
		i++;
}

static void	fill_player_animation(t_data *game)
{
	player_to_window(game, game->player_imgs.walk_n, true);
	game->player_imgs.last_direction = game->player_imgs.stand_n;
}

static void	fill_player_animation2(t_data *game)
{
	player_to_window(game, game->player_imgs.walk_w, true);
	game->player_imgs.last_direction = game->player_imgs.stand_w;
}

void	player_animation(t_data *game)
{
	static int	frame_speed = 0;

	if (frame_speed++ < 3)
	{
		player_to_window(game, game->player_imgs.last_frame, false);
		return ;
	}
	else if (game->inputs.w_pressed)
		fill_player_animation(game);
	else if (game->inputs.a_pressed)
		fill_player_animation2(game);
	else if (game->inputs.s_pressed)
	{
		player_to_window(game, game->player_imgs.walk_s, true);
		game->player_imgs.last_direction = game->player_imgs.stand_s;
	}
	else if (game->inputs.d_pressed)
	{
		player_to_window(game, game->player_imgs.walk_e, true);
		game->player_imgs.last_direction = game->player_imgs.stand_e;
	}
	else
		player_to_window(game, game->player_imgs.last_direction, true);
	frame_speed = 0;
}
