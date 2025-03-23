/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_pt_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:44:02 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/19 17:44:02 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

static void	check_map_borders(t_game *game_data, int line_count);
static void	check_map_geometry(t_game *game_data, int line_count);
static void	check_map_elements(t_game *game_data, int line_count);
static void	init_map_elements(int *i, int *e_counter, int *p_counter, int *c_counter);

void	check_and_finish_map(t_game *game_data, int line_count)
{
	check_map_geometry(game_data, line_count);
	check_map_borders(game_data, line_count);
	check_map_elements(game_data, line_count);
	check_forbidden_elements(game_data, line_count);
	fill_map_element_info(game_data, line_count);
	check_element_reachability(game_data);
}

static void	check_map_geometry(t_game *game_data, int line_count)
{
	int	width;
	int	i;
	int	j;

	i = 0;
	width = 0;
	while (game_data->map[0][width])
		width++;
	if (width < 5)
		free_data_and_fail_exit(game_data, line_count, 1);
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j])
			j++;
		if (j != width)
			free_data_and_fail_exit(game_data, line_count, 1);
		i++;
	}
}

static void	check_map_borders(t_game *game_data, int line_count)
{
	int	i;
	int	j;

	i = 0;
	while (game_data->map[0][i])
		if (game_data->map[0][i++] != '1')
			free_data_and_fail_exit(game_data, line_count, 1);
	j = i;
	i = 0;
	while (game_data->map[line_count - 1][i])
		if (game_data->map[line_count - 1][i++] != '1')
			free_data_and_fail_exit(game_data, line_count, 1);
	i = 0;
	while (game_data->map[i])
		if (game_data->map[i++][0] != '1')
			free_data_and_fail_exit(game_data, line_count, 1);
	i = 0;
	while (game_data->map[i])
		if (game_data->map[i++][j - 1] != '1')
			free_data_and_fail_exit(game_data, line_count, 1);
}

static void	check_map_elements(t_game *game_data, int line_count)
{
	int	i;
	int	j;
	int	e_counter;
	int	p_counter;
	int	c_counter;

	init_map_elements(&i, &e_counter, &p_counter, &c_counter);
	while (game_data->map[i])
	{
		j = 0;
		while (game_data->map[i][j])
		{
			if (game_data->map[i][j] == 'E')
				e_counter++;
			if (game_data->map[i][j] == 'P')
				p_counter++;
			if (game_data->map[i][j] == 'C')
				c_counter++;
			j++;
		}
		i++;
	}
	if ((e_counter != 1) || (p_counter != 1) || (c_counter < 1))
		free_data_and_fail_exit(game_data, line_count, 1);
}

static void	init_map_elements(int *i, int *e_counter, int *p_counter, int *c_counter)
{
	*i = 0;
	*e_counter = 0;
	*p_counter = 0;
	*c_counter = 0;
}
