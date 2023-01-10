# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 20:35:44 by egeorgel          #+#    #+#              #
#    Updated: 2023/01/02 14:17:40 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
SRC = free.c utils.c gnl/get_next_line_utils.c gnl/get_next_line.c get_map.c check_path.c get_images.c movement.c print_map.c main.c
OBJ = $(SRC:.c=.o)
NAME = soLong

%.o : %.c
	$(CC) $(CFLAGS) -g -Imlx -c -O0 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ) $(LIB) Makefile
	cd libft ; make
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

PHONY: all clean fclean re
