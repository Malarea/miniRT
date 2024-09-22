/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:05:53 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:31:49 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	matrix_transform_camera(t_camera *c, t_point from, t_vector dir)
{
	c->transform = view_transform(from, dir);
	if (!c->transform)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_camera(char **args, t_scene **scene)
{
	static int	dup;
	t_camera	*c;
	t_vector	v;
	t_point		p;

	if (check_args(dup, C, 3, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	c = ft_calloc(1, sizeof(*c));
	if (!c)
		return (EXIT_FAILURE);
	(*scene)->camera = c;
	if (check_coordinates(args[0], &p, C) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	c->position = p;
	if (check_orientation(args[1], &v, C) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	c->direction = normalize(v);
	if (check_float_range(args[2], 0, 180, C) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	c->fov = ft_atoi(args[2]);
	if (matrix_transform_camera(c, p, v) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	dup = 1;
	return (EXIT_SUCCESS);
}
