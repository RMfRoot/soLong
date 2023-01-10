/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:25:02 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/03 15:25:55 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
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
