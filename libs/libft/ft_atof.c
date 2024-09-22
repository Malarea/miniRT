/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:18:42 by agranger          #+#    #+#             */
/*   Updated: 2023/01/27 15:15:35 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	ft_atof(char *str)
{
	int		i;
	int		len;
	int		sign;
	float	integer;
	float	decimal;

	sign = 0;
	if (str[sign] == '-')
		sign++;
	i = sign;
	while (str[i] && str[i] != '.')
		i++;
	if (!str[i])
		return ((float)ft_atoi(str));
	str[i] = '\0';
	integer = (float)ft_atoi(&str[sign]);
	len = ft_strlen(&str[i + 1]);
	decimal = (float)ft_atoi(&str[i + 1]);
	str[i] = '.';
	while (len--)
		decimal /= 10;
	if (sign)
		return (-(integer + decimal));
	return (integer + decimal);
}
