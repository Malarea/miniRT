/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:00:39 by agranger          #+#    #+#             */
/*   Updated: 2023/02/16 18:35:27 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	reflect(t_vector v, t_vector n)
{
	return (v - n * 2 * dot(v, n));
}

t_color	compute_diffuse(t_object *obj, t_comps *comps, t_light *light,
	t_color color)
{
	t_color		diffuse;
	t_vector	lightv;
	float		light_dot_normal;

	lightv = normalize(light->position - comps->overpoint);
	light_dot_normal = dot(lightv, comps->normalv);
	if (light_dot_normal < 0)
		diffuse.c = 0x0;
	else
	{
		diffuse = color_ratio(color, light_dot_normal);
		diffuse = color_ratio(diffuse, obj->material->diffuse);
	}
	return (diffuse);
}

t_color	lighting(t_scene *scene, t_object *obj, t_comps *comps, t_bool shadow)
{
	t_color		c_amb;
	t_color		c_light;
	t_color		ambient;
	t_color		diffuse;

	diffuse.c = 0x0;
	if (scene->ambient)
	{
		c_amb = blend_colors(obj->material->color, scene->ambient->color);
		ambient = color_ratio(c_amb, scene->ambient->lighting);
	}
	else
		ambient.c = 0x0;
	if (shadow == TRUE || !scene->light)
		return (ambient);
	c_light = blend_colors(obj->material->color, scene->light->color);
	diffuse = compute_diffuse(obj, comps, scene->light, c_light);
	return (color_sum(ambient, diffuse));
}

int	shade_hit(t_scene *scene, t_object *obj, t_comps *comps, t_color *color)
{
	int	shadow;

	shadow = is_shadowed(scene, comps->overpoint);
	if (shadow == ERR)
		return (EXIT_FAILURE);
	*color = lighting(scene, obj, comps, shadow);
	return (EXIT_SUCCESS);
}
