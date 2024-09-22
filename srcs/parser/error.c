/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:19:13 by agranger          #+#    #+#             */
/*   Updated: 2023/01/16 15:59:11 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_args(int dup, char *elem, int expected, char **args)
{
	int	nb_args;

	if (dup)
		return (error_parsing(ERR_DUP_EL, elem));
	nb_args = ft_arrlen(args);
	if (nb_args < expected)
		return (error_parsing(ERR_MISS_INF, elem));
	if (nb_args > expected)
		return (error_parsing(ERR_TOO_MANY_INF, elem));
	return (EXIT_SUCCESS);
}

int	error_parsing(char *err, char *arg)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(err, 2);
	return (EXIT_FAILURE);
}
