/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_fonctions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 16:04:43 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/21 19:11:46 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	print_down_side(t_data *game, t_frames *frame, double x, double y)
{
	int	pos;
	int	img_pos;

	pos = game->x.player + game->x.move;
	img_pos = x * 48 + (game->x.w / 2 - game->x.player) - game->x.move;
	if (y * 48 > game->y.w || x * 48 < pos - game->x.w / 2 - 48
		|| x * 48 > game->x.w / 2 + pos)
		return ;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		frame->img[frame->frame_i], img_pos, y * 48);
}

void	print_top_side(t_data *game, t_frames *frame, double x, double y)
{
	int	pos_x;
	int	img_pos_x;
	int	img_pos_y;

	pos_x = game->x.player + game->x.move;
	img_pos_x = x * 48 + (game->x.w / 2 - game->x.player) - game->x.move;
	img_pos_y = y * 48 - (game->y.m_len * 48 - game->y.w);
	if (y * 48 < game->y.m_len * 48 - game->y.w - 48 || x * 48 < pos_x
		- game->x.w / 2 - 48 || x * 48 > game->x.w / 2 + pos_x)
		return ;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		frame->img[frame->frame_i], img_pos_x, img_pos_y);
}

void	print_right_side(t_data *game, t_frames *frame, double x, double y)
{
	int	pos_y;
	int	img_pos_x;
	int	img_pos_y;

	pos_y = game->y.player + game->y.move;
	img_pos_x = x * 48 - (game->x.m_len * 48 - game->x.w);
	img_pos_y = y * 48 + (game->y.w / 2 - game->y.player) - game->y.move;
	if (x * 48 < game->x.m_len * 48 - game->x.w - 48 || y * 48 < pos_y
		- game->y.w / 2 - 48 || y * 48 > game->y.w / 2 + pos_y)
		return ;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		frame->img[frame->frame_i], img_pos_x, img_pos_y);
}

void	print_left_side(t_data *game, t_frames *frame, double x, double y)
{
	int	pos_y;
	int	img_pos_y;

	pos_y = game->y.player + game->y.move;
	img_pos_y = y * 48 + (game->y.w / 2 - game->y.player) - game->y.move;
	if (x * 48 > game->x.w || y * 48 < pos_y - game->y.w / 2 - 48
		|| y * 48 > game->y.w / 2 + pos_y)
		return ;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		frame->img[frame->frame_i], x * 48, img_pos_y);
}

void	print_default(t_data *game, t_frames *frame, double x, double y)
{
	int	pos_y;
	int	pos_x;
	int	img_pos_x;
	int	img_pos_y;

	pos_x = game->x.player + game->x.move;
	pos_y = game->y.player + game->y.move;
	img_pos_x = x * 48 + (game->x.w / 2 - game->x.player) - game->x.move;
	img_pos_y = y * 48 + (game->y.w / 2 - game->y.player) - game->y.move;
	if (x * 48 < pos_x - game->x.w / 2 - 48 || y * 48 < pos_y
		- game->y.w / 2 - 48 || x * 48 > game->x.w / 2 + pos_x
		|| y * 48 > game->y.w / 2 + pos_y)
		return ;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		frame->img[frame->frame_i], img_pos_x, img_pos_y);
}
