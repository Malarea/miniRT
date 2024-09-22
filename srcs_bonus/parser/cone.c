/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:28:12 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 02:08:10 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	matrix_transform_cone(t_object *co, char **args)
{
	t_point		p;
	t_vector	v;

	if (check_coordinates(args[0], &p, CO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	co->position = p;
	if (check_orientation(args[1], &v, CO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	co->attr.cone.orientation = normalize(v);
	if (check_float_range(args[2], 0, 0, CO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	co->attr.cone.diameter = ft_atof(args[2]);
	if (check_float_range(args[3], 0, 0, CO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	co->attr.cone.height = ft_atof(args[3]);
	co->attr.cone.min = co->position.y - (co->attr.cone.height / 2);
	co->attr.cone.max = co->position.y + (co->attr.cone.height / 2);
	co->attr.cone.closed = FALSE;
	co->transform = compute_transform_cylinder(co->attr.cone.orientation,
			co->position, co->attr.cone.diameter);
	if (!co->transform)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_cone(char **args, t_scene **scene)
{
	t_object	*co;
	int			expected[2];

	expected[0] = 5;
	expected[1] = 6;
	if (check_args_bonus(0, CO, expected, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	co = ft_calloc(1, sizeof(*co));
	if (!co)
		return (EXIT_FAILURE);
	co->type = CONE;
	co->next = NULL;
	co->prev = NULL;
	add_back_object(&(*scene)->obj, co);
	if (matrix_transform_cone(co, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	co->material = create_material(GLOSSY);
	if (!co->material)
		return (EXIT_FAILURE);
	if (parse_color(co, &args[4], CO) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	co->intersect = intersect_cone;
	co->normal_at = normal_at_cone;
	co->material->uv_map_checker = cylindrical_checker_map;
	return (EXIT_SUCCESS);
}
