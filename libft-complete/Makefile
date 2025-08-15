# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/09 12:23:07 by aeudes            #+#    #+#              #
#    Updated: 2025/03/06 10:39:41 by aeudes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft-complete.a
LIB_PRINTF = ft_printf/libftprintf.a
LIB_LIBFT = libft/libft.a

all : ${NAME}

RM = rm -f

${NAME} : ${LIB_PRINTF} ${LIB_LIBFT}
	ar -v rcs ${NAME} ft_printf/*.o libft/*.o

${LIB_PRINTF} :
	${MAKE} -C $$(dirname $@)

${LIB_LIBFT} :
	${MAKE} -C $$(dirname $@)

clean :
	${MAKE} clean -C $$(dirname ${LIB_PRINTF});
	${MAKE} clean -C $$(dirname ${LIB_LIBFT});

fclean : clean
	${MAKE} fclean -C $$(dirname ${LIB_PRINTF});
	${MAKE} fclean -C $$(dirname ${LIB_LIBFT});
	# ${RM} ${LIB_PRINTF} ${LIB_LIBFT} ${NAME}
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re