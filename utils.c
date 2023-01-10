/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 19:46:35 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/15 10:44:51 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include "solong.h"

char	*my_strjoin(char *s1, char *s2, bool free_s1, bool free_s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 && s2)
	{
		str = ft_strdup(s2);
		if (free_s2)
			free(s2);
		return (str);
	}
	else if (!s2 && s1)
	{
		str = ft_strdup(s1);
		if (free_s1)
			free(s1);
		return (str);
	}
	str = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	if (free_s1)
		free(s1);
	if (free_s2)
		free(s2);
	return (str);
}
int	upper_multiple_of_48(int nbr)
{
	nbr = nbr / 48;
	return (++nbr * 48);
}
char *file_path(char *sprite_name, int iteration)
{
    char *path;
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