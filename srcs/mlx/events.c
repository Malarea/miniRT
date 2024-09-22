/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 18:11:30 by agranger          #+#    #+#             */
/*   Updated: 2022/12/04 18:11:57 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_win(t_vars *vars)
{
	clear_mlx(vars);
	exit(0);
}

int	keypress_events(int key, t_vars *vars)
{
	if (key == 65307)
		close_win(vars);
	return (0);
}
