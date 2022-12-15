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
#include "soLong.h"

char	*my_strjoin(char *s1, char *s2, int free_s1, int free_s2)
{
	char	*str;
	size_t	i;
	size_t	j;

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