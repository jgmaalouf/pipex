# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/25 19:02:48 by jmaalouf          #+#    #+#              #
#    Updated: 2022/09/20 09:08:46 by jmaalouf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

FLAGS = -g -Wall -Wextra -Werror

SRC = ft_strncmp.c ft_strlen.c ft_strlcpy.c ft_split.c ft_strjoin.c

SRC_OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${SRC_OBJ}
	ar rcs $@ $^

${SRC_OBJ}:
	${CC} ${FLAGS} -c ${SRC}

clean:
	rm -f *.o

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re