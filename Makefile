# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 15:00:20 by msousa            #+#    #+#              #
#    Updated: 2022/04/21 11:12:45 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror -g
LINKS		= -Llibft -lft
CC			= gcc
RM			= rm -f
INC			= -Iinclude -Ilibft/include
OBJ			= ${SRC:%.c=obj/%.o}
SRC			= cub3d.c

NAME		= cub3d

${NAME}:	${OBJ}
					${MAKE} -C libft
					${CC} ${CFLAGS} ${OBJ} ${LINKS} -o $@

obj/%.o:%.c
					@mkdir -p $(dir $@)
					${CC} ${CFLAGS} ${INC} -c $< -o $@

all:			${NAME}

bonus:		all

style:
					-norminette $$( find . -type f \( -name "*.c" -or -name "*.h" \) )

test:			${NAME}
					-./test/main.sh

check:
					-cat ${NAME}.c src/*/* | grep TODO

clean:
					${MAKE} clean -C libft
					${RM} -rf obj

fclean:		clean
					${RM} ${NAME}

re: 			fclean all

debug:		INC += -DDEBUG_MODE
debug:		CFLAGS += -g -fsanitize=address
debug:		clean
debug:		all

.PHONY : 	all clean fclean re bonus
