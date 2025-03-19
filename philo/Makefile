# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfilipe- <hfilipe-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 10:42:35 by hfilipe-          #+#    #+#              #
#    Updated: 2025/03/19 15:04:00 by hfilipe-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
GDB = -ggdb
FLAGS = -Wall -Werror -Wextra -g
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
SRC_FILES = philosophers.c philosophers_utils.c init.c check_args_errors.c \
threads.c destroy.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
NAME = philo
RM = rm -f

$(shell mkdir -p $(OBJ_DIR))

all: $(NAME)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(GDB)

clean:
	$(RM)	 $(OBJ)
	$(RM -rf $(OBJ_DIR)) 

fclean: clean
	$(RM) $(NAME)
	
re: fclean all