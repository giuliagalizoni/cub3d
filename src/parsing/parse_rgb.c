/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggalizon <ggalizon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:19:40 by ggalizon          #+#    #+#             */
/*   Updated: 2025/10/14 16:20:29 by ggalizon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_rgb_format(char *rgb_str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (rgb_str[i])
	{
		if (rgb_str[i] == ',')
		{
			if (rgb_str[i + 1] == ',')
				return (0);
			count++;
		}
		i++;
	}
	if (count != 2)
		return (0);
	return (1);
}

static int	check_empty_rgb(char **rgb_arr)
{
	int	i;
	int	j;
	int	not_empty;

	i = 0;
	while (i < 3)
	{
		if (!rgb_arr[i][0])
			return (0);
		j = 0;
		not_empty = 0;
		while (rgb_arr[i][j])
		{
			if (rgb_arr[i][j] != ' ' && rgb_arr[i][j] != '\t')
				not_empty = 1;
			j++;
		}
		if (!not_empty)
			return (0);
		i++;
	}
	return (1);
}

static int	parse_rgb(char *rgb_str)
{
	int		r;
	int		g;
	int		b;
	char	**rgb_arr;

	if (!check_rgb_format(rgb_str))
		return (-1);
	rgb_arr = ft_split(rgb_str, ',');
	if (!rgb_arr || arr_size(rgb_arr) != 3 || !check_empty_rgb(rgb_arr))
	{
		if (rgb_arr)
			free_arr(rgb_arr);
		return (-1);
	}
	r = ft_atoi(rgb_arr[0]);
	g = ft_atoi(rgb_arr[1]);
	b = ft_atoi(rgb_arr[2]);
	free_arr(rgb_arr);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

int	set_rgb(int *field, char *rgb_str)
{
	int	color;

	if (*field != -1)
		return (-2);
	color = parse_rgb(rgb_str);
	if (color == -1)
		return (-1);
	*field = color;
	return (1);
}
