# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 18:21:33 by jabenjam          #+#    #+#              #
#    Updated: 2020/07/29 14:01:29 by jabenjam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

LFT = /lib/libft.a

INCS =  /incs/cub3d.h \
		/incs/keys.h \
		/incs/libft.h \

B_INC = /bonus_incs/cub3d.h \
		/incs/keys.h \
		/incs/libft.h \

SRCS = /main.c \
		/srcs/bmp.c \
		/srcs/check_data.c \
		/srcs/controls.c \
		/srcs/core.c \
		/srcs/events.c \
		/srcs/exit.c \
		/srcs/init.c \
		/srcs/parser_core.c \
		/srcs/parser_params.c \
		/srcs/raycast_core.c \
		/srcs/raycast_display.c \

B_SRCS = /main.c \
		/srcs/bmp.c \
		/srcs/check_data.c \
		/bonus_srcs/controls.c \
		/srcs/core.c \
		/bonus_srcs/dont_press_t_if_epileptic.c \
		/bonus_srcs/events.c \
		/srcs/exit.c \
		/bonus_srcs/init.c \
		/bonus_srcs/mini_map.c \
		/srcs/parser_core.c \
		/srcs/parser_params.c \
		/srcs/raycast_core.c \
		/bonus_srcs/raycast_display.c \

OBJS = $(SRCS:.c=.o)

BOBJS = $(B_SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX = minilibx -L minilibx -lmlx -framework OpenGL -framework AppKit

#MLX_LINUX = 

all :
	$(CC) $(CFLAGS) $(MLX) $(LFT) $(SRCS) -I $(INCS) -o $(NAME)

bonus :
	$(CC) $(CFLAGS) $(MLX) $(LFT) $(B_SRCS) -I $(B_INCS) -o $(NAME)

clean :
	rm -rf $(OBJS) $(BOBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all bonus clean fclean re