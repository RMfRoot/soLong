/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 16:27:47 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/07 16:27:54 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

typedef struct s_fill{
    t_frames *frame;
	bool top;
	double x;
	double y;
}	t_fill;


void	print_map_sides_x(t_data *game, t_axis x, t_axis y, t_fill fill)
{
	if (fill.top)
	{
        if (fill.x * 48 < x.map_size * 48 - x.window - 48 || fill.y * 48 < y.player + y.move - y.window/2 - 48
        	    || fill.y * 48 > y.window/2 + y.player + y.move)
        	return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, fill.frame->images[fill.frame->frame_iteration], fill.x * 48 - (x.map_size * 48 - x.window), fill.y * 48 + (y.window/2 - y.player) - y.move);
	}
	else
	{
        if (fill.x * 48 > x.window || fill.y * 48 < y.player + y.move - y.window/2 - 48
                || fill.y * 48 > y.window/2 + y.player + y.move)
            return ;
    	mlx_put_image_to_window(game->mlx, game->mlx_win, fill.frame->images[fill.frame->frame_iteration], fill.x * 48, fill.y * 48 + (y.window/2 - y.player) - y.move);
    }
}
void	print_map_sides_y(t_data *game, t_axis x, t_axis y, t_fill fill)
{
	if (fill.top)
	{
        if (fill.y * 48 < y.map_size * 48 - y.window - 48 || fill.x * 48 < x.player + x.move - x.window/2 - 48
                || fill.x * 48 > x.window/2 + x.player + x.move)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, fill.frame->images[fill.frame->frame_iteration], fill.x * 48 + (x.window/2 - x.player) - x.move, fill.y * 48 - (y.map_size * 48 - y.window));
    }
	else
	{
        if (fill.y * 48 > y.window || fill.x * 48 < x.player + x.move - x.window/2 - 48
                || fill.x * 48 > x.window/2 + x.player + x.move)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, fill.frame->images[fill.frame->frame_iteration], fill.x * 48 + (x.window/2 - x.player) - x.move, fill.y * 48);
	}
}

void map_to_window(t_data *game, t_frames *frame, double x, double y)
{
    t_fill fill = {.frame = frame, .top = true, .x = x, .y = y};

    if (frame->frame_iteration >= frame->max_frame)
        frame->frame_iteration = 0;
    if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)) && game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
    {
        if (x * 48 < game->x.map_size * 48 - game->x.window - 48 || y * 48 < game->y.map_size * 48 - game->y.window - 48)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 - (game->x.map_size * 48 - game->x.window), y * 48 - (game->y.map_size * 48 - game->y.window));
    }
    else if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)) && game->y.player + game->y.move - game->y.window/2 < 0)
    {
        if (x * 48 < game->x.map_size * 48 - game->x.window - 48 || y * 48 > game->y.window)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 - (game->x.map_size * 48 - game->x.window), y * 48);
    }
    else if (game->x.player + game->x.move - game->x.window/2 < 0 && game->y.player + game->y.move - game->y.window/2 < 0)
    {
        if (x * 48 > game->x.window || y * 48 > game->y.window)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48, y * 48);
    }
    else if (game->x.player + game->x.move - game->x.window/2 < 0 && game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
    {
        if (x * 48 > game->x.window || y * 48 < game->y.map_size * 48 - game->y.window - 48)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48, y * 48 - (game->y.map_size * 48 - game->y.window));
    }
    else if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)))
        print_map_sides_x(game, game->x, game->y, fill);
    else if (game->x.player + game->x.move - game->x.window/2 < 0)
    {
        fill.top = false;
        print_map_sides_x(game, game->x, game->y, fill);
    }
    else if (game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
        print_map_sides_y(game, game->x, game->y, fill);
    else if (game->y.player + game->y.move - game->y.window/2 < 0)
    {
        fill.top = false;
        print_map_sides_y(game, game->x, game->y, fill);
    }
    else
    {
        if (x * 48 < game->x.player + game->x.move - game->x.window/2 - 48 || y * 48 < game->y.player + game->y.move - game->y.window/2 - 48
            || x * 48 > game->x.window/2 + game->x.player + game->x.move || y * 48 > game->y.window/2 + game->y.player + game->y.move)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 + (game->x.window/2 - game->x.player) - game->x.move, y * 48 + (game->y.window/2 - game->y.player) - game->y.move);
    }
    if (++frame->animation_speed > 5)
    {
        frame->frame_iteration++;
        frame->animation_speed = 0;
    }
}
