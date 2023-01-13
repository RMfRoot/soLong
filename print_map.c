/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:27:47 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/13 19:07:46 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void down_side(t_data *game, t_frames *frame, double x, double y)
{
    if (y * 48 > game->y.window || x * 48 < game->x.player + game->x.move - game->x.window/2 - 48
            || x * 48 > game->x.window/2 + game->x.player + game->x.move)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 + (game->x.window/2 - game->x.player) - game->x.move, y * 48);
}

void top_side(t_data *game, t_frames *frame, double x, double y)
{
    if (y * 48 < game->y.map_size * 48 - game->y.window - 48 || x * 48 < game->x.player + game->x.move - game->x.window/2 - 48
            || x * 48 > game->x.window/2 + game->x.player + game->x.move)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 + (game->x.window/2 - game->x.player) - game->x.move, y * 48 - (game->y.map_size * 48 - game->y.window));
}

void right_side(t_data *game, t_frames *frame, double x, double y)
{
    if (x * 48 < game->x.map_size * 48 - game->x.window - 48 || y * 48 < game->y.player + game->y.move - game->y.window/2 - 48
        	|| y * 48 > game->y.window/2 + game->y.player + game->y.move)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 - (game->x.map_size * 48 - game->x.window), y * 48 + (game->y.window/2 - game->y.player) - game->y.move);
}

void left_side(t_data *game, t_frames *frame, double x, double y)
{
   if (x * 48 > game->x.window || y * 48 < game->y.player + game->y.move - game->y.window/2 - 48
            || y * 48 > game->y.window/2 + game->y.player + game->y.move)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48, y * 48 + (game->y.window/2 - game->y.player) - game->y.move);
}

void down_right_corner(t_data *game, t_frames *frame, double x, double y)
{
    if (x * 48 < game->x.map_size * 48 - game->x.window - 48 || y * 48 < game->y.map_size * 48 - game->y.window - 48)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 - (game->x.map_size * 48 - game->x.window), y * 48 - (game->y.map_size * 48 - game->y.window));
}

void up_right_corner(t_data *game, t_frames *frame, double x, double y)
{
    if (x * 48 < game->x.map_size * 48 - game->x.window - 48 || y * 48 > game->y.window)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 - (game->x.map_size * 48 - game->x.window), y * 48);
}

void up_left_corner(t_data *game, t_frames *frame, double x, double y)
{
    if (x * 48 > game->x.window || y * 48 > game->y.window)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48, y * 48);
}

void down_left_corner(t_data *game, t_frames *frame, double x, double y)
{
    if (x * 48 > game->x.window || y * 48 < game->y.map_size * 48 - game->y.window - 48)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48, y * 48 - (game->y.map_size * 48 - game->y.window));
}

void print_default(t_data *game, t_frames *frame, double x, double y)
{
    if (x * 48 < game->x.player + game->x.move - game->x.window/2 - 48 || y * 48 < game->y.player + game->y.move - game->y.window/2 - 48
        || x * 48 > game->x.window/2 + game->x.player + game->x.move || y * 48 > game->y.window/2 + game->y.player + game->y.move)
        return ;
    mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 + (game->x.window/2 - game->x.player) - game->x.move, y * 48 + (game->y.window/2 - game->y.player) - game->y.move);
}

void map_to_window(t_data *game, t_frames *frame, double x, double y)
{
    if (frame->frame_iteration >= frame->max_frame)
        frame->frame_iteration = 0;
    if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)) && game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
        down_right_corner(game, frame, x, y);
    else if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)) && game->y.player + game->y.move - game->y.window/2 < 0)
        up_right_corner(game, frame, x, y);
    else if (game->x.player + game->x.move - game->x.window/2 < 0 && game->y.player + game->y.move - game->y.window/2 < 0)
        up_left_corner(game, frame, x, y);
    else if (game->x.player + game->x.move - game->x.window/2 < 0 && game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
        down_left_corner(game, frame, x, y);
    else if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)))
        right_side(game, frame, x, y);
    else if (game->x.player + game->x.move - game->x.window/2 < 0)
        left_side(game, frame, x, y);
    else if (game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
        top_side(game, frame, x, y);
    else if (game->y.player + game->y.move - game->y.window/2 < 0)
        down_side(game, frame, x, y);
    else
        print_default(game, frame, x, y);
    if (frame->animation_speed++ > 2)
    {
        frame->frame_iteration++;
        frame->animation_speed = 0;
    }
}