/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_shear_transl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 16:29:21 by agranger          #+#    #+#             */
/*   Updated: 2023/01/04 16:15:39 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	*translation(float x, float y, float z)
{
	t_matrix	*m;

	m = identity_matrix();
	if (!m)
		return (NULL);
	m->val[0][3] = x;
	m->val[1][3] = y;
	m->val[2][3] = z;
	return (m);
}

t_matrix	*shearing_x(float xy, float xz)
{
	t_matrix	*m;

	m = identity_matrix();
	if (!m)
		return (NULL);
	m->val[0][1] = xy;
	m->val[0][2] = xz;
	return (m);
}

t_matrix	*shearing_y(float yx, float yz)
{
	t_matrix	*m;

	m = identity_matrix();
	if (!m)
		return (NULL);
	m->val[1][0] = yx;
	m->val[1][2] = yz;
	return (m);
}

t_matrix	*shearing_z(float zx, float zy)
{
	t_matrix	*m;

	m = identity_matrix();
	if (!m)
		return (NULL);
	m->val[2][0] = zx;
	m->val[2][1] = zy;
	return (m);
}
