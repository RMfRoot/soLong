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
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
}   t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
char *file_path(char *action, char *direction, int iteration)
{
    char *path;
    path = my_strjoin("/mnt/c/Users/cuck/Downloads/", action, 0, 0);
    path = my_strjoin(path, "_", 1, 0);
    path = my_strjoin(path, direction, 1, 0);
    path = my_strjoin(path, ft_itoa(iteration), 1, 1);
    path = my_strjoin(path, ".xpm", 1, 0);
    return (path);
}
int main(void)
{
    void *mlx;
    void *mlx_win;
    char *img_path;
    t_data  img;
    int x = 500;
    int y = 500;

    mlx = mlx_init();
    if (!mlx)
        return (1);
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img_path = file_path("standup", "front", 0);
    img.img = mlx_xpm_file_to_image(mlx, img_path, &x, &y);
    if (!img.img)
    {
        perror("Image Path not found");
        return (1);
    }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 500, 500);
    mlx_put_image_to_window(mlx, mlx_win, img.img, 1000, 1000);
	mlx_loop(mlx);
}
