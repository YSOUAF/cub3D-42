CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Iminilibx-linux #-fsanitize=address -g

MLX_DIR = minilibx-linux
MLX = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

GNL_DIR = lib/get_next_line

SRC_DIR = raycasting
SRCS = raycasting/help_func.c raycasting/hooks.c \
		raycasting/horizental2d.c raycasting/init_mlx.c \
		raycasting/map.c raycasting/palyer_mov.c \
		raycasting/set_player.c raycasting/set_rays.c \
		raycasting/vertical2d.c main.c raycasting/facing.c

SRC_PARS = parsing/pars_map.c parsing/utilis_map.c parsing/pars_tex_fc.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	lib/ft_strlen.c lib/ft_strncmp.c lib/ft_split.c lib/ft_atoi.c lib/ft_strdup.c lib/ft_calloc.c lib/ft_memcpy.c \
	lib/ft_memset.c lib/is_digit.c lib/valid_num.c parsing/helper_function.c

OBJS = $(SRCS:%.c=%.o)
OBJSPARS = $(SRC_PARS:%.c=%.o)

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJS) $(OBJSPARS)
	$(CC) $(OBJS) $(OBJSPARS) $(MLX) -o $(NAME)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJSPARS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
