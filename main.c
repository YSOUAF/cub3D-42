#include "cub3d.h"

// int main(void)
// {
//     t_cub3d cub;

//     cub.keys = (t_keys){0};
//     init_map(&cub);
//     init_player(&cub);
//     init_mlx(&cub);
//     setup_hooks(&cub);
//     mlx_loop(cub.mlx);
//     return (0);
// }

void print_map(char **map_data)
{
	int i = 0;
	if (!map_data)
	{
		printf("map_data is NULL\n");
		return;
	}
	while (map_data[i])
	{
		printf("[%s]\n", map_data[i]);
		i++;
	}
	printf("-- end of map (%d lines) --\n", i);
}

void f(void) { system("lsof -c cub3d"); }

int main (int ac, char **av)
{

	
	atexit(f);
	if (ac != 2 || !check_ext(av[1]))
		return (printf("Error:\ninvalid ext or num arg"),1);

	t_map *map = malloc(sizeof(t_map));
	if (!map)
	{
		return (printf("Error :\nallocation struct failled\n"), 1);
	}
	ft_memset(map, 0, sizeof(t_map));
	if (!allocate_map(av[1], &map) || !map->height)
		return (printf("Error :\ninvalid map1"), 1);
	if (!parss_map(map->data))
		return (printf("Error :\ninvalid map2"), 1);
	printf("width => %d\n",map->width);
	printf("height => %d\n",map->height);
	printf("NO: -> %s\n", map->path_no);
	printf("SO: -> %s\n", map->path_so);
	printf("WE: -> %s\n", map->path_we);
	printf("EA: -> %s\n", map->path_ea);
	printf("F: -> %u\n", map->color_f);
	printf("C: -> %u\n", map->color_c);
	print_map(map->data);
	return (0);
}
