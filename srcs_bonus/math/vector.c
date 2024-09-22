/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:30:20 by agranger          #+#    #+#             */
/*   Updated: 2022/12/14 16:19:45 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	magnitude(t_vector vector)
{
	return (sqrt(vector.x * vector.x
			+ vector.y * vector.y
			+ vector.z * vector.z
			+ vector.w * vector.w));
}

t_vector	normalize(t_vector vector)
{
	return ((t_vector){
		vector.x / magnitude(vector),
		vector.y / magnitude(vector),
		vector.z / magnitude(vector),
		vector.w / magnitude(vector)
	});
}

float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x
		+ a.y * b.y
		+ a.z * b.z
		+ a.w * b.w);
}

t_vector	cross(t_vector a, t_vector b)
{
	return ((t_vector){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		0.0
	});
}

t_bool	tuple_equality(t_tuple a, t_tuple b)
{
	if (comparison_float(a.x, b.x) == TRUE
		&& comparison_float(a.y, b.y) == TRUE
		&& comparison_float(a.z, b.z) == TRUE
		&& comparison_float(a.w, a.w) == TRUE)
		return (TRUE);
	return (FALSE);
}
