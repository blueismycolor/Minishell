# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/09 11:58:32 by aeudes            #+#    #+#              #
#    Updated: 2025/02/09 14:31:22 by aeudes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c \
	ft_memchr.c \
	ft_putchar_fd.c \
	ft_strjoin.c \
	ft_toupper.c \
	ft_isascii.c \
	ft_memcmp.c \
	ft_putendl_fd.c \
	ft_strlcat.c \
	ft_strnstr.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_putnbr_fd.c \
	ft_strrchr.c \
	ft_isdigit.c \
	ft_putstr_fd.c \
	ft_strlcpy.c \
	ft_calloc.c \
	ft_memmove.c \
	ft_split.c \
	ft_strtrim.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_strchr.c \
	ft_strlen.c \
	ft_substr.c \
	ft_memset.c \
	ft_tolower.c \
	ft_isalpha.c \
	ft_itoa.c \
	ft_strdup.c \
	ft_strncmp.c \
	ft_strmapi.c \
	ft_striteri.c \

BONUS_SRCS = ft_lstnew_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstmap_bonus.c \

CFLAGS = -Wall -Wextra -Werror
CC = gcc

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
	ranlib $(NAME)

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re