# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 11:23:07 by ofilloux          #+#    #+#              #
#    Updated: 2024/08/30 21:50:32 by ofilloux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
COMP =  cc
FLAGS = -Wall -Wextra -Werror -g

INC_DIR = ./inc
INC = ./inc/pipex.h

UTILS = ./utils/clean_exit.c \
	./utils/string_utils.c \
	./utils/ft_split.c\

SRC = main.c \
	./src/init.c \
	./src/redirects.c \
	$(UTILS)

OBJ = $(SRC:.c=.o)

##################
all: $(NAME)

$(NAME): $(OBJ)
	$(COMP) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(INC) Makefile
	$(COMP) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
