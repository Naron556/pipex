NAME = pipex
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Ilibft

SRC = \
	pipex.c \
	pipex_utils.c \
	file_checks.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	@gcc $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a

libft/libft.a:
	@$(MAKE) -C libft

%.o: %.c
	@gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(MAKE) clean -C libft
	@rm -rf $(OBJ)

fclean: clean
	@$(MAKE) fclean -C libft
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
