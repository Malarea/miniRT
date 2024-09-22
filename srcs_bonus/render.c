/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:49:15 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 05:27:48 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_comps	*prepare_computation(t_intersection *i, t_ray *r)
{
	t_comps	*comps;

	comps = malloc(sizeof(*comps));
	if (!comps)
		return (NULL);
	comps->t = i->t;
	comps->obj = i->obj;
	comps->point = position(r, comps->t);
	comps->eyev = -r->direction;
	comps->normalv = normal_at(comps->obj, comps->point);
	if (comps->normalv.w == ERROR)
	{
		ft_free((void **)&comps);
		return (NULL);
	}
	if (dot(comps->normalv, comps->eyev) < 0)
	{
		comps->inside = TRUE;
		comps->normalv = -comps->normalv;
	}
	else
		comps->inside = FALSE;
	comps->overpoint = comps->point + comps->normalv * 0.002;
	return (comps);
}

int	color_at(t_scene *scene, t_ray *r, t_color *color)
{
	t_intersection	*xs;
	t_intersection	*hit;
	t_comps			*comps;
	int				ret;

	xs = NULL;
	if (intersect_scene(scene->obj, r, &xs) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	hit = get_hit(xs);
	if (!hit)
	{
		color->c = 0x0;
		free_intersection(xs);
		return (EXIT_SUCCESS);
	}
	comps = prepare_computation(hit, r);
	if (!comps)
	{
		free_intersection(xs);
		return (EXIT_FAILURE);
	}
	ret = shade_hit(scene, hit->obj, comps, color);
	free_intersection(xs);
	ft_free((void **)&comps);
	return (ret);
}

int	render(t_vars *vars)
{
	int		x;
	int		y;
	t_ray	*r;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			r = ray_for_pixel(vars->scene, x, y);
			if (!r || color_at(vars->scene, r, &color) == EXIT_FAILURE)
			{
				ft_free((void **)&r);
				return (EXIT_FAILURE);
			}
			ft_free((void **)&r);
			mlx_pixel_put_img(&vars->image, x, y, color.c);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	return (EXIT_SUCCESS);
}
