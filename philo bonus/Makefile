# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hchaguer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 20:21:16 by hchaguer          #+#    #+#              #
#    Updated: 2023/06/07 04:56:05 by hchaguer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread -g3

SRC = 	philo.c\
	  	ft_atoi.c\
		args.c\
		threads.c\
		utils.c

OBJ = ${SRC:.c=.o}

bonus : ${NAME}

${NAME} : ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean : 
	rm -rf ${OBJ}

fclean : clean
	rm -rf ${NAME}

re : fclean bonus

PHONY: bonus clean fclean re
