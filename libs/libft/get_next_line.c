/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 12:57:19 by agranger          #+#    #+#             */
/*   Updated: 2023/01/26 14:36:18 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contain_nl(char *s, int *size)
{
	int	len;

	if (!s)
	{
		*size = -1;
		return (0);
	}
	len = ft_strlen_gnl(s);
	*size = 0;
	while (*size < len)
	{
		if (s[*size] == '\n')
			return (1);
		(*size)++;
	}
	*size = -1;
	return (0);
}

int	read_file(int *size, int fd, char *buff, char **stock)
{
	int		ret;

	if (!contain_nl(*stock, size))
		ret = read(fd, buff, BUFF_SIZE);
	while (*size == -1 && ret > 0)
	{
		buff[ret] = '\0';
		*stock = ft_strjoin_gnl(*stock, buff);
		if (!*stock)
			return (-1);
		if (!contain_nl(*stock, size))
			ret = read(fd, buff, BUFF_SIZE);
	}
	if (*stock == NULL)
	{
		*stock = ft_substr_gnl(buff, 0, ft_strlen_gnl(buff));
		if (!*stock)
			return (-1);
	}
	if (*size == -1)
		*size = ft_strlen_gnl(*stock);
	return (ret);
}

int	update_stock(char **stock, int size, int ret)
{
	char	*tmp;

	if (ret <= 0)
		return (1);
	tmp = ft_substr_gnl(*stock, 0, ft_strlen_gnl(*stock));
	if (!tmp)
		return (0);
	ft_free((void **)stock);
	*stock = ft_substr_gnl(tmp, size + 1, ft_strlen_gnl(tmp) - size);
	ft_free((void **)&tmp);
	if (!*stock)
		return (0);
	return (1);
}

int	return_err(char **stock)
{
	ft_free((void **)stock);
	return (-1);
}

int	get_next_line(int fd, char **line)
{
	static char	*stock;
	char		*buff;
	int			ret;
	int			size;

	if (!line || fd < 0 || fd > 256 || BUFF_SIZE <= 0 || BUFF_SIZE > 100000000)
		return (-1);
	buff = ft_calloc(BUFF_SIZE + 1, sizeof(*buff));
	if (!buff)
		return (-1);
	size = 0;
	ret = read_file(&size, fd, buff, &stock);
	ft_free((void **)&buff);
	if (ret == -1)
		return (return_err(&stock));
	*line = ft_substr_gnl(stock, 0, size);
	if (!*line)
		return (return_err(&stock));
	if (!(update_stock(&stock, size, ret)))
		return (return_err(&stock));
	else
		ft_free((void **)&stock);
	return (ret);
}
