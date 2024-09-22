/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 16:26:28 by agranger          #+#    #+#             */
/*   Updated: 2023/01/26 15:10:13 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	word_count(char	*str, char *sep)
{
	int	i;
	int	nb_word;

	i = 0;
	nb_word = 0;
	while (str[i])
	{
		if (str[i] && !is_charset(str[i], sep))
		{
			nb_word++;
			while (str[i] && !is_charset(str[i], sep))
				i++;
		}
		else
			i++;
	}
	return (nb_word);
}

int	word_len(char **str, char *sep)
{
	int	len;

	while (**str && is_charset(**str, sep))
		(*str)++;
	len = 0;
	while ((*str)[len] && !is_charset((*str)[len], sep))
		len++;
	return (len);
}

int	fill_split(int nb_word, char **ret, char *str, char *sep)
{
	int		i;
	int		j;

	i = 0;
	while (i < nb_word)
	{
		j = 0;
		ret[i] = malloc(sizeof(char) * (word_len(&str, sep) + 1));
		if (!ret[i])
		{
			free_arr_of_str(ret);
			return (EXIT_FAILURE);
		}
		while (*str && !is_charset(*str, sep))
		{
			ret[i][j] = *str;
			j++;
			str++;
		}
		ret[i][j] = '\0';
		str++;
		i++;
	}
	ret[i] = NULL;
	return (EXIT_SUCCESS);
}

char	**ft_split(char *str, char *sep)
{
	char	**ret;
	int		nb_word;

	nb_word = word_count(str, sep);
	ret = calloc((nb_word + 1), sizeof(char *));
	if (!ret)
		return (NULL);
	if (fill_split(nb_word, ret, str, sep) == EXIT_FAILURE)
		return (NULL);
	return (ret);
}
