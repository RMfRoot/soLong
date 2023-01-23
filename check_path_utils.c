/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:52:59 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/21 21:46:10 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	fill_start(t_case *start, t_map *map, int x, int y)
{
	if (map->map[y][x] == 'P')
	{
		start->y = y;
		start->x = x;
	}
}

void	fill_dest(t_case *dest, t_map *map, int x, int y)
{
	static int	i = 0;

	if ((map->map[y][x] == 'C' || map->map[y][x] == 'E'))
	{
		dest[i].y = y;
		dest[i].x = x;
		i++;
	}
}
