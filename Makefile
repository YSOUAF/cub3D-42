CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes #-fsanitize=address -g

MLX = -lmlx
APPKIT = -framework AppKit
OPENGL = -framework OpenGL
GNL_DIR = lib/get_next_line

SRC_DIR = raycasting
SRCS = raycasting/help_func.c raycasting/hooks.c \
		raycasting/horizental2d.c raycasting/init_mlx.c \
		raycasting/map.c raycasting/palyer_mov.c \
		raycasting/set_player.c raycasting/set_rays.c \
		raycasting/vertical2d.c main.c raycasting/facing.c

SRC_PARS = parsing/pars_map.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	lib/ft_strlen.c lib/ft_strncmp.c

OBJS = $(SRCS:%.c=%.o)
OBJSPARS = $(SRC_PARS:%.c=%.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJS) $(OBJSPARS)
	$(CC) $(OBJS) $(OBJSPARS) $(MLX) $(APPKIT) $(OPENGL) -o $(NAME)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJSPARS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re