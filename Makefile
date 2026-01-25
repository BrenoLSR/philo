# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brendos- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/25 11:32:21 by brendos-          #+#    #+#              #
#    Updated: 2026/01/25 11:32:25 by brendos-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = \
	main.c \
	utils.c \
	ft_atol.c \
	parsing.c \
	table_init.c \
	clean.c \
	philo.c \
	routine.c \
	monitor.c \
	time.c	\
	simulation.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
PTHREAD = -pthread

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(PTHREAD) -o $(NAME)
	@echo "[\033[0;32mOK\033[0m] $(NAME) compiled!"

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	@echo "[\033[0;32mOK\033[0m] Objects cleaned!"

fclean: clean
	$(RM) $(NAME)
	@echo "[\033[0;32mOK\033[0m] Binary removed!"

re: fclean all

.PHONY: all clean fclean re
