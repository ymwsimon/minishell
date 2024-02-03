NAME := minishell

SRCS := main get_next_line

SRCS_DIR := srcs

OBJ_DIR := obj

INC_DIR := includes

FLAGS := -Wall -Werror -Wextra -g

LIBFT_DIR := lib/libft

LIBS := -lreadline -lft -L$(LIBFT_DIR)

CC := cc

all : $(NAME)

$(NAME) : $(SRCS:%=$(SRCS_DIR)/%.c)
	make -C $(LIBFT_DIR) bonus
	$(CC) $(FLAGS) $^ -o $(NAME) $(LIBS)

clean :
	make -C $(LIBFT_DIR) clean
	rm -rf *.o

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re : clean all

.PHONY : all clean fclean re