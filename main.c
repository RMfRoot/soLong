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

#include <mlx.h>
#include <stdio.h>
#include "soLong.h"

typedef struct s_data {
    t_player player_imgs;
    void *mlx;
    void *mlx_win;
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    char *pathstr;
    int width;
    int height;
}   t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
int render_next_frame(t_data *img)
{
    static int frame = 0;
    if (!img->player_imgs.walk_S.images[frame])
        frame = 0;
    mlx_put_image_to_window(img->mlx, img->mlx_win, img->player_imgs.walk_S.images[frame], 500, 500 - img->player_imgs.walk_S.height[frame]);
    frame++;
    return (1);
}
int main(void)
{
    t_data  img;

    img.mlx = mlx_init();
    if (!img.mlx)
        return (1);
    get_player_img(&img.player_imgs, img.mlx);
    img.mlx_win = mlx_new_window(img.mlx, 1920, 1080, "Hello world!");
    render_next_frame(&img);
    mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
}
