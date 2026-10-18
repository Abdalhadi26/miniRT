NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MINILIBX_DIR = ./minilibx-linux
MLX = $(MINILIBX_DIR)/libmlx.a
MLX_FLAGS = -L $(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lbsd

INCLUDES = -I includes -I $(LIBFT_DIR) -I $(MINILIBX_DIR)

SRC = \
	src/main.c \
	src/parsing/check_args.c \
	src/cleanup.c \
	src/hook_init.c \
	src/mlx_init.c \
	src/render.c \
	src/utils.c \
	src/math_func.c \

OBJ = $(SRC:.c=.o)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MINILIBX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c ./includes/miniRT.h
	$(CC)  $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(MINILIBX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re