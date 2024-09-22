/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:05:01 by agranger          #+#    #+#             */
/*   Updated: 2023/01/26 15:13:04 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	if (!s2)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!res)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = -1;
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	ft_free((void **)&s1);
	return (res);
}

char	*ft_substr_gnl(char *s1, unsigned int start, size_t len)
{
	char			*s2;
	unsigned int	i;

	if (!s1)
		return (0);
	s2 = malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (0);
	i = 0;
	if (start < ft_strlen_gnl(s1))
	{
		while (s1[start + i] && i < len)
		{
			s2[i] = s1[start + i];
			i++;
		}
	}
	s2[i] = '\0';
	return (s2);
}
