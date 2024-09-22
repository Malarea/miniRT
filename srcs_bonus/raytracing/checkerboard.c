/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:18:44 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 03:23:19 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	spherical_checker_map(t_point p, float *u, float *v)
{
	float	theta;
	float	radius;
	float	phi;
	float	raw_u;

	theta = atan2(p.x, p.z);
	p.w = VECTOR;
	radius = magnitude(p);
	phi = acos(p.y / radius);
	raw_u = theta / (2 * M_PI);
	*u = 1 - (raw_u + 0.5);
	*v = 1 - phi / M_PI;
	*u = floor(*u * 20);
	*v = floor(*v * 10);
	return ;
}

void	planar_checker_map(t_point p, float *u, float *v)
{
	*u = fmod(p.x, 1);
	*v = fmod(p.z, 1);
	*u = floor(*u * 2);
	*v = floor(*v * 2);
	return ;
}

void	cylindrical_checker_map(t_point p, float *u, float *v)
{
	float	theta;
	float	raw_u;

	theta = atan2(p.x, p.z);
	raw_u = theta / (2 * M_PI);
	*u = 1 - (raw_u + 0.5);
	*v = fmod(p.y, 1);
	*u = floor(*u * 28);
	*v = floor(*v * 4);
	return ;
}

t_color	uv_checkers(t_object *obj, t_point p)
{
	float	u;
	float	v;
	t_point	obj_p;

	obj_p = matrix_tuple_mult(obj->transform, p);
	obj->material->uv_map_checker(obj_p, &u, &v);
	if (fmod(u + v, 2) == 0)
		return (obj->material->color);
	return (obj->material->color2);
}
