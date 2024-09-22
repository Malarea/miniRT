/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 16:08:06 by agranger          #+#    #+#             */
/*   Updated: 2023/01/10 17:57:25 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	blend_colors(t_color a, t_color b)
{
	t_color	blend;

	blend.r = a.r * b.r / 255;
	blend.g = a.g * b.g / 255;
	blend.b = a.b * b.b / 255;
	return (blend);
}

t_color	color_ratio(t_color a, float ratio)
{
	t_color	b;

	b.r = a.r * ratio;
	b.b = a.b * ratio;
	b.g = a.g * ratio;
	return (b);
}

int	clamp_color(int n)
{
	if (n > 255)
		return (255);
	return (n);
}

t_color	color_sum(t_color a, t_color b)
{
	t_color	c;
	int		n;

	n = a.r + b.r;
	c.r = clamp_color(n);
	n = a.g + b.g;
	c.g = clamp_color(n);
	n = a.b + b.b;
	c.b = clamp_color(n);
	return (c);
}

void	set_color(t_color *c, int r, int g, int b)
{
	c->r = r;
	c->g = g;
	c->b = b;
}
