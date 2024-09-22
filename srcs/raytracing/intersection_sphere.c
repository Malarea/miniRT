/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:39:00 by agranger          #+#    #+#             */
/*   Updated: 2023/01/05 15:37:30 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	discriminant(t_ray *r, float *a, float *b)
{
	t_point	sp_to_ray;
	float	c;

	sp_to_ray = r->origin - (t_point){0, 0, 0, POINT};
	*a = dot(r->direction, r->direction);
	*b = 2 * dot(r->direction, sp_to_ray);
	c = dot(sp_to_ray, sp_to_ray) - 1;
	return (*b * *b - (4 * *a * c));
}

int	intersect_sphere(t_object *s, t_ray *r, t_intersection **first)
{
	t_quadratic		q;
	t_intersection	*x0;
	t_intersection	*x1;

	q.delta = discriminant(r, &q.a, &q.b);
	if (q.delta < 0)
		return (EXIT_SUCCESS);
	x0 = create_intersection((-q.b - sqrt(q.delta)) / (2 * q.a), s);
	x1 = create_intersection((-q.b + sqrt(q.delta)) / (2 * q.a), s);
	if (!x0 || !x1)
	{
		free_intersection(x0);
		free_intersection(x1);
		return (EXIT_FAILURE);
	}
	intersection_add_sort(first, x0);
	intersection_add_sort(first, x1);
	return (EXIT_SUCCESS);
}
