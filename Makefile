# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 18:21:33 by jabenjam          #+#    #+#              #
#    Updated: 2020/08/02 18:40:37 by jabenjam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#COLORS
GREY=$'\x1b[30m
RED=$'\x1b[31m
GREEN=$'\x1b[32m
YELLOW=$'\x1b[33m
BLUE=$'\x1b[34m
PURPLE=$'\x1b[35m
CYAN=$'\x1b[36m
WHITE=$'\x1b[37m

#STYLES
END=$'\x1b[0m
BOLD=$'\x1b[1m
UNDER=$'\x1b[4m
REV=$'\x1b[7m

#CORE
NAME = Cub3D

LFT = libft/

LFTA = libft/libft.a

INCS =  incs/cub3d.h \
		incs/keys.h\
		incs/libft.h \

B_INC = bonus_incs/cub3d.h \
		incs/keys.h \
		incs/libft.h \

SRCS = cub3d.c \
		srcs/bmp.c \
		srcs/check_closed.c \
		srcs/check_data.c \
		srcs/check_map.c \
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
		bonus_srcs/check_closed.c \
		bonus_srcs/check_data.c \
		bonus_srcs/check_map.c \
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

MLX = -lmlx -framework OpenGL -framework AppKit #MacOS

#MLX = #Linux

$(NAME) :
	@echo "$(YELLOW)Creating libft.a..."
	@$(MAKE) -C $(LFT) > /dev/null
	@echo "$(GREEN)Done !"
	@echo "$(YELLOW)Linking objects..."
ifeq ($(MAKECMDGOALS),bonus)
	$(CC) $(CFLAGS) -o $(NAME) $(BOBJS) $(MLX) $(LFTA)
else
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) $(LFTA)
endif

all : $(OBJS) $(NAME)
	@echo "$(BOLD)$(GREEN)$(NAME) is ready !"

bonus : $(BOBJS) $(NAME)
	@echo "$(BOLD)$(GREEN)$(NAME) is ready !"

clean :
	@echo "$(RED)Deleting object files in subfolders..."
	@rm -rf $(OBJS) $(BOBJS)
	@$(MAKE) clean -C $(LFT) > /dev/null
	@echo "$(GREEN)Done !"

fclean : clean
	@echo "$(RED)Deleting Cub3d, cub3d.bmp and libft.a..."
	@rm -rf $(NAME)
	@rm -rf cub3d.bmp
	@$(MAKE) fclean -C $(LFT) > /dev/null
	@echo "$(GREEN)Done !"


re : fclean all

.PHONY : all bonus clean fclean re