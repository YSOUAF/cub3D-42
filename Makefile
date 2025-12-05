CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes -fsanitize=address -g

MLX_DIR = lib/MLX42

MLX_FLAGS = -I $(MLX_DIR)/include/MLX42 -lm -lGL -lglfw

GNL_DIR = lib/get_next_line
MLX_LIB	= $(MLX_DIR)/build/libmlx42.a

# SRC_DIR = raycasting
SRCS_RAYCAST = raycasting/help_func.c raycasting/hooks.c \
		raycasting/horizental2d.c raycasting/init_mlx.c \
		raycasting/map.c raycasting/palyer_mov.c \
		raycasting/set_player.c raycasting/set_rays.c \
		raycasting/vertical2d.c main.c raycasting/facing.c \
		raycasting/set_rays2.c raycasting/player_mov2.c

SRC_PARS = parsing/pars_map.c parsing/utilis_map.c parsing/pars_tex_fc.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
	lib/ft_strlen.c lib/ft_strncmp.c lib/ft_split.c lib/ft_atoi.c lib/ft_strdup.c lib/ft_calloc.c lib/ft_memcpy.c \
	lib/ft_memset.c lib/is_digit.c lib/valid_num.c parsing/helper_function.c parsing/check_space.c texture/load_texture.c texture/load_texture_utilis.c texture/free_func.c   

SRCS = ${SRC_PARS} ${SRCS_RAYCAST}
OBJS = $(SRCS:%.c=%.o)
# OBJSPARS = $(SRC_PARS:%.c=%.o)

NAME = cub3d

all: $(MLX_LIB) $(NAME)

$(MLX_DIR):
	@echo "Cloning MLX Library"
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)

$(MLX_LIB): $(MLX_DIR)
	cd $(MLX_DIR) && cmake -B build -Wno-dev && cmake --build build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)

%.o: %.c includes/cub3d.h
	$(CC) $(CFLAGS) -I lib/MLX42/include/MLX42 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
