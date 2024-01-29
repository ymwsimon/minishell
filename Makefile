NAME := minishell

SRCS := main

SRCS_DIR := srcs

OBJ_DIR := obj

INC_DIR := includes

FLAGS := -Wall -Werror -Wextra

LIBS := -lreadline

CC := cc

all : $(NAME)

$(NAME) : $(SRCS:%=$(SRCS_DIR)/%.c)
	$(CC) $(FLAGS) $^ -o $(NAME) $(LIBS)