# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 20:35:44 by egeorgel          #+#    #+#              #
#    Updated: 2024/02/26 21:31:21 by egeorgel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = keys.c \
utils.c \
utils2.c \
gnl/get_next_line_utils.c \
gnl/get_next_line.c \
get_map.c \
check_path_utils.c \
check_path.c \
get_images.c \
parcour_map.c \
movement.c \
print_player.c \
print_map_fonctions.c \
print_map.c \
main.c

BNS_SRC = bonus_files/keys_b.c \
bonus_files/utils_b.c \
bonus_files/utils2_b.c \
gnl/get_next_line_utils.c \
gnl/get_next_line.c \
bonus_files/get_map_b.c \
bonus_files/check_path_utils_b.c \
bonus_files/check_path_b.c \
bonus_files/get_images_b.c \
bonus_files/parcour_map_b.c \
bonus_files/movement_b.c \
bonus_files/print_player_b.c \
bonus_files/print_map_fonctions_b.c \
bonus_files/print_map_b.c \
bonus_files/main_b.c

OBJ = $(SRC:.c=.o)
BOBJ = $(BNS_SRC:.c=.o)
NAME = so_long

ifdef WITH_BONUS
OBJS = $(BOBJ)
else
OBJS = $(OBJ)
endif

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -g -c $< -o $@

$(NAME): $(OBJS) $(LIB) Makefile
	cd libft ; make
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -L. -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

bonus:
	@${MAKE} WITH_BONUS=1

clean:
	rm -f $(OBJ) $(BOBJ)
	cd libft ; make clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all

PHONY: all bonus clean fclean re
