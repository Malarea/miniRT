/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:47:27 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:16:01 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	matrix_transform_sphere(t_object *s, char **args)
{
	t_point	p;

	if (check_coordinates(args[0], &p, S) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	s->position = p;
	if (check_float_range(args[1], 0.0, FLT_MAX, S) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	s->attr.sphere.diameter = ft_atof(args[1]);
	s->transform = compute_transform_sphere(s->attr.sphere.diameter,
			s->position);
	if (!s->transform)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_sphere(char **args, t_scene **scene)
{
	t_object	*s;
	t_color		c;

	if (check_args(0, S, 3, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	s = ft_calloc(1, sizeof(*s));
	if (!s)
		return (EXIT_FAILURE);
	s->type = SPHERE;
	s->next = NULL;
	s->prev = NULL;
	add_back_object(&(*scene)->obj, s);
	if (matrix_transform_sphere(s, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_color_format(args[2], &c, S) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	s->material = create_material(MATTE);
	if (!s->material)
		return (EXIT_FAILURE);
	s->material->color = c;
	s->intersect = intersect_sphere;
	s->normal_at = normal_at_sphere;
	return (EXIT_SUCCESS);
}
