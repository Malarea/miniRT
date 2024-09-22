# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agranger <agranger@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/29 09:54:25 by agranger          #+#    #+#              #
#    Updated: 2023/02/19 00:14:16 by agranger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CFLAGS = -Wall -Wextra -Werror -g3 

CC = gcc

SRCS =	ft_strlen.c \
		ft_arrlen.c \
		ft_putstr_fd.c \
		ft_free.c \
		ft_atoi.c \
		ft_atof.c \
		ft_calloc.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strjoin.c \
		ft_substr.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_split.c \
		free_arr_of_str.c \
		ft_strcmp.c \
		ft_isdigit.c \
		ft_strdup.c

OBJS = $(SRCS:.c=.o)

INCLUDES = -I.

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^
	@echo "$(NAME) created"

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

clean: 
	@$(RM) *.o
	@echo "object files libft removed"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(NAME) removed"

re: fclean all

.PHONY: clean fclean re all bonus
