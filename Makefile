# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msousa <mlrcbsousa@gmail.com>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/29 15:00:20 by msousa            #+#    #+#              #
#    Updated: 2022/05/08 16:46:29 by msousa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS	= -Wall -Wextra -Werror
LINKS		= -lmlx -lm -Llibft -lft
CC			= gcc
RM			= rm -f
INC			= -Iinclude -Ilibft/include
UNAME 	:= ${shell uname}
OBJ			= ${SRC:%.c=obj/%.o}
SRC			= src/main.c src/draw.c src/hooks.c src/helpers.c src/test.c \
					src/parse.c src/parse_1.c src/parse_2.c src/maplines.c src/errors.c \
					src/settings.c src/map.c src/map_1.c src/elements.c src/maplines_1.c

NAME		= cub3d

ifeq (${UNAME}, Linux)
LINKS 	+= -lbsd -lXext -lX11
endif

ifeq (${UNAME}, Darwin)
LINKS 	+= -framework OpenGL -framework AppKit
CFLAGS 	+= -DOS_MAC
endif

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
					./test main.sh

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
