/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranger <agranger@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:38:25 by agranger          #+#    #+#             */
/*   Updated: 2023/02/19 05:41:30 by agranger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_mlx(t_vars *vars)
{
	if (vars->scene)
		free_scene(vars->scene, vars);
	if (vars->mlx)
	{
		if (vars->image.img)
			mlx_destroy_image(vars->mlx, vars->image.img);
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		mlx_loop_end(vars->mlx);
		ft_free((void **)&vars->mlx);
	}
}

void	*init_win(void *mlx)
{
	if (!mlx)
		return (NULL);
	return (mlx_new_window(mlx, WIDTH, HEIGHT, "miniRT"));
}

t_data	init_image(void *mlx)
{
	t_data	image;

	if (!mlx)
	{
		image.img = NULL;
		return (image);
	}
	image.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image.img)
		return (image);
	image.addr = mlx_get_data_addr(image.img, &image.bpp,
			&image.size_line, &image.endian);
	return (image);
}

void	mlx_pixel_put_img(t_data *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1)
	{
		ft_putstr_fd("pixel_put_img: wrong coordinates\n", 2);
		return ;
	}
	dst = image->addr + (y * image->size_line + x * 4);
	*(unsigned int *)dst = color;
}

unsigned int	get_pixel_color(t_data *image, int x, int y)
{
	char			*dst;

	if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1)
	{
		ft_putstr_fd("get_pixel_color: wrong coordinates\n", 2);
		return (0x0);
	}
	dst = image->addr + (y * image->size_line + x * 4);
	return (*(unsigned int *)dst);
}
