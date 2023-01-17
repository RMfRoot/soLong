/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:56:03 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/17 22:07:26 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

static char	**get_map(char *map_path)
{
	int fd;
	char **res;
	char *map;
	char *line;

	map = NULL;
	if (!check_file_type(map_path, ".ber"))
	{
		printf("Invalid file type");
		exit(EXIT_SUCCESS);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Invalid map path");
		exit(EXIT_SUCCESS);
	}
	line = get_next_line(fd);
	while (line)
	{
		map = my_strjoin(map, line, true, true);
		line = get_next_line(fd);
	}
	close(fd);
	if (!map)
	{
		printf("Empty map");
		exit(EXIT_SUCCESS);
	}
	res = ft_split(map, '\n');
	free(map);
	return (res);
}
void	parsing_error(char **map, int x, int y)
{
	int i;

	i = -1;
	while (map[++i])
		printf("%d\t%s\n", i, map[i]);
	if (x == -1 && y == 0)
		printf("\n missing P\\E\\C");
	else if (x == 0 && y == -1)
		printf("path to exit or collectible is invalid");
	else
		printf("\nparsing error at x=%d y=%d", x, y);
	exit(EXIT_SUCCESS);
}

void	is_map_valid(t_data *game, char *map_path)
{
	t_map map;
	bool is_P = false;
	bool is_E = false;
	int x;
	int y;
	int c_nbr;

	y = -1;
	c_nbr = 0;
	map.map = get_map(map_path);
	while (map.map[++y])
	{
		x = -1;
		while (map.map[y][++x])
		{
			if (map.map[y][x] != '1' && (x - 1 < 0 || !map.map[y][x + 1] || y - 1 < 0 || !map.map[y + 1][x]))
				parsing_error(map.map, x, y);
			if (!ft_strchr("01CEP", map.map[y][x]))
				parsing_error(map.map, x, y);
			if ((is_P == true && map.map[y][x] == 'P') || (is_E == true && map.map[y][x] == 'E'))
				parsing_error(map.map, x, y);
			if (map.map[y][x] == 'P')
				is_P = true;
			if (map.map[y][x] == 'E')
				is_E = true;
			if (map.map[y][x] == 'C')
				c_nbr++;
		}
	}
	if (!(is_E || is_P))
		parsing_error(map.map, -1, -1);
	game->x.map_size = x;
	game->y.map_size = y;
	map.collectibles_nbr = c_nbr + 1;
	check_path(game, &map);
	game->map = map;
}