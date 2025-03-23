/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_pt_four.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:23:34 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/21 17:23:34 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

static void	flood_fill(t_game *game_data, t_count_variables *count_vars, int x, int y);
static void	fix_flags_to_original(t_game *game_data);

void	fill_map_element_info_pt_four(t_game *game_data)
{
	int	i;
	int	j;
	int	c_index;

	i = 0;
	c_index = 0;
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j])
		{
			if (game_data->map[i][j] == 'C')
			{
				game_data->collectible_loc_x[c_index] = j;
				game_data->collectible_loc_y[c_index] = i;
				c_index++;
			}
			j++;
		}
		i++;
	}
}

void	check_element_reachability(t_game *game_data)
{
	t_count_variables *count_vars;
	
	count_vars = malloc(sizeof(count_vars));
	if (!count_vars)
		free_data_and_fail_exit(game_data, game_data->map_height, 2);
	count_vars->collectible_count = 0;
	count_vars->exit_count = 0;
	flood_fill(game_data, count_vars, game_data->player_loc_x, game_data->player_loc_y);
	if ((count_vars->collectible_count != game_data->collectible_count) || count_vars->exit_count != 1)
		free_data_and_fail_exit(game_data, game_data->map_height, 2);
	fix_flags_to_original(game_data);
	free(count_vars);
}

static void	flood_fill(t_game *game_data, t_count_variables *count_vars, int x, int y)
{
	if ((x < 0) || (y < 0) || (x >= game_data->map_width)
		|| (y >= game_data->map_height) || ((game_data->map[y][x] != '0')
		&& (game_data->map[y][x] != 'E') && (game_data->map[y][x] != 'P')
		&& (game_data->map[y][x] != 'C')))
		return ;
	else
	{
		if (game_data->map[y][x] == 'E')
			count_vars->exit_count += 1;
		if (game_data->map[y][x] == 'C')
			count_vars->collectible_count += 1;
		game_data->map[y][x] = 'R';
		flood_fill(game_data, count_vars, x, y + 1);
		flood_fill(game_data, count_vars, x, y - 1);
		flood_fill(game_data, count_vars, x + 1, y);
		flood_fill(game_data, count_vars, x - 1, y);
	}
}

static void	fix_flags_to_original(t_game *game_data)
{
	int	i;
	int	j;

	i = 0;
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j])
		{
			if (game_data->map[i][j] == 'R')
				game_data->map[i][j] = '0';
			j++;
		}
		i++;
	}
	game_data->map[game_data->player_loc_y][game_data->player_loc_x] = 'P';
	game_data->map[game_data->exit_loc_y][game_data->exit_loc_x] = 'E';
	i = game_data->collectible_count;
	while (i)
	{
		game_data->map[game_data->collectible_loc_y[i - 1]][game_data->collectible_loc_x[i - 1]] = 'C';
		i--;
	}
}
