/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:04:16 by agranger          #+#    #+#             */
/*   Updated: 2023/01/24 18:13:41 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	*create_ray(t_point p, t_vector v)
{
	t_ray	*r;

	r = malloc(sizeof(*r));
	if (!r)
		return (NULL);
	r->origin = p;
	r->direction = v;
	return (r);
}

t_point	position(t_ray *r, float t)
{
	return (r->origin + r->direction * t);
}

t_ray	*transform(t_ray *r1, t_matrix *m)
{
	t_ray		*r2;
	t_point		p;
	t_vector	v;

	p = matrix_tuple_mult(m, r1->origin);
	v = matrix_tuple_mult(m, r1->direction);
	r2 = create_ray(p, v);
	if (!r2)
		return (NULL);
	return (r2);
}

t_ray	*ray_for_pixel(t_scene *scene, int x, int y)
{
	t_ray		*r;
	float		offset[2];
	t_point		pixel;
	t_point		origin;
	t_matrix	*t;

	t = scene->camera->transform;
	offset[X] = (x + 0.5) * scene->pixel_size;
	offset[Y] = (y + 0.5) * scene->pixel_size;
	pixel = matrix_tuple_mult(t, (t_point){scene->half_w - offset[X],
			scene->half_h - offset[Y], -1, POINT});
	origin = matrix_tuple_mult(t, (t_point){0, 0, 0, POINT});
	r = create_ray(origin, normalize(pixel - origin));
	if (!r)
		return (NULL);
	return (r);
}
