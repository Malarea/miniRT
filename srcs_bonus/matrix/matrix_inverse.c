/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:08:23 by agranger          #+#    #+#             */
/*   Updated: 2023/01/26 15:17:27 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	determinant(t_matrix *m, float *det)
{
	int		i;
	float	cofact;

	if (m->size == 2)
	{
		*det = m->val[0][0] * m->val[1][1] - m->val[0][1] * m->val[1][0];
		return (0);
	}
	i = 0;
	*det = 0;
	while (i < m->size)
	{
		if (cofactor(m, 0, i, &cofact))
			return (1);
		*det += m->val[0][i] * cofact;
		i++;
	}
	return (0);
}

int	minor(t_matrix *m, int rdel, int cdel, float *minor)
{
	t_matrix	*subm;
	int			ret;

	subm = submatrix(m, rdel, cdel);
	if (!subm)
		return (1);
	ret = 0;
	if (determinant(subm, minor))
		ret = 1;
	free_matrix(&subm);
	return (ret);
}

int	cofactor(t_matrix *m, int rdel, int cdel, float *cofact)
{
	if (minor(m, rdel, cdel, cofact))
		return (1);
	if ((rdel + cdel) % 2 != 0)
		*cofact = -(*cofact);
	return (0);
}

int	fill_inverse_matrix(t_matrix *m, t_matrix **inv)
{
	float		cofact;
	float		det;
	int			row;
	int			col;

	row = 0;
	while (row < m->size)
	{
		col = 0;
		while (col < m->size)
		{
			if (cofactor(m, row, col, &cofact) || determinant(m, &det))
				return (EXIT_FAILURE);
			(*inv)->val[col][row] = cofact / det;
			col++;
		}
		row++;
	}
	return (EXIT_SUCCESS);
}

t_matrix	*inverse(t_matrix *m)
{
	t_matrix	*inverse;

	if (!m)
		return (NULL);
	inverse = create_matrix(m->size);
	if (!inverse)
	{
		free_matrix(&m);
		return (NULL);
	}
	fill_inverse_matrix(m, &inverse);
	inverse->size = m->size;
	free_matrix(&m);
	return (inverse);
}
