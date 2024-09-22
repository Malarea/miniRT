/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 11:12:27 by agranger          #+#    #+#             */
/*   Updated: 2023/01/27 16:09:11 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	compare_hit_distance(float distance, t_intersection *x)
{
	t_intersection	*hit;
	int				ret;

	hit = get_hit(x);
	if (hit && hit->t < distance)
		ret = TRUE;
	else
		ret = FALSE;
	free_intersection(x);
	return (ret);
}

int	is_shadowed(t_scene *scene, t_point p)
{
	t_vector		v;
	float			distance;
	t_ray			*r;
	t_intersection	*x;

	if (!scene->light)
		return (FALSE);
	v = scene->light->position - p;
	distance = magnitude(v);
	r = create_ray(p, normalize(v));
	if (!r)
		return (ERR);
	x = NULL;
	if (intersect_scene(scene->obj, r, &x) == EXIT_FAILURE)
	{
		ft_free((void **)&r);
		return (ERR);
	}
	ft_free((void **)&r);
	return (compare_hit_distance(distance, x));
}
