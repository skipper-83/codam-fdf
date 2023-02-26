/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrome.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 22:59:21 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/26 14:18:14 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	update_rotation_disp(t_meta *m)
{
	char		rotation_disp[200];
	static int	old_img;
	int			new_img;

	new_img = 0;
	if (old_img == 0)
		new_img = 1;
	if (ft_sprintf(rotation_disp, "cam rotation: % 7.2fx % 7.2fy % 7.2fz \
	| world rotation % 7.2fx % 7.2fy % 7.2fz", m->cam_rotation.x, \
	m->cam_rotation.y, m->cam_rotation.z, m->world_rotation.x, \
	m->world_rotation.y, m->world_rotation.z) < 0)
		exit_error(ERROR_MEM, m);
	m->rotations[new_img] = mlx_put_string(m->mlx, rotation_disp, 30, \
														m->window_h - 30);
	if (m->rotations[new_img] == NULL)
		exit_error(ERROR_MLX, m);
	mlx_set_instance_depth(&m->rotations[new_img]->instances[0], 10);
	mlx_delete_image(m->mlx, m->rotations[old_img]);
	old_img = new_img;
}

static void	header_background(t_meta *m, int x_pos, int y_pos)
{
	t_list		*item;
	mlx_image_t	*img;

	img = mlx_put_string(m->mlx, "CONTROLS", x_pos, y_pos);
	if (img == NULL)
		exit_error(ERROR_MLX, m);
	m->strings = ft_lstnew(img);
	if (m->strings == NULL)
		exit_error(ERROR_MEM, m);
	img = mlx_new_image(m->mlx, 330, 310);
	if (img == NULL)
		exit_error(ERROR_MLX, m);
	item = ft_lstnew(img);
	if (item == NULL)
		exit_error(ERROR_MEM, m);
	ft_lstadd_front(&m->strings, item);
	ft_memset(img->pixels, 0xFFFFFF44, 330 * 310 * sizeof(int));
	mlx_image_to_window(m->mlx, img, x_pos - 10, y_pos - 8);
	mlx_set_instance_depth(&img->instances[0], 0);
}

static void	make_lines(t_meta *m, const char *chrome[13])
{
	int			i;
	t_list		*item;
	int			x_pos;
	int			y_pos;
	mlx_image_t	*img;

	i = 0;
	x_pos = m->window_w - 350;
	y_pos = 50;
	header_background(m, x_pos, y_pos);
	while (i < 13)
	{
		img = mlx_put_string(m->mlx, chrome[i], x_pos, y_pos + 30);
		if (img == NULL)
			exit_error(ERROR_MLX, m);
		item = ft_lstnew(img);
		if (item == NULL)
			exit_error(ERROR_MEM, m);
		ft_lstadd_front(&m->strings, item);
		y_pos += 20;
		i++;
	}
}

void	draw_chrome(t_meta *m)
{
	static const char	*chrome[13] = {
		"rotate world x/y: mouse",
		"rotate world z: [ / ]",
		"rotate cam x/y: lshift + mouse",
		"rotate cam z: arrow l/r",
		"z trans cam: scroll | arrow u/d",
		"x/y-trans cam: wsad",
		"expand / collapse model: +/-",
		"scale model: </>",
		"reset cam: 0",
		"parallel / perspective: p",
		"fade to vanish: f",
		"cycle colors: c",
		"show/hide overlays: h"
	};

	m->chrome = CHROME;
	make_lines(m, chrome);
	update_rotation_disp(m);
}

void	remove_chrome(t_meta *m)
{
	free_strings_list(&m->strings, m);
	mlx_delete_image(m->mlx, m->rotations[0]);
	mlx_delete_image(m->mlx, m->rotations[1]);
	m->chrome = NO_CHROME;
}
