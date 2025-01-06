# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/17 17:11:29 by lbuisson          #+#    #+#              #
#    Updated: 2025/01/06 14:22:34 by lbuisson         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRCS_DIR = ./srcs
SRCS = main.c exec_cmd.c utils.c
SRCS_FILES = $(addprefix $(SRCS_DIR)/, $(SRCS))
OBJS = $(SRCS_FILES:.c=.o)

LIBFT_DIR = ./libft
LIBFT_A = $(LIBFT_DIR)/libft.a
LIBFT_FUNCTIONS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c \
	ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c \
	ft_striteri.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c \
	ft_strtrim.c ft_tolower.c ft_toupper.c \
	ft_printf/ft_numbers.c ft_printf/ft_words_pointer.c ft_printf/ft_printf.c
LIBFT_FILES = $(addprefix $(LIBFT_DIR)/, $(LIBFT_FUNCTIONS)) $(LIBFT_DIR)/libft.h $(LIBFT_DIR)/ft_printf/ft_printf.h $(LIBFT_DIR)/Makefile
LIBFT_FLAGS = -L$(LIBFT_DIR) $(LIBFT_A)

$(NAME): $(OBJS) $(LIBFT_FILES)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) -o $(NAME)

all: $(NAME)

%.o: %.c Makefile include/pipex.h libft/libft.h
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
