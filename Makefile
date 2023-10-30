# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afarheen <afarheen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 09:59:04 by afarheen          #+#    #+#              #
#    Updated: 2023/07/25 16:29:57 by afarheen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

MY_SOURCES = main.c thread_init.c philo_routine.c philo_utils.c utils.c forks.c

MY_OBJS = $(MY_SOURCES:.c=.o)

CFLAGS = -pthread -Wall -Werror -Wextra
CC = cc

all: $(NAME)

$(NAME): $(MY_OBJS)
	$(CC) $(CFLAGS) $(MY_SOURCES) -o $(NAME)

clean:
	rm -f $(MY_OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf philo.dSYM

re: fclean all
