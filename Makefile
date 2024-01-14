NAME = so_long_bonus
SRCS = so_long_bonus.c ./moves.c counter.c read_check_map.c ./animitions.c utilis_bonus.c ./start_game.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -L/usr/lib -lXext -lX11  -g -g3
LIBFT = ./libft/libft.a
MLX = ./minilibx-linux/libmlx_Linux.a

all:$(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	make -C ./libft

$(MLX):
	make -C ./minilibx-linux

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	gcc $(OBJS) $(MLX) $(LIBFT) $(CFLAGS) -o $(NAME)

clean:
	make clean -C ./libft
	rm -f *.o
fclean: clean
	make fclean -C ./libft
	make clean -C ./minilibx-linux
	rm -f $(NAME)

re:fclean all

