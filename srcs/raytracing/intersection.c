/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:38:36 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:24:37 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_intersection(t_intersection *x)
{
	t_intersection	*tmp;

	while (x)
	{
		tmp = x->next;
		free(x);
		x = tmp;
	}
}

t_intersection	*get_hit(t_intersection *x)
{
	t_intersection	*ret;

	ret = NULL;
	while (x)
	{
		if (x->t > 0 && (!ret || x->t < ret->t))
			ret = x;
		x = x->next;
	}
	return (ret);
}

void	intersection_add_sort(t_intersection **first, t_intersection *new)
{
	t_intersection	*tmp;
	t_intersection	*next;

	tmp = *first;
	if (!*first)
		*first = new;
	else if (!(*first)->next && new->t < (*first)->t)
	{
		*first = new;
		new->next = tmp;
		tmp->prev = new;
	}
	else
	{
		while (tmp->next && tmp->next->t < new->t)
			tmp = tmp->next;
		next = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = next;
		if (next)
			next->prev = new;
	}
}

t_intersection	*create_intersection(float t, t_object *obj)
{
	t_intersection	*x;

	x = ft_calloc(1, sizeof(*x));
	if (!x)
		return (NULL);
	x->t = t;
	x->obj = obj;
	x->next = NULL;
	x->prev = NULL;
	return (x);
}

int	intersect_scene(t_object *obj, t_ray *r1, t_intersection **x)
{
	t_ray		*r2;

	while (obj)
	{
		r2 = transform(r1, obj->transform);
		if (!r2)
			return (EXIT_FAILURE);
		if (obj->intersect(obj, r2, x) == EXIT_FAILURE)
		{
			free_intersection(*x);
			ft_free((void **)&r2);
			return (EXIT_FAILURE);
		}
		obj = obj->next;
		ft_free((void **)&r2);
	}
	return (EXIT_SUCCESS);
}
