# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfilipe- < hfilipe-@student.42porto.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 10:42:35 by hfilipe-          #+#    #+#              #
#    Updated: 2025/04/29 16:19:47 by hfilipe-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
GDB = -ggdb
FLAGS = -Wall -Werror -Wextra -g
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
SRC_FILES = philosophers.c philosophers_utils.c init.c check_args_errors.c \
threads.c destroy.c actions.c monitoring.c time.c threads2.c mutex.c actions2.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
NAME = philo
RM = rm -f
SANITIZE_FLAGS = -fsanitize=thread

DEPS = $(OBJ:.o=.d)

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -I $(INC_DIR) -MMD -c $< -o $@

-include $(DEPS)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

sanitize: fclean all
sanitize: FLAGS += $(SANITIZE_FLAGS)
