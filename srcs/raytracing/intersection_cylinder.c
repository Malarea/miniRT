/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 11:24:34 by agranger          #+#    #+#             */
/*   Updated: 2023/01/06 16:24:17 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	discr_cylinder(float *a, float *b, t_ray *r)
{
	float	c;

	*a = r->direction.x * r->direction.x + r->direction.z * r->direction.z;
	if (*a < EPSILON)
		return (0);
	*b = 2 * r->origin.x * r->direction.x
		+ 2 * r->origin.z * r->direction.z;
	c = r->origin.x * r->origin.x + r->origin.z * r->origin.z - 1;
	return (*b * *b - 4 * *a * c);
}

int	check_min_max_cylinder(t_intersection **first, float t[2],
	t_ray *r, t_object *c)
{
	t_intersection	*x0;
	t_intersection	*x1;
	float			y0;
	float			y1;

	y0 = r->origin.y + t[0] * r->direction.y;
	if (c->attr.cylinder.min < y0 && y0 < c->attr.cylinder.max)
	{
		x0 = create_intersection(t[0], c);
		if (!x0)
			return (EXIT_FAILURE);
		intersection_add_sort(first, x0);
	}
	y1 = r->origin.y + t[1] * r->direction.y;
	if (c->attr.cylinder.min < y1 && y1 < c->attr.cylinder.max)
	{
		x1 = create_intersection(t[1], c);
		if (!x1)
			return (EXIT_FAILURE);
		intersection_add_sort(first, x1);
	}
	return (EXIT_SUCCESS);
}

t_bool	check_cap(t_ray *r, float t)
{
	float	x;
	float	z;

	x = r->origin.x + t * r->direction.x;
	z = r->origin.z + t * r->direction.z;
	if ((x * x + z * z) <= 1)
		return (TRUE);
	return (FALSE);
}

int	intersect_caps(t_object *c, t_ray *r, t_intersection **first)
{
	float			t;
	t_intersection	*x0;
	t_intersection	*x1;

	if (c->attr.cylinder.closed != TRUE || fabs(r->direction.y) < EPSILON)
		return (EXIT_SUCCESS);
	t = (c->attr.cylinder.min - r->origin.y) / r->direction.y;
	if (check_cap(r, t) == TRUE)
	{
		x0 = create_intersection(t, c);
		if (!x0)
			return (EXIT_FAILURE);
		intersection_add_sort(first, x0);
	}
	t = (c->attr.cylinder.max - r->origin.y) / r->direction.y;
	if (check_cap(r, t) == TRUE)
	{
		x1 = create_intersection(t, c);
		if (!x1)
			return (EXIT_FAILURE);
		intersection_add_sort(first, x1);
	}
	return (EXIT_SUCCESS);
}

int	intersect_cylinder(t_object *c, t_ray *r, t_intersection **first)
{
	t_quadratic		q;
	float			t[2];

	q.delta = discr_cylinder(&q.a, &q.b, r);
	if (q.delta < 0)
		return (intersect_caps(c, r, first));
	t[0] = (-q.b - sqrt(q.delta)) / (2 * q.a);
	t[1] = (-q.b + sqrt(q.delta)) / (2 * q.a);
	if (t[0] < t[1])
		swap(&t[0], &t[1]);
	if (check_min_max_cylinder(first, t, r, c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (intersect_caps(c, r, first));
}
