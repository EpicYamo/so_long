SRCS = so_long.c get_next_line_utils.c get_next_line.c map_utils_pt_one.c map_utils_pt_two.c \
		map_utils_pt_three.c map_utils_pt_four.c utils_pt_one.c \
		game_utils_pt_one.c game_utils_pt_two.c game_utils_pt_three.c \
		
NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
OBJS = $(SRCS:.c=.o)

all: $(MLX) $(NAME)

$(MLX):
	@make -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(MLX) -lX11 -lXext

clean:
	rm -f $(OBJS)

fclean: clean
	@make clean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re