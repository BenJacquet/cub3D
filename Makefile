# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 18:21:33 by jabenjam          #+#    #+#              #
#    Updated: 2020/07/29 16:02:19 by jabenjam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

LFT = lib/libft.a

INCS =  incs/cub3d.h \
		incs/keys.h\
		incs/libft.h \

B_INC = bonus_incs/cub3d.h \
		incs/keys.h \
		incs/libft.h \

SRCS = cub3d.c \
		srcs/bmp.c \
		srcs/check_data.c \
		srcs/controls.c \
		srcs/core.c \
		srcs/events.c \
		srcs/exit.c \
		srcs/init.c \
		srcs/parser_core.c \
		srcs/parser_params.c \
		srcs/raycast_core.c \
		srcs/raycast_display.c \
		srcs/sprites_core.c \
		srcs/sprites_display.c \
		srcs/sprites_sort.c \


B_SRCS = cub3d_bonus.c \
		bonus_srcs/aesthetic.c \
		bonus_srcs/bmp.c \
		bonus_srcs/check_data.c \
		bonus_srcs/controls.c \
		bonus_srcs/core.c \
		bonus_srcs/events.c \
		bonus_srcs/exit.c \
		bonus_srcs/init.c \
		bonus_srcs/mini_map.c \
		bonus_srcs/parser_core.c \
		bonus_srcs/parser_params.c \
		bonus_srcs/raycast_core.c \
		bonus_srcs/raycast_display.c \
		bonus_srcs/sprites_core.c \
		bonus_srcs/sprites_display.c \
		bonus_srcs/sprites_sort.c \

OBJS = $(SRCS:.c=.o)

BOBJS = $(B_SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX = -lmlx -framework OpenGL -framework AppKit

#MLX_LINUX = 

all :
	$(CC) $(CFLAGS) $(MLX) $(LFT) $(SRCS) -I $(INCS)

bonus :
	$(CC) $(CFLAGS) $(MLX) $(LFT) $(B_SRCS) -I $(B_INCS)

clean :
	rm -rf $(OBJS) $(BOBJS)

fclean : clean
	rm -rf $(NAME)
	rm -rf cub3d.bmp

re : fclean all

.PHONY : all bonus clean fclean re