# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jabenjam <jabenjam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/09 17:02:15 by jabenjam          #+#    #+#              #
#    Updated: 2020/08/11 18:43:35 by jabenjam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

HEADER = libft.h

SRCS = ft_abs.c \
		ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_ilen.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isinset.c \
		ft_isprint.c \
		ft_isspace.c \
		ft_itoa.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strrev.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \

BSRCS = ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c \

BOBJS = $(BSRCS:.c=.o)

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

$(NAME): $(OBJS) $(HEADER)
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

all: $(NAME)

bonus: $(BOBJS) $(HEADER)
	ar rc $(NAME) $(BOBJS)
	ranlib $(NAME)

clean:
	rm -rf $(OBJS) $(BOBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re bonus
