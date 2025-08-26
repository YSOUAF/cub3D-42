CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
MLX = -lmlx
APPKIT = -framework AppKit
OPENGL = -framework OpenGL

SRC_DIR = raycasting
SRCS = raycasting/help_func.c raycasting/hooks.c \
		raycasting/horizental2d.c raycasting/init_mlx.c \
		raycasting/map.c raycasting/palyer_mov.c \
		raycasting/set_player.c raycasting/set_rays.c \
		raycasting/vertical2d.c main.c raycasting/facing.c 
OBJS = $(SRCS:.c=.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX) $(APPKIT) $(OPENGL) -o $(NAME)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re