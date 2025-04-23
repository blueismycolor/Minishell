
NAME		= minishell

RM 		= rm -f
SRCS_MAIN	= main.c
SRCS 		= 

LIBFT_DIR	= libft-complete
LIBFT		= $(LIBFT_DIR)/libft-complete.a

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ilibft-complete -g

OBJS_MAIN	= $(SRCS_MAIN:.c=.o) $(SRCS:.c=.o) 

$(NAME): $(LIBFT) $(OBJS_MAIN)
	@$(CC) $(CFLAGS) $(OBJS_MAIN) -L$(LIBFT_DIR) -lft-complete -o $(NAME)
	
$(LIBFT):
	make -s -C $(LIBFT_DIR)

all: $(NAME)

clean:
	make -s -C $(LIBFT_DIR) clean
	$(RM) $(OBJS_MAIN)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
