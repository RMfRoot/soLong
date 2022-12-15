# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 20:35:44 by egeorgel          #+#    #+#              #
#    Updated: 2022/12/15 21:03:17 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
SRC = utils.c get_images.c main.c
OBJ = $(SRC:.c=.o)
NAME = soLong

%.o : %.c
	$(CC) $(CFLAGS) -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(LIB) Makefile
	$(CC) $(CFLAGS) $(OBJ) libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

PHONY: all clean fclean re
