/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:07:50 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:31:49 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_matrix(t_matrix **m)
{
	int	i;

	i = 0;
	if (*m && (*m)->val)
	{
		while (i < (*m)->size)
			free((*m)->val[i++]);
		free((*m)->val);
	}
	if (*m)
	{
		free(*m);
		*m = NULL;
	}
}

float	**create_matrix_val(int size, t_matrix **matrix)
{
	float	**val;
	int		i;

	val = ft_calloc(size, sizeof(float *));
	if (!val)
	{
		free_matrix(matrix);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		val[i] = ft_calloc(size, sizeof(float));
		if (!val[i])
		{
			(*matrix)->val = val;
			(*matrix)->size = i;
			free_matrix(matrix);
			return (NULL);
		}
		i++;
	}
	return (val);
}

t_matrix	*create_matrix(int size)
{
	float		**val;
	t_matrix	*matrix;

	matrix = ft_calloc(1, sizeof(*matrix));
	if (!matrix)
		return (NULL);
	val = create_matrix_val(size, &matrix);
	if (!val)
	{
		ft_free((void **)&matrix);
		return (NULL);
	}
	matrix->val = val;
	matrix->size = size;
	return (matrix);
}

void	incr_row_col(int *m, int *s, int del)
{
	if (*m != del)
		(*s)++;
	(*m)++;
}

t_matrix	*submatrix(t_matrix *m, int rdel, int cdel)
{
	t_matrix	*subm;
	int			m_row;
	int			m_col;
	int			s_row;
	int			s_col;

	subm = create_matrix(m->size - 1);
	if (!subm)
		return (NULL);
	m_row = 0;
	s_row = 0;
	while (m_row < m->size)
	{
		m_col = 0;
		s_col = 0;
		while (m_col < m->size)
		{
			if (m_col != cdel && m_row != rdel)
				subm->val[s_row][s_col] = m->val[m_row][m_col];
			incr_row_col(&m_col, &s_col, cdel);
		}
		incr_row_col(&m_row, &s_row, rdel);
	}
	subm->size = m->size - 1;
	return (subm);
}
