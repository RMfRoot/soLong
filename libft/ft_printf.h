/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 16:18:55 by egeorgel          #+#    #+#             */
/*   Updated: 2022/12/01 21:02:29 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* *****************************************int main(void)
{
	char *str;
	int fd = open("/Users/egeorgel/Deskt
********************************* */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>

void	ft_putstr_printf(char *s, int fd, int *count);
void	ft_putchar_printf(char c, int fd, int *count);

#endif
