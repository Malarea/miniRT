/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:33:17 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 23:31:50 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_back_light(t_light **first, t_light *new)
{
	t_light	*tmp;

	if (!*first)
	{
		*first = new;
		return ;
	}
	tmp = *first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}

int	create_light(char **args, t_scene **scene)
{
	t_light		*l;
	t_color		c;
	t_point		p;

	if (check_args(0, L, 3, args) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	l = ft_calloc(1, sizeof(*l));
	if (!l)
		return (EXIT_FAILURE);
	l->next = NULL;
	l->prev = NULL;
	add_back_light(&(*scene)->light, l);
	if (check_coordinates(args[0], &p, L) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	l->position = p;
	if (check_float_range(args[1], 0.0, 1.0, L) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	l->brightness = ft_atof(args[1]);
	if (check_color_format(args[2], &c, L) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	l->color = c;
	return (EXIT_SUCCESS);
}
