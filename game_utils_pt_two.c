/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils_pt_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:40:09 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/08 15:04:13 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>

static int	input_handler(int key, t_game *game_data);
static void	event_handler(int move_flag, t_game *game_data);
static int	player_pos_updater(int key, t_game *game_data);
static void	last_move_exit(t_game *game_data);

void	game_loop(t_game *game_data)
{
	mlx_hook(game_data->mlx_window, 2, 1, input_handler, game_data);
	mlx_hook(game_data->mlx_window, CLOSE_WINDOW, 0, exit_game, game_data);
	mlx_loop(game_data->mlx_ptr);
}

static int	input_handler(int key, t_game *game_data)
{
	int	move_flag;

	move_flag = 0;
	if (key == KEY_ESC)
		exit_game(game_data);
	else if (key == KEY_W && game_data->map[game_data->player_loc_y - 1]
		[game_data->player_loc_x] != '1')
		move_flag = player_pos_updater(KEY_W, game_data);
	else if (key == KEY_S && game_data->map[game_data->player_loc_y + 1]
		[game_data->player_loc_x] != '1')
		move_flag = player_pos_updater(KEY_S, game_data);
	else if (key == KEY_A && game_data->map[game_data->player_loc_y]
		[game_data->player_loc_x - 1] != '1')
		move_flag = player_pos_updater(KEY_A, game_data);
	else if (key == KEY_D && game_data->map[game_data->player_loc_y]
		[game_data->player_loc_x + 1] != '1')
		move_flag = player_pos_updater(KEY_D, game_data);
	event_handler(move_flag, game_data);
	if (move_flag != 0)
		render_map(game_data);
	return (0);
}

static void	event_handler(int move_flag, t_game *game_data)
{
	int	i;
	int	h;

	i = 0;
	if (game_data->map[game_data->player_loc_y][game_data->player_loc_x] == 'C')
	{
		game_data->map[game_data->player_loc_y][game_data->player_loc_x] = '0';
		game_data->collectible_count--;
	}
	if (game_data->collectible_count == 0
		&& game_data->map[game_data->player_loc_y]
		[game_data->player_loc_x] == 'E')
		last_move_exit(game_data);
	if (move_flag != 0)
	{
		game_data->move_count++;
		ft_putnbr(game_data->move_count);
		write(1, "\n", 1);
	}
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

static void	last_move_exit(t_game *game_data)
{
	game_data->move_count++;
	write(1, "Total Move Count: ", 18);
	ft_putnbr(game_data->move_count);
	write(1, "\n", 1);
	exit_game(game_data);
}
