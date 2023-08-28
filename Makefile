# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eaubry <eaubry@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/28 13:25:39 by eaubry            #+#    #+#              #
#    Updated: 2023/08/28 17:00:12 by eaubry           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    =	src/main.c

INC    =	../inc/philo.h

NAME    =	philo

OBJS    =	${SRCS:.c=.o}

CFLAGS    =    -Wall -Wextra -Werror -g

all:	${NAME}

.c.o:	${INC}
	cc ${CFLAGS} -fPIC -c $< -o ${<:.c=.o}

${NAME}:	libft/libft.a  ${OBJS}
	gcc ${OBJS} ${CFLAGS} -Llibft -lft -o ${NAME} 

clean:
	rm -f ${OBJS}
	make -C libft clean

fclean:	clean
	rm -f ${NAME}
	make -C libft fclean


re:	fclean all

.PHONY:	all clean fclean re bonus

libft/libft.a:
	make -C libft