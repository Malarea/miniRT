/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:10:28 by agranger          #+#    #+#             */
/*   Updated: 2023/01/06 11:57:58 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_plane(t_object *p, t_ray *r, t_intersection **first)
{
	t_intersection	*x;
	float			t;

	if (fabs(r->direction.y) < EPSILON)
		return (EXIT_SUCCESS);
	t = -r->origin.y / r->direction.y;
	x = create_intersection(t, p);
	if (!x)
		return (EXIT_FAILURE);
	intersection_add_sort(first, x);
	return (EXIT_SUCCESS);
}
