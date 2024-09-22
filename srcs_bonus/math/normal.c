/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 15:57:12 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 12:49:42 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	normal_at_sphere(t_object *s, t_point objp)
{
	(void)s;
	return (objp - (t_point){0, 0, 0, POINT});
}

t_vector	normal_at_plane(t_object *p, t_point objp)
{
	(void)p;
	(void)objp;
	return ((t_vector){0, 1, 0, VECTOR});
}

t_vector	normal_at_cylinder(t_object *c, t_point objp)
{
	float	dist;

	dist = objp.x * objp.x + objp.z * objp.z;
	if (dist < 1 && objp.y >= c->attr.cylinder.max - EPSILON)
		return ((t_vector){0, 1, 0, VECTOR});
	else if (dist < 1 && objp.y <= c->attr.cylinder.min + EPSILON)
		return ((t_vector){0, -1, 0, VECTOR});
	return ((t_vector){objp.x, 0, objp.z, VECTOR});
}

t_vector	normal_at_cone(t_object *c, t_point objp)
{
	float	dist;
	float	y;

	dist = objp.x * objp.x + objp.z * objp.z;
	if (dist < 1 && objp.y >= c->attr.cylinder.max - EPSILON)
		return ((t_vector){0, 1, 0, VECTOR});
	else if (dist < 1 && objp.y <= c->attr.cylinder.min + EPSILON)
		return ((t_vector){0, -1, 0, VECTOR});
	y = sqrt(pow(objp.x, 2) + pow(objp.z, 2));
	if (objp.y > 0)
		y = -y;
	return ((t_vector){objp.x, y, objp.z, VECTOR});
}

t_vector	normal_at(t_object *obj, t_point p)
{
	t_point		objp;
	t_vector	n;
	t_vector	objn;
	t_matrix	*transp;

	objp = matrix_tuple_mult(obj->transform, p);
	objn = obj->normal_at(obj, objp);
	transp = transpose(obj->transform);
	if (!transp)
		return ((t_vector){0, 0, 0, ERROR});
	n = matrix_tuple_mult(transp, objn);
	n.w = 0;
	free_matrix(&transp);
	return (normalize(n));
}
