# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mben-zeh <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/16 10:14:42 by mben-zeh          #+#    #+#              #
#    Updated: 2022/12/16 10:14:45 by mben-zeh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC=gcc

CFLAGS = -Wall -Werror -Wextra

SRC =	pipex.c \
		pipex_utils.c \
		ft_split.c \
		libft_utils.c \

SRCB =	bonus/bonus.c \
		bonus/get_next_line_utils.c \
		bonus/gnl.c \
		bonus/utils_bonus.c \
		bonus/ft_split_bonus.c \
		bonus/libft_utils_bonus.c \
	
OBJ = ${SRC:.c=.o}

OBJ_B = ${SRCB:.c=.o}

all: ${NAME}

${NAME}: $(OBJ)
	$(CC) $(CFLAGS) ${OBJ} -o ${NAME}

bonus : ${OBJ_B}
	$(CC) $(CFLAGS) ${OBJ_B} -o ${NAME}

clean:
	@rm -f ${OBJ} ${OBJ_B}

fclean: clean
	@rm -f ${NAME}
re: fclean all

.PHONY:all clean fclean re
