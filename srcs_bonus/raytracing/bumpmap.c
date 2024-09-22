/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 16:38:06 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 06:06:51 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	get_perturbation(t_data *image, int x, int y)
{
	char		*dst;
	t_color		color;

	dst = image->addr + y * image->size_line + x * 4;
	color.c = *(unsigned int *)dst;
	return ((t_vector){color.r / 255.0 * 2.0 - 1, color.g / 255.0 * 2.0 - 1,
		color.b / 255.0 * 2.0 - 1, VECTOR});
}

int	load_normal_map(t_vars *vars, t_object *obj)
{
	t_data	*tex;
	char	*filename;

	while (obj)
	{
		filename = obj->material->filename_bm;
		if (filename)
		{
			tex = ft_calloc(1, sizeof(*tex));
			if (!tex)
				return (EXIT_FAILURE);
			obj->material->bumpmap = tex;
			tex->img = mlx_xpm_file_to_image(vars->mlx,
					filename, &tex->width, &tex->height);
			if (!tex->img)
			{
				perror(filename);
				return (EXIT_FAILURE);
			}
			tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
					&tex->size_line, &tex->endian);
		}
		obj = obj->next;
	}
	return (EXIT_SUCCESS);
}

void	spherical_bm_map(t_point p, float *u, float *v)
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
	return ;
}

int	apply_perturbation_normal(t_comps *comps, t_object *obj)
{
	t_point		objp;	
	float		u;
	float		v;

	objp = matrix_tuple_mult(obj->transform, comps->overpoint);
	spherical_bm_map(objp, &u, &v);
	u = round(((u + 1.0) / 2.0) * obj->material->bumpmap->width);
	v = round(obj->material->bumpmap->height
			- (((v + 1.0) / 2.0) * obj->material->bumpmap->height));
	comps->normalv = perturb_normal(comps->normalv, (t_vector){u, v, 0, VECTOR},
			obj->material->bumpmap);
	return (EXIT_SUCCESS);
}

t_vector	perturb_normal(t_vector n, t_vector texcoord, t_data *tex)
{
	t_vector	perturbation;
	t_vector	t;
	t_vector	bt;

	perturbation = get_perturbation(tex, texcoord.x, texcoord.y);
	t = normalize(cross((t_vector){0, 1, 0, VECTOR}, n));
	bt = normalize(cross(n, t));
	return (normalize(n + perturbation.x
			* t + perturbation.y * bt + n * perturbation.z));
}
