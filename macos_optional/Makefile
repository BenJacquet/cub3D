# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/28 18:21:33 by jabenjam          #+#    #+#              #
#    Updated: 2020/10/23 11:35:00 by jabenjam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BONUS = cub3D_bonus

LFT = libft/

LFTA = libft/libft.a

INCS =  incs/cub3d.h \
		incs/libft.h \
		incs/keys_mac.h

B_INC = bonus_incs/cub3d.h \
		incs/libft.h \
		incs/keys_mac.h

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
		srcs/sprites_sort.c


B_SRCS = cub3d_bonus.c \
		bonus_srcs/aesthetic_bonus.c \
		bonus_srcs/bmp_bonus.c \
		bonus_srcs/check_closed_bonus.c \
		bonus_srcs/check_data_bonus.c \
		bonus_srcs/check_map_bonus.c \
		bonus_srcs/controls_bonus.c \
		bonus_srcs/core_bonus.c \
		bonus_srcs/events_bonus.c \
		bonus_srcs/exit_bonus.c \
		bonus_srcs/init_bonus.c \
		bonus_srcs/mini_map_bonus.c \
		bonus_srcs/parser_core_bonus.c \
		bonus_srcs/parser_params_bonus.c \
		bonus_srcs/raycast_core_bonus.c \
		bonus_srcs/raycast_display_bonus.c \
		bonus_srcs/sprites_core_bonus.c \
		bonus_srcs/sprites_display_bonus.c \
		bonus_srcs/sprites_sort_bonus.c

OBJS = $(SRCS:.c=.o)

BOBJS = $(B_SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MLX = -lmlx -framework OpenGL -framework AppKit

$(NAME) : $(OBJS)
	@echo "Creating libft.a..."
	@$(MAKE) -C $(LFT) > /dev/null
	@echo "Done !"
	@echo "Linking objects..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFTA) $(MLX)

$(NAME_BONUS) : $(BOBJS) 
	@echo "Creating libft.a..."
	@$(MAKE) -C $(LFT) > /dev/null
	@echo "Done !"
	@echo "Linking objects..."
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(BOBJS) $(LFTA) $(MLX)

all : $(NAME)
	@echo "$(NAME) is ready !"

bonus : $(NAME_BONUS)
	@echo "$(NAME_BONUS) is ready !"

clean :
	@echo "Deleting object files in subfolders..."
	@rm -rf $(OBJS) $(BOBJS)
	@echo "Done !"
	@echo "Cleaning libft !"
	@$(MAKE) fclean -C $(LFT) > /dev/null
	@echo "Done !"

fclean : clean
	@echo "Deleting Cub3d, Cub3D_bonus, and Cub3D.bmp..."
	@rm -rf $(NAME) $(NAME_BONUS)
	@rm -rf Cub3D.bmp
	@echo "Done !"

re : fclean all

.PHONY : all bonus clean fclean re