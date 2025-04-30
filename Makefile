NAME		= minishell
RM			= rm -f
SRCS		= $(wildcard src/*.c) $(wildcard src/exec/*.c) $(wildcard src/parsing/*.c)
LIBFT_DIR	= libft-complete
LIBFT		= $(LIBFT_DIR)/libft-complete.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(LIBFT_DIR) -g
OBJS		= $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft-complete -o $(NAME) -lreadline

$(LIBFT):
	make -s -C $(LIBFT_DIR)

all: $(NAME)
clean:
	make -s -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)
fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
