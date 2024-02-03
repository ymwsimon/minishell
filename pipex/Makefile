SRCS = pipex exe utils 

SRCS_B = pipex_bonus exe_bonus utils_bonus here_doc

OBJS = $(SRCS:=.o)

OBJS_B = $(SRCS_B:=.o)

NAME = pipex

CC	 = cc

FLAGS = -Wall -Werror -Wextra

INC_DIR = includes

LIBFT_DIR = libft

GNL_DIR = get_next_line

GNL_SRC = get_next_line get_next_line_utils

LIBFT = libft.a

SRC_DIR = srcs

$(NAME) : $(OBJS) $(LIBFT_DIR)/$(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -I$(INC_DIR) -I$(LIBFT_DIR) -lft -L$(LIBFT_DIR)
	
$(OBJS) : $(SRCS:%=$(SRC_DIR)/%.c)
	$(CC) $(FLAGS) $^ -c -I$(INC_DIR) -I$(LIBFT_DIR) -lft -L$(LIBFT_DIR)

$(LIBFT_DIR)/$(LIBFT) :
	make -C $(LIBFT_DIR)

all : $(NAME)

bonus : $(OBJS_B) $(LIBFT_DIR)/$(LIBFT) $(GNL_SRC:%=$(GNL_DIR)/%.c)
	$(CC) $(FLAGS) $(OBJS_B) $(GNL_SRC:%=$(GNL_DIR)/%.c) -o $(NAME) -I$(INC_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -lft -L$(LIBFT_DIR)

$(OBJS_B) : $(SRCS_B:%=$(SRC_DIR)/%.c) $(GNL_SRC:%=$(GNL_DIR)/%.c)
	$(CC) $(FLAGS) $^ -c -I$(INC_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -lft -L$(LIBFT_DIR)

clean :
	make -C $(LIBFT_DIR) clean
	rm -rf *.o

fclean : clean
	make -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re		: clean $(NAME)

.PHONY : all clean fclean re bonus

