NAME		= 	minishell
RM			= 	rm -f
SRC_DIR		= 	./src
PARS_DIR	= 	./src/parsing
EXEC_DIR	= 	./src/exec
BUILIN_DIR	= 	./src/exec/builtins
SRCS		= 	$(SRC_DIR)/exit.c \
				$(SRC_DIR)/handle_pipes.c \
				$(SRC_DIR)/heredoc_preprocess.c \
				$(SRC_DIR)/heredoc.c \
				$(SRC_DIR)/history.c \
				$(SRC_DIR)/main_loop.c \
				$(SRC_DIR)/main.c \
				$(SRC_DIR)/minishell_process.c \
				$(SRC_DIR)/redir_utils.c \
				$(SRC_DIR)/redir.c \
				$(SRC_DIR)/utils.c \
				$(PARS_DIR)/create_list_tcmd0.c \
				$(PARS_DIR)/create_list_tcmd1.c \
				$(PARS_DIR)/expansion0.c \
				$(PARS_DIR)/expansion1.c \
				$(PARS_DIR)/expansion2.c \
				$(PARS_DIR)/free_struct.c \
				$(PARS_DIR)/ft_remove_quote.c \
				$(PARS_DIR)/ft_remove_quotes_utils.c \
				$(PARS_DIR)/get_args.c \
				$(PARS_DIR)/get_nbr_token.c \
				$(PARS_DIR)/get_token_tabstr.c \
				$(PARS_DIR)/get_token_utils0.c \
				$(PARS_DIR)/get_token_utils1.c \
				$(PARS_DIR)/parsing0.c \
				$(PARS_DIR)/parsing1.c \
				$(PARS_DIR)/add_cmd_to_result.c \
				$(PARS_DIR)/check_for_args.c \
				$(EXEC_DIR)/exec_2.c \
				$(EXEC_DIR)/exec.c \
				$(EXEC_DIR)/init_data.c \
				$(EXEC_DIR)/utils.c \
				$(BUILIN_DIR)/cd_utils.c \
				$(BUILIN_DIR)/cd.c \
				$(BUILIN_DIR)/echo.c \
				$(BUILIN_DIR)/env.c \
				$(BUILIN_DIR)/exit.c \
				$(BUILIN_DIR)/export_utils.c \
				$(BUILIN_DIR)/export.c \
				$(BUILIN_DIR)/pwd.c \
				$(BUILIN_DIR)/unset.c
LIBFT_DIR	= libft-complete
LIBFT		= $(LIBFT_DIR)/libft-complete.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I$(LIBFT_DIR) -g
# CFLAGS		+= -fsanitize=address
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
