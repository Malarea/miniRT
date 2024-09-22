/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:33:17 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:24:13 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_light(char **args, t_scene **scene)
{
	static int	dup;
	t_light		*l;
	t_color		c;
	t_point		p;

	if (check_args(dup, L, 3, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	l = ft_calloc(1, sizeof(*l));
	if (!l)
		return (EXIT_FAILURE);
	(*scene)->light = l;
	if (check_coordinates(args[0], &p, L) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	l->position = p;
	if (check_float_range(args[1], 0.0, 1.0, L) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	l->brightness = ft_atof(args[1]);
	if (check_color_format(args[2], &c, L) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	l->color = c;
	dup = 1;
	return (EXIT_SUCCESS);
}
