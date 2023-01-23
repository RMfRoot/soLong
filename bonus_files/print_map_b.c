/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:29:30 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/22 16:56:34 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_b.h"

void	print_down_right_corner(t_data *g, t_frames *f, double x, double y)
{
	int	img_pos_x;
	int	img_py;

	img_pos_x = x * 48 - (g->x.m_len * 48 - g->x.w);
	img_py = y * 48 - (g->y.m_len * 48 - g->y.w);
	if (x * 48 < g->x.m_len * 48 - g->x.w - 48
		|| y * 48 < g->y.m_len * 48 - g->y.w - 48)
		return ;
	mlx_put_image_to_window(g->mlx, g->mlx_win, f->img[f->frame_i],
		img_pos_x, img_py);
}

void	print_up_right_corner(t_data *g, t_frames *frame, double x, double y)
{
	int	img_pos_x;

	img_pos_x = x * 48 - (g->x.m_len * 48 - g->x.w);
	if (x * 48 < g->x.m_len * 48 - g->x.w - 48
		|| y * 48 > g->y.w)
		return ;
	mlx_put_image_to_window(g->mlx, g->mlx_win,
		frame->img[frame->frame_i], img_pos_x, y * 48);
}

void	print_up_left_corner(t_data *g, t_frames *frame, double x, double y)
{
	if (x * 48 > g->x.w || y * 48 > g->y.w)
		return ;
	mlx_put_image_to_window(g->mlx, g->mlx_win,
		frame->img[frame->frame_i], x * 48, y * 48);
}

static void	frames(t_frames *frame)
{
	if (frame->animation_speed++ > 2)
	{
		if (frame->frame_i >= frame->max_frame)
			frame->frame_i = 0;
		else
			frame->frame_i++;
		frame->animation_speed = 0;
	}
}

void	map_to_window(t_data *g, t_frames *frame, double x, double y)
{
	int	px;
	int	py;

	px = g->x.player + g->x.move;
	py = g->y.player + g->y.move;
	if (g->x.w / 2 > abs(g->x.m_len * 48 - px)
		&& g->y.w / 2 > abs(g->y.m_len * 48 - py))
		print_down_right_corner(g, frame, x, y);
	else if (g->x.w / 2 > abs(g->x.m_len * 48 - px) && py - g->y.w / 2 < 0)
		print_up_right_corner(g, frame, x, y);
	else if (px - g->x.w / 2 < 0 && py - g->y.w / 2 < 0)
		print_up_left_corner(g, frame, x, y);
	else if (px - g->x.w / 2 < 0 && g->y.w / 2 > abs(g->y.m_len * 48 - py))
		print_down_left_corner(g, frame, x, y);
	else if (g->x.w / 2 > abs(g->x.m_len * 48 - px))
		print_right_side(g, frame, x, y);
	else if (px - g->x.w / 2 < 0)
		print_left_side(g, frame, x, y);
	else if (g->y.w / 2 > abs(g->y.m_len * 48 - py))
		print_top_side(g, frame, x, y);
	else if (py - g->y.w / 2 < 0)
		print_down_side(g, frame, x, y);
	else
		print_default(g, frame, x, y);
	frames(frame);
}
