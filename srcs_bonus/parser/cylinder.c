/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 18:28:28 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 02:07:37 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	matrix_transform_cylinder(t_object *cy, char **args)
{
	t_point		p;
	t_vector	v;

	if (check_coordinates(args[0], &p, CY) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cy->position = p;
	if (check_orientation(args[1], &v, CY) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cy->attr.cylinder.orientation = normalize(v);
	if (check_float_range(args[2], 0, 0, CY) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cy->attr.cylinder.diameter = ft_atof(args[2]);
	if (check_float_range(args[3], 0, 0, CY) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cy->attr.cylinder.height = ft_atof(args[3]);
	cy->attr.cylinder.min = cy->position.y - (cy->attr.cylinder.height / 2);
	cy->attr.cylinder.max = cy->position.y + (cy->attr.cylinder.height / 2);
	cy->attr.cylinder.closed = TRUE;
	cy->transform = compute_transform_cylinder(cy->attr.cylinder.orientation,
			cy->position, cy->attr.cylinder.diameter);
	if (!cy->transform)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_cylinder(char **args, t_scene **scene)
{
	t_object	*cy;
	int			expected[2];

	expected[0] = 5;
	expected[1] = 6;
	if (check_args_bonus(0, CY, expected, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cy = ft_calloc(1, sizeof(*cy));
	if (!cy)
		return (EXIT_FAILURE);
	cy->type = CYLINDER;
	cy->next = NULL;
	cy->prev = NULL;
	add_back_object(&(*scene)->obj, cy);
	if (matrix_transform_cylinder(cy, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cy->material = create_material(GLOSSY);
	if (!cy->material)
		return (EXIT_FAILURE);
	if (parse_color(cy, &args[4], CY) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	cy->intersect = intersect_cylinder;
	cy->normal_at = normal_at_cylinder;
	cy->material->uv_map_checker = cylindrical_checker_map;
	return (EXIT_SUCCESS);
}
