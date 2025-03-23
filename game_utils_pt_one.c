/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_pt_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 11:14:45 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/23 11:14:45 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <stdio.h>

static void	load_textures(t_game *game_data);
static void	check_textures(t_game *game_data);
static int	input_handler(int key, t_game *game_data);
static int	player_pos_updater(int key, t_game *game_data);

void	run_game(t_game *game_data)
{
	game_data->mlx_ptr = mlx_init();
	if (!game_data->mlx_ptr)
		free_data_and_fail_exit(game_data, game_data->map_height, 2);
	game_data->mlx_window = mlx_new_window(game_data->mlx_ptr, game_data->map_width * PIXEL, game_data->map_height * PIXEL, "so_long");
	if (!game_data->mlx_window)
	{
		mlx_destroy_display(game_data->mlx_ptr);
		free(game_data->mlx_ptr);
		free_data_and_fail_exit(game_data, game_data->map_height, 2);
	}
	load_textures(game_data);
	mlx_hook(game_data->mlx_window, 2, 1, input_handler, game_data);
	mlx_hook(game_data->mlx_window, CLOSE_WINDOW, 0, exit_game, game_data);
	mlx_loop_hook(game_data->mlx_ptr, render_map, game_data);
	mlx_loop(game_data->mlx_ptr);
}

static void	load_textures(t_game *game_data)
{
	int	width;
	int	height;

	game_data->background_texture = mlx_xpm_file_to_image(game_data->mlx_ptr, "textures/background.xpm", &width,
			&height);
	game_data->exit_texture = mlx_xpm_file_to_image(game_data->mlx_ptr, "textures/exitoff.xpm",
			&width, &height);
	game_data->collectible_texture = mlx_xpm_file_to_image(game_data->mlx_ptr, "textures/collectible.xpm",
			&width, &height);
	game_data->player_right_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
			"textures/player_right.xpm", &width, &height);
	game_data->player_left_texture = mlx_xpm_file_to_image(game_data->mlx_ptr,
			"textures/player_left.xpm", &width, &height);
	game_data->wall_texture = mlx_xpm_file_to_image(game_data->mlx_ptr, "textures/wall.xpm",
			&width, &height);
	game_data->player_active_texture = game_data->player_right_texture;
	check_textures(game_data);
}

static void	check_textures(t_game *game_data)
{
	if (!game_data->background_texture || !game_data->exit_texture || !game_data->collectible_texture
		|| !game_data->player_right_texture || !game_data->player_left_texture || !game_data->wall_texture)
	{
		if (game_data->collectible_texture)
			mlx_destroy_image(game_data->mlx_ptr, game_data->collectible_texture);
		if (game_data->wall_texture)
			mlx_destroy_image(game_data->mlx_ptr, game_data->wall_texture);
		if (game_data->background_texture)
			mlx_destroy_image(game_data->mlx_ptr, game_data->background_texture);
		if (game_data->player_left_texture)
			mlx_destroy_image(game_data->mlx_ptr, game_data->player_left_texture);
		if (game_data->player_right_texture)
			mlx_destroy_image(game_data->mlx_ptr, game_data->player_right_texture);
		if (game_data->exit_texture)
			mlx_destroy_image(game_data->mlx_ptr, game_data->exit_texture);
		mlx_destroy_window(game_data->mlx_ptr, game_data->mlx_window);
		mlx_destroy_display(game_data->mlx_ptr);
		free(game_data->mlx_ptr);
		free_game_data(game_data, game_data->map_height, 2);
		exit(EXIT_SUCCESS);
	}
}

static int	input_handler(int key, t_game *game_data)
{
	int	move_flag;

	move_flag = 0;
	if (key == KEY_ESC)
		exit_game(game_data);
	else if (key == KEY_W && game_data->map[game_data->player_loc_y - 1][game_data->player_loc_x] != '1')
		move_flag = player_pos_updater(KEY_W, game_data);
	else if (key == KEY_S && game_data->map[game_data->player_loc_y + 1][game_data->player_loc_x] != '1')
		move_flag = player_pos_updater(KEY_S, game_data);
	else if (key == KEY_A && game_data->map[game_data->player_loc_y][game_data->player_loc_x - 1] != '1')
		move_flag = player_pos_updater(KEY_A, game_data);
	else if (key == KEY_D && game_data->map[game_data->player_loc_y][game_data->player_loc_x + 1] != '1')
		move_flag = player_pos_updater(KEY_D, game_data);
	event_handler(move_flag, game_data);
	return (0);
}

static int	player_pos_updater(int key, t_game *game_data)
{
	if (key == KEY_W)
		game_data->player_loc_y--;
	else if (key == KEY_S)
		game_data->player_loc_y++;
	else if (key == KEY_A)
	{
		game_data->player_active_texture = game_data->player_left_texture;
		game_data->player_loc_x--;
	}
	else if (key == KEY_D)
	{
		game_data->player_active_texture = game_data->player_right_texture;
		game_data->player_loc_x++;
	}
	return (1);
}
