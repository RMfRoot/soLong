/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 18:04:41 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/02 19:26:38 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*str_rem(char *str);
char	*get_next_line(int fd);
int		is_end(char *s);
char	*ft_strdup(char *str);
char	*get_read_fill(char *str, char *s, int read_res);
char	*strjoin(char *str, char *s);

#endif
