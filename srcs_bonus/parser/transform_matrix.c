/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_matrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 12:03:04 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 04:57:40 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*compute_transform_sphere(float diam, t_point pos)
{
	t_matrix	*scale;
	t_matrix	*transl;
	t_matrix	*transform;

	scale = scaling(diam / 2, diam / 2, diam / 2);
	transl = translation(pos.x, pos.y, pos.z);
	if (!scale || !transl)
	{
		free_matrix(&scale);
		free_matrix(&transl);
		return (NULL);
	}
	transform = matrix_mult(transl, scale);
	free_matrix(&scale);
	free_matrix(&transl);
	return (inverse(transform));
}

t_matrix	*compute_transform_plane(t_vector v, t_point pos)
{
	t_matrix	*rotate;
	t_matrix	*transl;
	t_matrix	*transform;

	transl = translation(pos.x, pos.y, pos.z);
	if (tuple_equality(v, (t_vector){0, 1, 0, VECTOR}) == TRUE
		|| tuple_equality(v, (t_vector){0, -1, 0, VECTOR}) == TRUE)
		rotate = identity_matrix();
	else
		rotate = rodrigues_rotation((t_vector){0, 1, 0, VECTOR}, v);
	if (!transl || !rotate)
	{
		free_matrix(&rotate);
		free_matrix(&transl);
		return (NULL);
	}
	transform = matrix_mult(transl, rotate);
	free_matrix(&rotate);
	free_matrix(&transl);
	return (inverse(transform));
}

void	*free_all_matrix(t_matrix *m1, t_matrix *m2, t_matrix *m3, t_matrix *m4)
{
	free_matrix(&m1);
	free_matrix(&m2);
	free_matrix(&m3);
	free_matrix(&m4);
	return (NULL);
}

t_matrix	*compute_transform_cylinder(t_vector v, t_point pos, float diam)
{
	t_matrix	*rotate;
	t_matrix	*scale;
	t_matrix	*transl;
	t_matrix	*transform;
	t_matrix	*tmp;

	scale = scaling(diam / 2, 1, diam / 2);
	transl = translation(pos.x, pos.y, pos.z);
	if (tuple_equality(v, (t_vector){0, 1, 0, VECTOR}) == TRUE
		|| tuple_equality(v, (t_vector){0, -1, 0, VECTOR}) == TRUE)
		rotate = identity_matrix();
	else
		rotate = rodrigues_rotation((t_vector){0, 1, 0, VECTOR}, v);
	if (!transl || !rotate || !scale)
	{
		free_all_matrix(rotate, scale, transl, NULL);
		return (NULL);
	}
	tmp = matrix_mult(transl, rotate);
	if (!tmp)
		return (free_all_matrix(rotate, scale, transl, tmp));
	transform = matrix_mult(tmp, scale);
	free_all_matrix(rotate, scale, transl, tmp);
	return (inverse(transform));
}

t_matrix	*view_transform(t_point from, t_vector forward)
{
	t_vector	left;
	t_matrix	*orientation;
	t_matrix	*transl;
	t_matrix	*transform;

	left = cross(forward, (t_vector){0, 1, 0, VECTOR});
	orientation = orientation_matrix(left, cross(left, forward), forward);
	if (!orientation)
		return (NULL);
	transl = translation(-from.x, -from.y, -from.z);
	if (!transl)
	{
		free_matrix(&orientation);
		return (NULL);
	}
	transform = matrix_mult(orientation, transl);
	free_matrix(&transl);
	free_matrix(&orientation);
	return (inverse(transform));
}
