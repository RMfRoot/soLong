/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:27:15 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/03 15:27:31 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

static char	*str_rem_fill(char *str, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i])
	{
		s[j] = str[i];
		i++;
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*str_rem(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	while (str[i++])
		j++;
	if (j == 0)
	{
		free(str);
		return (0);
	}
	s = malloc(j + 1);
	if (!s)
		return (0);
	s = str_rem_fill(str, s);
	free(str);
	return (s);
}

char	*ft_strdup(char *str)
{
	char	*s;
	int		i;

	i = 0;
	while (str[i])
		i++;
	s = malloc(i + 1);
	if (!s)
		return (0);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*get_read_fill(char *str, char *s, int read_res)
{
	if (read_res == 0)
	{
		free(s);
		return (str);
	}
	else if (read_res == -1)
	{
		free(s);
		if (str)
			free(str);
		return (0);
	}
	s[read_res] = '\0';
	str = strjoin(str, s);
	free(s);
	return (str);
}
