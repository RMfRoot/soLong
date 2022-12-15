/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soLong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:15:20 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/15 10:41:49 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SOLONG_H
# define SOLONG_H
# include <stdio.h>
# include "libft.h"

typedef struct s_frames{
	void **images;
	int width;
	int *height;
} 	t_frames;

typedef struct s_player{
	t_frames walk_S;
	t_frames walk_E;
	t_frames walk_O;
	t_frames walk_N;
	t_frames stand_S;
	t_frames stand_E;
	t_frames stand_O;
	t_frames stand_N;
} 	t_player;

char *my_strjoin(char *s1, char *s2, int free_s1, int free_s2);
char *file_path(char *action, char *direction, int iteration);
void get_player_img(t_player *player_imgs, void *mlx);

#endif
