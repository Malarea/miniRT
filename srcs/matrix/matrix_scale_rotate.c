/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scale_rotate.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:32:07 by agranger          #+#    #+#             */
/*   Updated: 2023/01/21 18:34:43 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*scaling(float x, float y, float z)
{
	t_matrix	*m;

	m = identity_matrix();
	if (!m)
		return (NULL);
	m->val[0][0] = x;
	m->val[1][1] = y;
	m->val[2][2] = z;
	return (m);
}

float	get_angle_vector(t_vector a, t_vector b)
{
	return (acos(dot(a, b) / (magnitude(a) * magnitude(b))));
}

t_matrix	*get_rot_matrix(t_vector v, float theta)
{
	t_matrix	*m;
	float		costh;
	float		sinth;
	float		t;

	costh = cos(theta);
	sinth = sin(theta);
	t = 1.0 - costh;
	m = identity_matrix();
	if (!m)
		return (NULL);
	m->val[0][0] = costh + v.x * v.x * t;
	m->val[0][1] = v.x * v.y * t - v.z * sinth;
	m->val[0][2] = v.x * v.z * t + v.y * sinth;
	m->val[1][0] = v.x * v.y * t + v.z * sinth;
	m->val[1][1] = costh + v.y * v.y * t;
	m->val[1][2] = v.y * v.z * t - v.x * sinth;
	m->val[2][0] = v.z * v.x * t - v.y * sinth;
	m->val[2][1] = v.z * v.y * t + v.x * sinth;
	m->val[2][2] = costh + v.z * v.z * t;
	return (m);
}

t_matrix	*rodrigues_rotation(t_vector a, t_vector b)
{
	float		theta;
	t_vector	axe_rot;
	t_matrix	*m;

	theta = get_angle_vector(a, b);
	axe_rot = normalize(cross(a, b));
	m = get_rot_matrix(axe_rot, theta);
	return (m);
}
