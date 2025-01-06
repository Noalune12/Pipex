# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:11:29 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/06 13:29:13 by lbuisson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

# SRCS = main.c utilsV1.c get_exec.c pipexV1.c
SRCS = main.c exec_cmd.c utils.c
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) $(LIBFT_A)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -g3 $(OBJS) $(LIBFT_FLAGS) -o $(NAME)

all: $(NAME)

%.o: %.c Makefile pipex.h libft/libft.h
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
