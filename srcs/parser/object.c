/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:15:59 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:23:23 by agranger         ###   ########.fr       */
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
	return (m);
}
