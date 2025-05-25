/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:14:32 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/11 22:12:25 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <unistd.h>

static void	check_args(int argc, char **argv);
static void	init_game_data(t_game *game_data);
static void	exit_game_unexpectedly(t_game *game_data);

int	main(int argc, char **argv)
{
	t_game	*game_data;
	int		line_count;

	check_args(argc, argv);
	game_data = NULL;
	game_data = malloc(sizeof(t_game));
	if (!game_data)
		fail_exit();
	line_count = count_lines(argv[1], game_data);
	init_game_data(game_data);
	fill_map(game_data, argv);
	check_and_finish_map(game_data, line_count);
	run_game(game_data);
	exit_game_unexpectedly(game_data);
}

static void	check_args(int argc, char **argv)
{
	if ((argc != 2) || (argc == 2 && !argv[1][0]) || (ft_strlen(argv[1]) < 5))
		fail_exit();
	if ((argv[1][ft_strlen(argv[1]) - 1] != 'r')
		|| (argv[1][ft_strlen(argv[1]) - 2] != 'e')
		|| (argv[1][ft_strlen(argv[1]) - 3] != 'b')
		|| (argv[1][ft_strlen(argv[1]) - 4] != '.'))
		fail_exit();
}

static void	init_game_data(t_game *game_data)
{
	game_data->map = NULL;
	game_data->map_width = 0;
	game_data->map_height = 0;
	game_data->player_loc_x = 0;
	game_data->player_loc_y = 0;
	game_data->exit_loc_x = 0;
	game_data->exit_loc_y = 0;
	game_data->move_count = 0;
	game_data->collectible_count = 0;
	game_data->collectible_loc_x = NULL;
	game_data->collectible_loc_y = NULL;
	game_data->mlx_ptr = NULL;
	game_data->mlx_window = NULL;
	game_data->player_right_texture = NULL;
	game_data->player_left_texture = NULL;
	game_data->player_active_texture = NULL;
	game_data->exit_texture = NULL;
	game_data->background_texture = NULL;
	game_data->collectible_texture = NULL;
	game_data->wall_texture = NULL;
}

static void	exit_game_unexpectedly(t_game *game_data)
{
	mlx_destroy_image(game_data->mlx_ptr, game_data->exit_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->wall_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->collectible_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->background_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->player_left_texture);
	mlx_destroy_image(game_data->mlx_ptr, game_data->player_right_texture);
	mlx_destroy_window(game_data->mlx_ptr, game_data->mlx_window);
	mlx_destroy_display(game_data->mlx_ptr);
	free(game_data->mlx_ptr);
	free_game_data(game_data, game_data->map_height, 2);
	write(2, "Game Crashed!\nA problem has occurred with the (mlx loop)\n", 57);
	exit(EXIT_FAILURE);
}
