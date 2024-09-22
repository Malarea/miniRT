/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 18:00:39 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 01:45:34 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	compute_diffuse(t_object *obj, t_comps *comps, t_light *light,
	t_color col_obj)
{
	t_color		diffuse;
	t_color		col_light;
	t_color		tmp;
	t_vector	lightv;
	float		light_dot_normal;

	diffuse.c = 0x0;
	while (light)
	{
		col_light = blend_colors(col_obj, light->color);
		lightv = normalize(light->position - comps->overpoint);
		light_dot_normal = dot(lightv, comps->normalv);
		tmp = color_ratio(col_light, fmax(0, light_dot_normal));
		tmp = color_ratio(tmp, obj->material->diffuse);
		diffuse = color_sum(diffuse, tmp);
		light = light->next;
	}
	return (diffuse);
}

t_color	compute_specular(t_light *light, t_object *obj, t_comps *comps)
{
	t_color		specular;
	t_vector	lightv;
	t_vector	reflectv;
	float		factor;
	t_color		tmp;

	specular.c = 0x0;
	while (light)
	{
		lightv = normalize(light->position - comps->overpoint);
		reflectv = -lightv - comps->normalv * 2 * dot(-lightv, comps->normalv);
		factor = pow(fmax(0, dot(reflectv, comps->eyev)),
				obj->material->shininess);
		tmp = color_ratio(light->color, factor);
		tmp = color_ratio(tmp, obj->material->specular);
		specular = color_sum(specular, tmp);
		light = light->next;
	}
	return (specular);
}

t_color	compute_ambient(t_scene *scene, t_color color)
{
	t_color	c_amb;
	t_color	ambient;

	if (scene->ambient)
	{
		c_amb = blend_colors(color, scene->ambient->color);
		ambient = color_ratio(c_amb, scene->ambient->lighting);
	}
	else
		ambient.c = 0x0;
	return (ambient);
}

t_color	lighting(t_scene *scene, t_object *obj, t_comps *comps, t_bool shadow)
{
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_color		color;

	if (obj->material->checkerboard == TRUE)
		color = uv_checkers(obj, comps->overpoint);
	else
		color = obj->material->color;
	ambient = compute_ambient(scene, color);
	if (shadow == TRUE || !scene->light)
		return (ambient);
	diffuse = compute_diffuse(obj, comps, scene->light, color);
	if (diffuse.c != 0x0 && !obj->material->filename_bm)
		specular = compute_specular(scene->light, obj, comps);
	else
		specular.c = 0x0;
	return (color_sum(color_sum(ambient, diffuse), specular));
}

int	shade_hit(t_scene *scene, t_object *obj, t_comps *comps, t_color *color)
{
	int	shadow;

	shadow = is_shadowed(scene, comps->overpoint);
	if (shadow == ERR)
		return (EXIT_FAILURE);
	if (obj->material->filename_bm)
		apply_perturbation_normal(comps, obj);
	*color = lighting(scene, obj, comps, shadow);
	return (EXIT_SUCCESS);
}
