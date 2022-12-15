/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:04:29 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/15 21:15:56 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "soLong.h"

static void get_img(t_frames *frames, void *mlx, char *action, char *direction)
{
	void *buff;
	char *pathstr;
	int x;
	int i;
	int j;

	x = 0;
	i = 0;
	j = 0;
	buff = (void *)1;
	while (buff)
	{
		pathstr = file_path(action, direction, i);
		printf("%s\n", pathstr);
		buff = mlx_xpm_file_to_image(mlx, pathstr, &frames->width, &x);
		printf("%p\n", buff);
		i++;
	}
	frames->images = malloc(sizeof(void *) * i);
	frames->height = malloc(sizeof(int) * i);
	while (j < i)
	{
		pathstr = file_path(action, direction, j);
		frames->images[j] = mlx_xpm_file_to_image(mlx, pathstr, &frames->width, &frames->height[j]);
		j++;
	}
}

void get_player_img(t_player *player_imgs, void *mlx)
{
	get_img(&player_imgs->stand_S, mlx, "stand", "S");
	get_img(&player_imgs->walk_S, mlx, "walk", "S");
}
