/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:56:03 by egeorgel          #+#    #+#             */
/*   Updated: 2024/02/26 21:37:21 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static char	**get_map_lines(int fd)
{
	char	*line;
	char	*map;
	char	**res;

	map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		map = my_strjoin(map, line, true, true);
		line = get_next_line(fd);
	}
	close(fd);
	if (map)
	{
		res = ft_split(map, '\n');
		free(map);
		return (res);
	}
	ft_printf("Empty map");
	exit(EXIT_SUCCESS);
}

static char	**get_map(char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (!check_file_type(map_path, ".ber"))
		ft_printf("Invalid file type");
	else if (fd == -1)
		ft_printf("Invalid map path");
	else
		return (get_map_lines(fd));
	exit(EXIT_SUCCESS);
}

void	parsing_error(char **map, int x, int y)
{
	int	i;

	i = -1;
	if (x == -1 && y == -1)
	{
		ft_printf("could not access image files\n");
		exit(EXIT_SUCCESS);
	}
	while (map[++i])
		ft_printf("%d\t%s\n", i, map[i]);
	if (x == -1 && y == 0)
		ft_printf("\n missing P\\E\\C");
	else if (x == 0 && y == -1)
		ft_printf("path to exit or collectible is invalid");
	else
		ft_printf("\nparsing error at x=%d y=%d", x, y);
	exit(EXIT_SUCCESS);
}

static int	check_map(t_map *map, int *y, bool p, bool e)
{
	int	x;

	while (map->map[++(*y)])
	{
		x = -1;
		while (map->map[*y][++x])
		{
			if (map->map[*y][x] != '1' && (x - 1 < 0 || !map->map[*y][x + 1]
				|| *y - 1 < 0 || !map->map[*y + 1][x]))
				parsing_error(map->map, x, *y);
			if (!ft_strchr("01CEP", map->map[*y][x]))
				parsing_error(map->map, x, *y);
			if ((p && map->map[*y][x] == 'P') || (e && map->map[*y][x] == 'E'))
				parsing_error(map->map, x, *y);
			if (map->map[*y][x] == 'P')
				p = true;
			if (map->map[*y][x] == 'E')
				e = true;
			if (map->map[*y][x] == 'C')
				map->collectibles_nbr++;
		}
	}
	if (!(e && p && map->collectibles_nbr != 0))
		parsing_error(map->map, -1, 0);
	return (x);
}

void	is_map_valid(t_data *game, char *map_path)
{
	t_map	map;
	int		y;
	bool	p;
	bool	e;

	p = false;
	e = false;
	y = -1;
	map.collectibles_nbr = 0;
	map.map = get_map(map_path);
	game->x.m_len = check_map(&map, &y, p, e);
	game->y.m_len = y;
	map.collectibles_nbr++;
	check_path(game, &map);
	game->map = map;
}
