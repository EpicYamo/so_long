/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_pt_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:00:51 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/21 16:00:51 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

static void	fill_map_element_info_pt_two(t_game *game_data, int loc_x, int loc_y, char type);
static void	fill_map_element_info_pt_three(t_game *game_data);

void	check_forbidden_elements(t_game *game_data, int line_count)
{
	int	i;
	int	j;

	i = 0;
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j])
		{
			if ((game_data->map[i][j] != '1') && (game_data->map[i][j] != '0')
				&& (game_data->map[i][j] != 'E') && (game_data->map[i][j] != 'P')
				&& (game_data->map[i][j] != 'C'))
				free_data_and_fail_exit(game_data, line_count, 1);
			j++;
		}
		i++;
	}
}

void	fill_map_element_info(t_game *game_data, int line_count)
{
	int	i;
	int	j;

	j = 0;
	game_data->map_height = line_count;
	while (game_data->map[0][j])
		j++;
	game_data->map_width = j;
	i = 0;
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j])
		{
			if (game_data->map[i][j] == 'E' || game_data->map[i][j] == 'P')
				fill_map_element_info_pt_two(game_data, j, i, game_data->map[i][j]);
			j++;
		}
		i++;
	}
	fill_map_element_info_pt_three(game_data);
}

static void	fill_map_element_info_pt_two(t_game *game_data, int loc_x, int loc_y, char type)
{
	if (type == 'E')
	{
		game_data->exit_loc_x = loc_x;
		game_data->exit_loc_y = loc_y;
	}
	if (type == 'P')
	{
		game_data->player_loc_x = loc_x;
		game_data->player_loc_y = loc_y;
	}
}

static void	fill_map_element_info_pt_three(t_game *game_data)
{
	int	i;
	int	j;
	int	c_count;

	i = 0;
	c_count = 0;
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j])
		{
			if (game_data->map[i][j] == 'C')
				c_count += 1;
			j++;
		}
		i++;
	}
	game_data->collectible_count = c_count;
	game_data->collectible_loc_x = malloc(sizeof(int) * game_data->collectible_count);
	if (!game_data->collectible_loc_x)
		free_data_and_fail_exit(game_data, game_data->map_height, 1);
	game_data->collectible_loc_y = malloc(sizeof(int) * game_data->collectible_count);
	if (!game_data->collectible_loc_y)
		free_data_and_fail_exit(game_data, game_data->map_height, 3);
	fill_map_element_info_pt_four(game_data);
}
