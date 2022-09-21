# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 11:56:41 by jmaalouf          #+#    #+#              #
#    Updated: 2022/09/21 11:02:09 by jmaalouf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex.a

CC = cc

# FLAGS = -g
FLAGS = -g -Wall -Wextra -Werror

SRC = src/main.c src/cmdlist_parse_argv.c src/exec_cmd.c src/pipification.c\
	src/here_doc.c src/here_doc_pipification.c utils/free_and_error_1.c utils/free_and_error_2.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRC_OBJ = ${SRC:.c=.o}

all: ${NAME}

${NAME}: ${SRC_OBJ}
	$(MAKE) -C ./libft
	cp libft/libft.a $(NAME)
	ar rcs $@ $^
	${CC} ${FLAGS} -o pipex $(SRC) $(NAME)

%.o: %.c
	${CC} ${FLAGS} -c $^ -o $@

clean:
	$(MAKE) clean -C ./libft
	rm -f *.o
	rm -f src/*.o
	rm -f utils/*.o

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f ${NAME}
	rm -rf pipex.dSYM
	rm -rf ./get_next_line/*.o
pclean: fclean
	rm -f pipex

re: fclean all

.PHONY: all clean fclean re