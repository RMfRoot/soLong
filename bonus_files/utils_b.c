/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_b.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:29:57 by egeorgel          #+#    #+#             */
/*   Updated: 2023/01/31 23:56:33 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong_b.h"

void	my_strjoin_free(char *s1, char *s2, bool free_s1, bool free_s2)
{
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
}

char	*my_strjoin(char *s1, char *s2, bool free_s1, bool free_s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && s2)
		str = ft_strdup(s2);
	else if (s1 && !s2)
		str = ft_strdup(s1);
	else
	{
		str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (!str)
			return (NULL);
		i = -1;
		j = 0;
		while (s1[++i])
			str[j++] = s1[i];
		i = -1;
		while (s2[++i])
			str[j++] = s2[i];
		str[j] = 0;
	}
	my_strjoin_free(s1, s2, free_s1, free_s2);
	return (str);
}

char	*file_path(char *sprite_name, int iteration)
{
	char	*path;

	path = my_strjoin("sprites/", sprite_name, false, false);
	path = my_strjoin(path, ft_itoa(iteration), true, true);
	path = my_strjoin(path, ".xpm", true, false);
	return (path);
}

int	check_file_type(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(haystack) - ft_strlen(needle);
	j = 0;
	while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
		j++;
	if (!needle[j])
		return (1);
	return (0);
}

void	write_step_count(t_data *game)
{
	static unsigned long	last_count = 0;
	char					*str;

	if (game->step_count / 48 > last_count && game->step_count / 48 < INT8_MAX)
		last_count = game->step_count / 48;
	str = ft_itoa(last_count);
	mlx_string_put(game->mlx, game->mlx_win, game->x.w
		- ((ft_strlen(str) + 1) * 10), 10, 0x00FFFFFF, str);
}
