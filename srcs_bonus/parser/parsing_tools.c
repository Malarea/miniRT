/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 18:20:58 by agranger          #+#    #+#             */
/*   Updated: 2023/02/18 18:34:21 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_bool	str_is_float(char *num)
{
	if (*num == '-')
		num++;
	while (*num)
	{
		if (!ft_isdigit(*num) && *num != '.')
			return (FALSE);
		num++;
	}
	return (TRUE);
}

t_bool	str_is_int(char *num)
{
	if (*num == '-')
		num++;
	while (*num)
	{
		if (!ft_isdigit(*num))
			return (FALSE);
		num++;
	}
	return (TRUE);
}

t_bool	check_file_extension(char *file, char *ext)
{
	int	i;

	i = 0;
	while (file[i] && file[i] != '.')
		i++;
	if (!file[i])
		return (FALSE);
	if (!ft_strcmp(&file[i + 1], ext))
		return (TRUE);
	return (FALSE);
}
