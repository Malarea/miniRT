/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:31:16 by agranger          #+#    #+#             */
/*   Updated: 2022/12/14 16:11:01 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	matrix_equality(t_matrix *a, t_matrix *b)
{
	int	row;
	int	col;

	if (a->size != b->size)
		ft_putstr_fd("matrix_equality: different sizes\n", 2);
	row = 0;
	while (row < a->size)
	{
		col = 0;
		while (col < a->size)
		{
			if (comparison_float(a->val[row][col],
				b->val[row][col]) == FALSE)
				return (FALSE);
			col++;
		}
		row++;
	}
	return (TRUE);
}

void	fill_product_matrix(t_matrix *a, t_matrix *b, t_matrix *m, int i[2])
{
	int	k;
	int	row;
	int	col;

	row = i[ROW];
	col = i[COL];
	k = 0;
	while (k < a->size)
	{
		m->val[row][col] += a->val[row][k]
			* b->val[k][col];
		k++;
	}
}

t_matrix	*matrix_mult(t_matrix *a, t_matrix *b)
{
	t_matrix	*m;
	int			i[2];

	if (a->size != b->size)
		ft_putstr_fd("matrix_mult: different sizes\n", 2);
	m = create_matrix(a->size);
	if (!m)
		return (NULL);
	i[ROW] = 0;
	while (i[ROW] < a->size)
	{
		i[COL] = 0;
		while (i[COL] < a->size)
		{
			fill_product_matrix(a, b, m, i);
			i[COL]++;
		}
		i[ROW]++;
	}
	m->size = a->size;
	return (m);
}

t_tuple	matrix_tuple_mult(t_matrix *a, t_tuple b)
{
	return ((t_vector){
		b.x * a->val[0][0] + b.y * a->val[0][1]
		+ b.z * a->val[0][2] + b.w * a->val[0][3],
		b.x * a->val[1][0] + b.y * a->val[1][1]
		+ b.z * a->val[1][2] + b.w * a->val[1][3],
		b.x * a->val[2][0] + b.y * a->val[2][1]
		+ b.z * a->val[2][2] + b.w * a->val[2][3],
		b.x * a->val[3][0] + b.y * a->val[3][1]
		+ b.z * a->val[3][2] + b.w * a->val[3][3],
	});
}

t_matrix	*transpose(t_matrix *m)
{
	t_matrix	*t;
	int			row;
	int			col;

	t = create_matrix(m->size);
	if (!t)
		return (NULL);
	row = 0;
	while (row < m->size)
	{
		col = 0;
		while (col < m->size)
		{
			t->val[row][col] = m->val[col][row];
			col++;
		}
		row++;
	}
	t->size = m->size;
	return (t);
}
