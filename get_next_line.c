/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 04:24:51 by aaycan            #+#    #+#             */
/*   Updated: 2025/03/26 17:47:23 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>
#include <stdlib.h>

static char	*ft_set_left_characters(int fd, char *left_c);
static char	*ft_create_output_line(char *left_c);
static char	*ft_update_left_characters(char *left_c);
static char	*ft_validate_variables_and_join(char *left_c, char *tmp);

char	*get_next_line(int fd)
{
	char		*output_line;
	static char	*left_c;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(left_c);
		return (NULL);
	}
	left_c = ft_set_left_characters(fd, left_c);
	if (!left_c)
		return (NULL);
	output_line = ft_create_output_line(left_c);
	left_c = ft_update_left_characters(left_c);
	return (output_line);
}

static char	*ft_set_left_characters(int fd, char *left_c)
{
	int		read_bytes;
	char	*tmp;

	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
	{
		free(left_c);
		return (NULL);
	}
	read_bytes = 1337;
	while (read_bytes != 0 && !ft_check_newline_existence(left_c))
	{
		read_bytes = read(fd, tmp, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(left_c);
			free(tmp);
			return (NULL);
		}
		tmp[read_bytes] = '\0';
		left_c = ft_validate_variables_and_join(left_c, tmp);
	}
	free(tmp);
	return (left_c);
}

static char	*ft_create_output_line(char *left_c)
{
	char	*line;
	int		i;

	i = 0;
	if (!left_c[i])
		return (NULL);
	if (ft_strchr(left_c, '\n'))
		line = malloc(ft_count_to_end_of_line(left_c) + 2);
	else
		line = malloc(ft_count_to_end_of_line(left_c) + 1);
	if (!line)
	{
		free(left_c);
		return (NULL);
	}
	i = -1;
	while (left_c[++i] != '\n' && left_c[i] != '\0')
		line[i] = left_c[i];
	if (left_c[i] == '\n')
	{
		line[i] = left_c[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*ft_update_left_characters(char *left_c)
{
	char	*updated_left_c;
	int		i;
	int		j;

	i = ft_count_to_end_of_line(left_c);
	if (!left_c[i] && left_c)
	{
		free(left_c);
		return (NULL);
	}
	updated_left_c = malloc(ft_strlen(left_c) - i + 1);
	if (!updated_left_c)
	{
		free(left_c);
		return (NULL);
	}
	i++;
	j = 0;
	while (left_c[i])
		updated_left_c[j++] = left_c[i++];
	updated_left_c[j] = '\0';
	free(left_c);
	return (updated_left_c);
}

static char	*ft_validate_variables_and_join(char *left_c, char *tmp)
{
	char	*joined_str;

	if (!left_c)
	{
		left_c = malloc(1);
		left_c[0] = '\0';
	}
	if (!left_c || !tmp)
		return (NULL);
	joined_str = ft_strjoin_modified(left_c, tmp);
	return (joined_str);
}
