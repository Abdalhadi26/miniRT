NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror -O3

LIBFT_DIR = ./libft
GNL_DIR = ./gnl
LIBFT = $(LIBFT_DIR)/libft.a
GNL = $(GNL_DIR)/libgnl.a

MINILIBX_DIR = ./minilibx-linux
MLX = $(MINILIBX_DIR)/libmlx.a
MLX_FLAGS = -L $(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lbsd

INCLUDES = -I includes -I $(LIBFT_DIR) -I $(MINILIBX_DIR)

SRC = \
	src/main.c \
	src/cleanup.c \
	src/hook_init.c \
	src/mlx_init.c \
	src/render.c \
	src/utils.c \
	src/math_func.c \
	src/hit_functions.c \
	src/normal.c \
	src/intersection_sphere.c \
	src/intersection_cylinder.c \
	src/intersection_plane.c \
	src/color.c

OBJ = $(SRC:.c=.o)

all: $(LIBFT)  $(GNL) $(MLX) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(GNL):
	make -C $(GNL_DIR)

$(MLX):
	make -C $(MINILIBX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL) $(MLX_FLAGS) -o $(NAME)

%.o: %.c ./includes/miniRT.h
	$(CC)  $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(GNL_DIR) clean
	make -C $(MINILIBX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(GNL_DIR) fclean
	make -C $(MINILIBX_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
