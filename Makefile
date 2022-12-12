# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 20:35:44 by egeorgel          #+#    #+#              #
#    Updated: 2022/12/11 20:35:47 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC =
OBJ = {SRC:.c=.o}
HDR = mlx.h
NAME = soLong

%.o : %.c
	{CC} {CFLAGS} -c -o %.c %.o

all:
	{NAME}

NAME: {OBJ} {HDR} Makefile
	{CC} {CFLAGS} -o {OBJ}

clean:
	rm -f {OBJ}

fclean: clean
	rm -f {NAME}

re: fclean all

PHONY: all clean fclean re
