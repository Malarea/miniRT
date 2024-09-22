/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:37:48 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:23:48 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	matrix_transform_plane(t_object *pl, char **args)
{
	t_point		p;
	t_vector	v;

	if (check_coordinates(args[0], &p, P) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pl->position = p;
	if (check_orientation(args[1], &v, P) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pl->attr.plane.orientation = normalize(v);
	pl->transform = compute_transform_plane(pl->attr.plane.orientation,
			pl->position);
	if (!pl->transform)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	create_plane(char **args, t_scene **scene)
{
	t_object	*pl;
	t_color		c;

	if (check_args(0, P, 3, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pl = ft_calloc(1, sizeof(*pl));
	if (!pl)
		return (EXIT_FAILURE);
	pl->type = PLANE;
	pl->next = NULL;
	pl->prev = NULL;
	add_back_object(&(*scene)->obj, pl);
	if (matrix_transform_plane(pl, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_color_format(args[2], &c, P) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pl->material = create_material(MATTE);
	if (!pl->material)
		return (EXIT_FAILURE);
	pl->material->color = c;
	pl->intersect = intersect_plane;
	pl->normal_at = normal_at_plane;
	return (EXIT_SUCCESS);
}
