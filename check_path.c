/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:48:11 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/27 14:48:14 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

typedef struct s_case{
	int x;
	int y;
}	t_case;

t_case	get_direction(t_case start, t_case dest, int pos)
{
	t_case direction;
	int towardY = dest.y - start.y;
	int towardX = dest.x - start.x;

	direction.y = 0;
	direction.x = 0;
    if (towardY < 0 && (pos == 0 || pos == 2))
		direction.y = -1;
    else if (pos == 0 || pos == 2)
		direction.y = 1;
    else if (towardX < 0 && (pos == 1 || pos == 3))
		direction.x = -1;
    else if (pos == 1 || pos == 3)
		direction.x = 1;
	if (pos == 2 || pos == 3)
	{
		direction.x *= -1;
		direction.y *= -1;
	}
	return (direction);
}
bool find_path(t_map *map, t_case start, t_case dest);
static bool recur_call(t_map *map, t_case start, t_case dest, t_case direction)
{
	if (map->map[start.y + direction.y][start.x + direction.x] != '1' && map->tried[start.y + direction.y][start.x + direction.x] == false)
	{
		start.y += direction.y;
		start.x += direction.x;
    	if (find_path(map, start, dest))
        	return true;
	}
	return (false);
}
bool find_path(t_map *map, t_case start, t_case dest)
{
	if (start.x == dest.x && start.y == dest.y)
        return true;
    map->tried[start.y][start.x] = true;
    if (abs(dest.x - start.x) < abs(dest.y - start.y))
    {
        if (recur_call(map, start, dest, get_direction(start, dest, 0)))
            return true;
        if (recur_call(map, start, dest, get_direction(start, dest, 1)))
            return true;
        if (recur_call(map, start, dest, get_direction(start, dest, 2)))
            return true;
        if (recur_call(map, start, dest, get_direction(start, dest, 3)))
            return true;
        return false;
    }
    else
    {
        if (recur_call(map, start, dest, get_direction(start, dest, 1)))
            return true;
        if (recur_call(map, start, dest, get_direction(start, dest, 0)))
            return true;
        if (recur_call(map, start, dest, get_direction(start, dest, 3)))
            return true;
        if (recur_call(map, start, dest, get_direction(start, dest, 2)))
            return true;
        return false;
    }
}
void	find_path_call(t_map *map, t_case start, t_case *dest)
{
	int i;

	i = 0;
	while (i < map->collectibles_nbr)
	{
		if (!find_path(map, start, dest[i]))
			parsing_error(map->map, 0, -1);
		i++;
	}
}
void	check_path(t_data *game, t_map *map)
{
	int y;
	int x;
	int dest_count;
	t_case start;
	t_case *dest;

	y = -1;
	dest_count = 0;
	map->tried = malloc(sizeof(bool **) * game->y.map_size);
	dest = malloc(sizeof(t_case *) * map->collectibles_nbr);
	while (map->map[++y])
	{
		x = -1;
		map->tried[y] = malloc(sizeof(bool *) * game->x.map_size);
		while (map->map[y][++x])
		{
			map->tried[y][x] = false;
			if (map->map[y][x] == 'P')
			{
				start.y = y;
				start.x = x;
			}
			else if (map->map[y][x] == 'C' || map->map[y][x] == 'E')
			{
				dest[dest_count].y = y;
				dest[dest_count].x = x;
				dest_count++;
			}
		}
	}
	find_path_call(map, start, dest);
}