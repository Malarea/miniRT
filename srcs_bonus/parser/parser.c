/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:19:33 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 05:38:56 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	compute_pixel_size(unsigned int deg, t_scene *scene)
{
	float	fov;
	float	half_view;
	float	aspect;

	if (deg == 180)
		deg = 179;
	fov = radians((float)deg);
	half_view = tan(fov / 2);
	aspect = (float)WIDTH / (float)HEIGHT;
	if (aspect >= 1)
	{
		scene->half_w = half_view;
		scene->half_h = half_view / aspect;
	}
	else
	{
		scene->half_w = half_view * aspect;
		scene->half_h = half_view;
	}
	scene->pixel_size = (scene->half_w * 2) / WIDTH;
}

static void	return_err(t_scene **scene, char *line)
{
	free_scene(*scene, NULL);
	*scene = NULL;
	ft_free((void **)&line);
	return ;
}

int	detect_item(t_scene **scene, char **split)
{
	int	ret;

	if (!split[0])
	{
		free(split);
		return (EXIT_SUCCESS);
	}
	if (!ft_strcmp(split[0], "A"))
		ret = create_ambient(&split[1], scene);
	else if (!ft_strcmp(split[0], "C"))
		ret = create_camera(&split[1], scene);
	else if (!ft_strcmp(split[0], "l"))
		ret = create_light(&split[1], scene);
	else if (!ft_strcmp(split[0], "sp"))
		ret = create_sphere(&split[1], scene);
	else if (!ft_strcmp(split[0], "pl"))
		ret = create_plane(&split[1], scene);
	else if (!ft_strcmp(split[0], "cy"))
		ret = create_cylinder(&split[1], scene);
	else if (!ft_strcmp(split[0], "co"))
		ret = create_cone(&split[1], scene);
	else
		ret = error_parsing(ERR_INV_EL, split[0]);
	free_arr_of_str(split);
	return (ret);
}

void	split_file(int fd, t_scene **scene)
{
	char	*line;
	char	**split;
	int		ret;
	int		end;

	line = NULL;
	end = 1;
	while (end > 0)
	{
		end = get_next_line(fd, &line);
		if (end == -1)
			return (return_err(scene, line));
		split = ft_split(line, " \t");
		if (!split)
			return (return_err(scene, line));
		ret = detect_item(scene, split);
		ft_free((void **)&line);
		if (ret == EXIT_FAILURE)
			return (return_err(scene, NULL));
	}
	return ;
}

t_scene	*parser(char *file)
{
	t_scene	*scene;
	int		fd;

	if (check_file_extension(file, "rt") == FALSE)
	{
		error_parsing(ERR_EXT, NULL);
		return (NULL);
	}
	fd = open(file, O_RDWR);
	if (fd == -1 || errno == EISDIR)
	{
		perror(file);
		return (NULL);
	}
	scene = ft_calloc(1, sizeof(*scene));
	if (!scene)
		return (NULL);
	split_file(fd, &scene);
	close(fd);
	if (scene && scene->camera)
		compute_pixel_size(scene->camera->fov, scene);
	return (scene);
}
