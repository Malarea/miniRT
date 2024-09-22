/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 19:29:42 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 00:14:01 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>

char	**ft_split(char *str, char *sep);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_substr_gnl(char *s1, unsigned int start, size_t len);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *str);
size_t	ft_strlen_gnl(const char *str);
size_t	ft_arrlen(char **str);
int		ft_atoi(const char *str);
int		get_next_line(int fd, char **line);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_isdigit(int c);
float	ft_atof(char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_free(void **item);
void	free_arr_of_str(char **arr);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *s, int c, size_t len);

#endif
