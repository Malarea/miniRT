/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:36:54 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 13:20:44 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	discr_cone(t_quadratic *q, t_ray *r)
{
	q->a = pow(r->direction.x, 2) - pow(r->direction.y, 2)
		+ pow(r->direction.z, 2);
	q->b = 2 * r->origin.x * r->direction.x
		- 2 * r->origin.y * r->direction.y
		+ 2 * r->origin.z * r->direction.z;
	q->c = pow(r->origin.x, 2) - pow(r->origin.y, 2) + pow(r->origin.z, 2);
	q->a = floor(q->a * 1000000) / 1000000;
	return (pow(q->b, 2) - 4 * q->a * q->c);
}

int	check_min_max_cone(t_intersection **first, float t[2],
	t_ray *r, t_object *c)
{
	t_intersection	*x0;
	t_intersection	*x1;
	float			y0;
	float			y1;

	y0 = r->origin.y + t[0] * r->direction.y;
	if (c->attr.cone.min < y0 && y0 < c->attr.cone.max)
	{
		x0 = create_intersection(t[0], c);
		if (!x0)
			return (EXIT_FAILURE);
		intersection_add_sort(first, x0);
	}
	y1 = r->origin.y + t[1] * r->direction.y;
	if (c->attr.cone.min < y1 && y1 < c->attr.cone.max)
	{
		x1 = create_intersection(t[1], c);
		if (!x1)
			return (EXIT_FAILURE);
		intersection_add_sort(first, x1);
	}
	return (EXIT_SUCCESS);
}

int	intersect_cone(t_object *c, t_ray *r, t_intersection **first)
{
	t_quadratic		q;
	float			t[2];
	t_intersection	*x;

	q.delta = discr_cone(&q, r);
	if (q.a < EPSILON && q.a > -EPSILON)
	{
		if (q.b < EPSILON && q.b > -EPSILON)
			return (EXIT_SUCCESS);
		t[0] = -q.c / (2 * q.b);
		x = create_intersection(t[0], c);
		if (!x)
			return (EXIT_FAILURE);
		intersection_add_sort(first, x);
		return (EXIT_SUCCESS);
	}
	if (q.delta < 0)
		return (EXIT_SUCCESS);
	t[0] = (-q.b - sqrt(q.delta)) / (2 * q.a);
	t[1] = (-q.b + sqrt(q.delta)) / (2 * q.a);
	if (t[0] < t[1])
		swap(&t[0], &t[1]);
	if (check_min_max_cone(first, t, r, c) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
