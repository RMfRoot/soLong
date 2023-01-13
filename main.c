/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:29:54 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/13 19:09:21 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int keyrelease(int keycode, t_data *game)
{
    if (keycode == 13)
        game->inputs.W_pressed = false;
    if (keycode == 0)
        game->inputs.A_pressed = false;
    if (keycode == 1)
        game->inputs.S_pressed = false;
    if (keycode == 2)
        game->inputs.D_pressed = false;
    return (1);
}
int keypress(int keycode, t_data *game)
{
    if (keycode == 13)
        game->inputs.W_pressed = true;
    if (keycode == 0)
        game->inputs.A_pressed = true;
    if (keycode == 1)
        game->inputs.S_pressed = true;
    if (keycode == 2)
        game->inputs.D_pressed = true;
    return (1);
}
void player_to_window(t_data *game, t_frames frame, bool newframe)
{
    static int i = 0;
    if (i >= frame.max_frame)
        i = 0;
    if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)) && game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->x.player + game->x.move - (game->x.map_size * 48 - game->x.window), game->y.player + game->y.move - (game->y.map_size * 48 - game->y.window) - (frame.height[i] - 50));
    else if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)) && game->y.player + game->y.move < game->y.window/2)
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->x.player + game->x.move - (game->x.map_size * 48 - game->x.window), game->y.player + game->y.move - (frame.height[i] - 50));
    else if (game->x.player + game->x.move < game->x.window/2 && game->y.player + game->y.move < game->y.window/2)
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i],  game->x.player + game->x.move, game->y.player + game->y.move - (frame.height[i] - 50));
    else if (game->x.player + game->x.move < game->x.window/2 && game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i],  game->x.player + game->x.move, game->y.player + game->y.move - (game->y.map_size * 48 - game->y.window) - (frame.height[i] - 50));
    else if (game->x.window/2 > abs(game->x.map_size * 48 - (game->x.player + game->x.move)))
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->x.player + game->x.move - (game->x.map_size * 48 - game->x.window), game->y.window/2 - (frame.height[i] - 50));
    else if (game->x.player + game->x.move < game->x.window/2)
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->x.player + game->x.move, game->y.window/2 - (frame.height[i] - 50));
    else if (game->y.window/2 > abs(game->y.map_size * 48 - (game->y.player + game->y.move)))
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->x.window/2, game->y.player + game->y.move - (game->y.map_size * 48 - game->y.window) - (frame.height[i] - 50));
    else if (game->y.player + game->y.move < game->y.window/2)
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->x.window/2, game->y.player + game->y.move - (frame.height[i] - 50));
    else
        mlx_put_image_to_window(game->mlx, game->mlx_win, frame.images[i], game->x.window/2, game->y.window/2 - (frame.height[i] - 50));
    game->player_imgs.last_frame = frame;
    if (newframe)
        i++;
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
                map_to_window(game, &game->map.collectible, (double)x + 0.2, y);
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
    if (frame_speed++ < 3)
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
    game->x.window = 600;
    game->y.window = 600;
    if (game->y.map_size * 48 < 600)
        game->y.window = game->y.map_size * 48;
    if (game->x.map_size * 48 < 600)
        game->x.window = game->x.map_size * 48;
    game->player_imgs.last_direction = game->player_imgs.stand_S;
    game->player_imgs.last_frame = game->player_imgs.stand_S;
    game->x.move = 0;
    game->y.move = 0;
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
    is_map_valid(&game, argv[1]);
    game.mlx = mlx_init();
    if (!game.mlx)
        return (1);
    get_images(&game);
    struct_default(&game);
    game.mlx_win = mlx_new_window(game.mlx, game.x.window, game.y.window, "Hello world!");
    render_next_frame(&game);
    mlx_loop_hook(game.mlx, render_next_frame, &game);
	mlx_loop(game.mlx);
}
