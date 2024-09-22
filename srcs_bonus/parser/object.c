/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:15:59 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 05:58:13 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_back_object(t_object **first, t_object *new)
{
	t_object	*tmp;

	if (!*first)
	{
		*first = new;
		return ;
	}
	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

void	free_material(t_material *m, t_vars *vars)
{
	mlx_destroy_image(vars->mlx, m->bumpmap->img);
	ft_free((void **)&m->filename_bm);
	ft_free((void **)&m->bumpmap);
}

int	parse_color(t_object *obj, char **args, char *elem)
{
	t_color	c1;
	t_color	c2;

	if (check_color_format(args[0], &c1, elem) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	obj->material->color = c1;
	if (!args[1])
	{
		obj->material->checkerboard = FALSE;
		return (EXIT_SUCCESS);
	}
	if (obj->type == SPHERE && check_file_extension(args[1], "xpm") == TRUE)
		obj->material->filename_bm = ft_strdup(args[1]);
	else if (check_color_format(args[1], &c2, elem) == EXIT_SUCCESS)
	{
		obj->material->checkerboard = TRUE;
		obj->material->color2 = c2;
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_material	*create_material(t_finish f)
{
	t_material	*m;

	m = ft_calloc(1, sizeof(*m));
	if (!m)
		return (NULL);
	if (f == GLOSSY)
	{
		m->diffuse = 0.7;
		m->specular = 0.9;
		m->shininess = 200;
	}
	if (f == MATTE)
	{
		m->diffuse = 0.7;
		m->specular = 0;
		m->shininess = 0;
	}
	m->filename_bm = NULL;
	m->checkerboard = FALSE;
	return (m);
}
