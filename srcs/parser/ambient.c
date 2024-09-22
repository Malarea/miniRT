/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:13:04 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:20:34 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_ambient(char **args, t_scene **scene)
{
	static int	dup;
	t_ambient	*a;
	t_color		c;

	if (check_args(dup, A, 2, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	a = ft_calloc(1, sizeof(*a));
	if (!a)
		return (EXIT_FAILURE);
	(*scene)->ambient = a;
	if (check_float_range(args[0], 0.0, 1.0, A) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	a->lighting = ft_atof(args[0]);
	if (check_color_format(args[1], &c, A) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	a->color = c;
	dup = 1;
	return (EXIT_SUCCESS);
}
