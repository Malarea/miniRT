/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:24:51 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 05:56:21 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_scene *scene, t_vars *vars)
{
	t_object	*tmp;
	t_light		*l;

	while (scene->obj)
	{
		tmp = scene->obj->next;
		free_matrix(&scene->obj->transform);
		if (scene->obj->material->filename_bm && vars)
			free_material(scene->obj->material, vars);
		ft_free((void **)&scene->obj->material);
		ft_free((void **)&scene->obj);
		scene->obj = tmp;
	}
	ft_free((void **)&scene->ambient);
	while (scene->light)
	{
		l = scene->light->next;
		ft_free((void **)&scene->light);
		scene->light = l;
	}
	if (scene->camera)
		free_matrix(&scene->camera->transform);
	ft_free((void **)&scene->camera);
	ft_free((void **)&scene);
}

t_bool	not_enough_elem(t_vars *vars)
{
	if (!vars->scene->camera
		|| !vars->scene->obj)
		return (TRUE);
	return (FALSE);
}

int	exec(t_vars *vars)
{
	mlx_hook(vars->win, 17, 1L << 17, close_win, vars);
	mlx_hook(vars->win, 2, 1L << 0, keypress_events, vars);
	if (not_enough_elem(vars) == TRUE || load_normal_map(vars,
			vars->scene->obj) == EXIT_FAILURE || render(vars) == EXIT_FAILURE)
	{
		clear_mlx(vars);
		return (EXIT_FAILURE);
	}
	mlx_loop(vars->mlx);
	clear_mlx(vars);
	return (EXIT_SUCCESS);
}

int	check_init(t_vars *vars)
{
	if (!vars->scene
		|| !vars->mlx
		|| !vars->image.img)
		return (EXIT_FAILURE);
	vars->win = init_win(vars->mlx);
	if (!vars->win)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	main(int argc, char	**argv)
{
	t_vars		vars;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./minirt scene.rt\n", 2);
		return (EXIT_SUCCESS);
	}
	vars = (t_vars){
		vars.mlx = mlx_init(),
		vars.win = NULL,
		vars.image = init_image(vars.mlx),
		vars.scene = parser(argv[1])
	};
	if (check_init(&vars) == EXIT_FAILURE)
	{
		clear_mlx(&vars);
		return (EXIT_FAILURE);
	}
	return (exec(&vars));
}
