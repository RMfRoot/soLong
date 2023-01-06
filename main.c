/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:29:54 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/15 10:45:42 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int keyrelease(int keycode, t_data *game)
{
    if (keycode == 0x0057 || keycode == 0x0077)
        game->inputs.W_pressed = false;
    if (keycode == 0x0041 || keycode == 0x0061)
        game->inputs.A_pressed = false;
    if (keycode == 0x0053 || keycode == 0x0073)
        game->inputs.S_pressed = false;
    if (keycode == 0x0044 || keycode == 0x0064)
        game->inputs.D_pressed = false;
    return (1);
}
int keypress(int keycode, t_data *game)
{
    if (keycode == 0x0057 || keycode == 0x0077)
        game->inputs.W_pressed = true;
    if (keycode == 0x0041 || keycode == 0x0061)
        game->inputs.A_pressed = true;
    if (keycode == 0x0053 || keycode == 0x0073)
        game->inputs.S_pressed = true;
    if (keycode == 0x0044 || keycode == 0x0064)
        game->inputs.D_pressed = true;
    return (1);
}
void player_to_window(t_data *game, t_frames frame, bool newframe)
{
    static int i = 0;
    if (i >= frame.max_frame)
        i = 0;
    if (game->window_x/2 > abs(game->map.size_x * 48 - (game->player_x + game->move_x)))
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->player_x + game->move_x - (game->map.size_x * 48 - game->window_x), game->window_y/2 - frame.height[i]);
    else if (game->player_x + game->move_x < game->window_x/2)
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->player_x + game->move_x, game->window_y/2 - frame.height[i]);
    else if (game->window_y/2 > abs(game->map.size_y * 48 - (game->player_y + game->move_y)))
        mlx_put_image_to_window(game->mlx, game->mlx_win,frame.images[i], game->window_x/2, game->player_y + game->move_y - (game->map.size_y * 48 - game->window_y) - frame.height[i]);
    else
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->window_x/2, game->window_y/2 - frame.height[i]);
    game->player_imgs.last_frame = frame;
    if (newframe)
        i++;
}
void map_to_window(t_data *game, t_frames *frame, double x, double y)
{
    if (frame->frame_iteration >= frame->max_frame)
        frame->frame_iteration = 0;
    if (game->window_x/2 > abs(game->map.size_x * 48 - (game->player_x + game->move_x)))
    {
        if (x * 48 < game->map.size_x * 48 - game->window_x - 48 || y * 48 < game->player_y + game->move_y - game->window_y/2 
            || y * 48 > game->window_y/2 + 48 + game->player_y + game->move_y)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 - (game->map.size_x * 48 - game->window_x), y * 48 + (game->window_y/2 - game->player_y) - game->move_y - 48);
    }
    else if (game->player_x + game->move_x - game->window_x/2 < 0)
    {
        if (x * 48 > game->window_x || y * 48 < game->player_y + game->move_y - game->window_y/2 
            || y * 48 > game->window_y/2 + 48 + game->player_y + game->move_y)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48, y * 48 + (game->window_y/2 - game->player_y) - game->move_y - 48);
    }
    else if (game->window_y/2 > abs(game->map.size_y * 48 - (game->player_y + game->move_y + 48)))
    {
        if (y * 48 < game->map.size_y * 48 - game->window_y - 48 || x * 48 < game->player_x + game->move_x - game->window_x/2 
            || x * 48 > game->window_x/2 + 48 + game->player_x + game->move_x)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 + (game->window_x/2 - game->player_x) - game->move_x, y * 48 - (game->map.size_y * 48 - game->window_y));
    }/*
    else if (game->player_y + game->move_y - game->window_y/2 + 48 < 0)
    {
        if (y * 48 > game->window_y + 48 || x * 48 < game->player_x + game->move_x - game->window_x/2 
            || x * 48 > game->window_x/2 + 48 + game->player_x + game->move_x)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 + (game->window_x/2 - game->player_x) + game->move_x, y * 48);
    }*/
    else
    {
        if (x * 48 < game->player_x - 48 + game->move_x - game->window_x/2 || y * 48 < game->player_y + game->move_y - game->window_y/2 
            || x * 48 > game->window_x/2 + game->player_x + game->move_x || y * 48 > game->window_y/2 + 48 + game->player_y + game->move_y)
            return ;
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame->images[frame->frame_iteration], x * 48 + (game->window_x/2 - game->player_x) - game->move_x, y * 48 + (game->window_y/2 - game->player_y) - game->move_y - 48);
    }
    if (++frame->animation_speed > 190)
    {
        frame->frame_iteration++;
        frame->animation_speed = 0;
    }
}
void    print_grass(t_data *game)
{
    int y;
    int x;

    y = -1;
    while (game->map.map[++y])
    {
        x = -1;
        while (game->map.map[y][++x])
            map_to_window(game, &game->map.grass, x, y);
    }
}
void    print_map(t_data *game)
{
    int y;
    int x;

    y = -1;
    while (game->map.map[++y])
    {
        x = -1;
        while (game->map.map[y][++x])
        {
            if (game->map.map[y][x] == '1')
            {
                map_to_window(game, &game->map.barrier_stick, (double)x + 0.25, y);
                if (game->map.map[y][x + 1] == '1')
                    map_to_window(game, &game->map.barrier, (double)x + (double)((double)game->map.barrier_stick.width/48) + 0.25, y);
                if (game->map.map[y + 1] && game->map.map[y + 1][x] == '1')
                    map_to_window(game, &game->map.vertical_barrier, x + 0.25, (double)y + (double)((double)game->map.barrier_stick.width/48));
            }
            else if (game->map.map[y][x] == 'E')
                map_to_window(game, &game->map.teleport_on, x, y);
            else if (game->map.map[y][x] == 'C')
                map_to_window(game, &game->map.collectible, x, y);
        }
    }
}
int render_next_frame(t_data *game)
{
    static int frame_speed = 0;
    mlx_hook(game->mlx_win, 2, 1L<<0, keypress, game);
    mlx_key_hook(game->mlx_win, keyrelease, game);
    get_movement(game);
    print_grass(game);
    print_map(game);
    //screen_border(game, &game->map.border);
    if (frame_speed++ < 100)
    {
        player_to_window(game, game->player_imgs.last_frame, false);
        return (0);
    }
    else if (game->inputs.W_pressed)
    {
        player_to_window(game, game->player_imgs.walk_N, true);
        game->player_imgs.last_direction = game->player_imgs.stand_N;
    }
    else if (game->inputs.A_pressed)
    {
        player_to_window(game,game->player_imgs.walk_W, true);
        game->player_imgs.last_direction = game->player_imgs.stand_W;
    }
    else if (game->inputs.S_pressed)
    {
        player_to_window(game,game->player_imgs.walk_S, true);
        game->player_imgs.last_direction = game->player_imgs.stand_S;
    }
    else if (game->inputs.D_pressed)
    {
        player_to_window(game,game->player_imgs.walk_E, true);
        game->player_imgs.last_direction = game->player_imgs.stand_E;
    }
    else
        player_to_window(game, game->player_imgs.last_direction, true);
    frame_speed = 0;
    return (1);
}
void struct_default(t_data *game)
{
    game->inputs.W_pressed = false;
    game->inputs.A_pressed = false;
    game->inputs.S_pressed = false;
    game->inputs.D_pressed = false;
    game->window_x = 600;
    game->window_y = 600;
    if (game->map.size_y * 48 < 600)
        game->window_y = game->map.size_y * 48;
    if (game->map.size_x * 48 < 600)
        game->window_x = game->map.size_x * 48;
    game->player_imgs.last_direction = game->player_imgs.stand_S;
    game->player_imgs.last_frame = game->player_imgs.stand_S;
    game->move_x = 0;
    game->move_y = 0;
    start_position(game);
}
int main(int argc, char **argv)
{
    t_data  game;

    if (argc != 2)
    {
        printf("Invalid number of arguments");
        return (1);
    }
    game.map = is_map_valid(argv[1]);
    game.mlx = mlx_init();
    if (!game.mlx)
        return (1);
    get_images(&game);
    struct_default(&game);
    game.mlx_win = mlx_new_window(game.mlx, game.window_x, game.window_y, "Hello world!");
    render_next_frame(&game);
    mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);
}
