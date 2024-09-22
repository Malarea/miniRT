/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 12:15:01 by agranger          #+#    #+#             */
/*   Updated: 2023/01/26 11:53:58 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	comparison_float(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (TRUE);
	return (FALSE);
}

float	radians(float deg)
{
	return (deg / 180 * M_PI);
}

t_matrix	*identity_matrix(void)
{
	t_matrix	*m;
	int			row;
	int			col;

	m = create_matrix(4);
	if (!m)
		return (NULL);
	row = 0;
	while (row < 4)
	{
		col = 0;
		while (col < 4)
		{
			m->val[row][col] = (col == row);
			col++;
		}
		row++;
	}
	m->size = 4;
	return (m);
}

void	swap(float *a, float *b)
{
	float	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

t_matrix	*orientation_matrix(t_vector left, t_vector up, t_vector forward)
{
	t_matrix	*m;

	m = identity_matrix();
	if (!m)
		return (NULL);
	m->val[0][0] = left.x;
	m->val[0][1] = left.y;
	m->val[0][2] = left.z;
	m->val[1][0] = up.x;
	m->val[1][1] = up.y;
	m->val[1][2] = up.z;
	m->val[2][0] = -forward.x;
	m->val[2][1] = -forward.y;
	m->val[2][2] = -forward.z;
	return (m);
}
