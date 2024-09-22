/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:58:55 by agranger          #+#    #+#             */
/*   Updated: 2023/01/19 18:39:05 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_orientation(char *arg, t_vector *v, char *elem)
{
	char	**orient;
	float	val[3];
	int		i;

	orient = ft_split(arg, ",");
	if (!orient)
		return (EXIT_FAILURE);
	if (ft_arrlen(orient) != 3)
	{
		free_arr_of_str(orient);
		return (error_parsing(ERR_FORMAT_ORIENT, elem));
	}
	i = 0;
	while (orient[i])
	{
		val[i] = ft_atof(orient[i]);
		if (str_is_float(orient[i]) == FALSE || val[i] < -1.0 || val[i++] > 1.0)
		{
			free_arr_of_str(orient);
			return (error_parsing(ERR_FORMAT_ORIENT, elem));
		}
	}
	*v = (t_vector){val[0], val[1], val[2], VECTOR};
	free_arr_of_str(orient);
	return (EXIT_SUCCESS);
}

int	check_coordinates(char *arg, t_point *p, char *elem)
{
	char	**coord;
	int		i;

	coord = ft_split(arg, ",");
	if (!coord)
		return (EXIT_FAILURE);
	if (ft_arrlen(coord) != 3)
	{
		free_arr_of_str(coord);
		return (error_parsing(ERR_FORMAT_COORD, elem));
	}
	i = 0;
	while (coord[i])
	{
		if (str_is_float(coord[i]) == FALSE)
		{
			free_arr_of_str(coord);
			return (error_parsing(ERR_FORMAT_COORD, elem));
		}
		i++;
	}
	*p = (t_point){ft_atof(coord[0]), ft_atof(coord[1]),
		ft_atof(coord[2]), POINT};
	free_arr_of_str(coord);
	return (EXIT_SUCCESS);
}

int	check_color_format(char *arg, t_color *c, char *elem)
{
	char	**color;
	int		i;
	int		rgb[3];

	color = ft_split(arg, ",");
	if (!color)
		return (EXIT_FAILURE);
	if (ft_arrlen(color) != 3)
	{
		free_arr_of_str(color);
		return (error_parsing(ERR_FORMAT_COLOR, elem));
	}
	i = 0;
	while (color[i])
	{
		rgb[i] = ft_atoi(color[i]);
		if (str_is_int(color[i]) == FALSE || rgb[i] < 0 || rgb[i++] > 255)
		{
			free_arr_of_str(color);
			return (error_parsing(ERR_FORMAT_COLOR, elem));
		}
	}
	set_color(c, rgb[0], rgb[1], rgb[2]);
	free_arr_of_str(color);
	return (EXIT_SUCCESS);
}

int	check_float_range(char *ratio, float min, float max, char *elem)
{
	float	value;

	if (str_is_float(ratio) == TRUE)
		value = ft_atof(ratio);
	else
		return (error_parsing(ERR_FLOAT_INF, elem));
	if (min != max && (value < min || value > max))
		return (error_parsing(ERR_RANGE_INF, elem));
	return (EXIT_SUCCESS);
}
