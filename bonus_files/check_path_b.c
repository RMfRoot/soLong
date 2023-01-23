/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:27:40 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/22 16:56:07 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_b.h"

t_case	get_direction(t_case start, t_case dest, int pos)
{
	t_case	direction;
	int		toward_y;
	int		toward_x;

	toward_y = dest.y - start.y;
	toward_x = dest.x - start.x;
	direction.y = 0;
	direction.x = 0;
	if (toward_y < 0 && (pos == 0 || pos == 2))
		direction.y = -1;
	else if (pos == 0 || pos == 2)
		direction.y = 1;
	else if (toward_x < 0 && (pos == 1 || pos == 3))
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

bool	find_path(t_map *map, t_case start, t_case dest);

static bool	recur_call(t_map *map, t_case start, t_case dest, t_case direction)
{
	if (map->map[start.y + direction.y][start.x + direction.x] != '1'
		&& map->tried[start.y + direction.y][start.x + direction.x] == false)
	{
		start.y += direction.y;
		start.x += direction.x;
		if (find_path(map, start, dest))
			return (true);
	}
	return (false);
}

bool	find_path(t_map *map, t_case start, t_case dest)
{
	if (start.x == dest.x && start.y == dest.y)
		return (true);
	map->tried[start.y][start.x] = true;
	if (abs(dest.x - start.x) < abs(dest.y - start.y))
	{
		if (recur_call(map, start, dest, get_direction(start, dest, 0)))
			return (true);
		if (recur_call(map, start, dest, get_direction(start, dest, 1)))
			return (true);
		if (recur_call(map, start, dest, get_direction(start, dest, 2)))
			return (true);
		if (recur_call(map, start, dest, get_direction(start, dest, 3)))
			return (true);
	}
	else
	{
		if (recur_call(map, start, dest, get_direction(start, dest, 1)))
			return (true);
		if (recur_call(map, start, dest, get_direction(start, dest, 0)))
			return (true);
		if (recur_call(map, start, dest, get_direction(start, dest, 3))
			|| recur_call(map, start, dest, get_direction(start, dest, 2)))
			return (true);
	}
	return (false);
}

void	find_path_call(t_map *map, t_case start, t_case *dest)
{
	int	i;
	int	y;
	int	x;

	i = 0;
	while (i < map->collectibles_nbr)
	{
		y = -1;
		while (map->map[++y])
		{
			x = -1;
			while (map->map[y][++x])
				map->tried[y][x] = false;
		}
		if (!find_path(map, start, dest[i]))
			parsing_error(map->map, 0, -1);
		i++;
	}
}

void	check_path(t_data *game, t_map *map)
{
	int		y;
	int		x;
	t_case	start;
	t_case	*dest;

	y = -1;
	map->tried = malloc(sizeof(bool **) * game->y.m_len);
	dest = malloc(sizeof(t_case *) * map->collectibles_nbr);
	while (map->map[++y])
	{
		x = -1;
		map->tried[y] = malloc(sizeof(bool *) * game->x.m_len);
		while (map->map[y][++x])
		{
			fill_start(&start, map, x, y);
			fill_dest(dest, map, x, y);
		}
	}
	find_path_call(map, start, dest);
	free(dest);
}
