/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_key_scroll_resize.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 22:53:51 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/27 22:21:38 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	handle_key2(mlx_key_data_t keydata, t_meta *m)
{
	if (keydata.key == MLX_KEY_0 && keydata.action == MLX_PRESS)
		reset_cam(m);
	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		cycle_colorschemes(m);
	if (keydata.key == MLX_KEY_H && keydata.action == MLX_PRESS)
	{
		if (m->chrome == CHROME)
			remove_chrome(m);
		else
			draw_chrome(m);
	}
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (m->fade_alpha)
			m->fade_alpha = 0;
		else
			m->fade_alpha = 1;
		create_new_image(m);
	}
}

static void	execute_projection_change(t_meta *m)
{
	if (m->projection == PARALLEL)
	{
		scale_world(m, 1 / (10.0 / m->drawing_w), \
				1 / (10.0 / m->drawing_w), 1 / (10.0 / m->drawing_w));
		m44_translate(m->camera, 0, 0, m->drawing_h * 4);
		apply_rotate(&m->camera, m->transformer, -135, 'z');
		m->projection = PERSPECTIVE;
	}
	else
	{
		scale_world(m, 10.0 / m->drawing_w, \
				10.0 / m->drawing_w, 10.0 / m->drawing_w);
		m44_translate(m->camera, 0, 0, m->drawing_h * -4);
		apply_rotate(&m->camera, m->transformer, 135, 'z');
		m->projection = PARALLEL;
	}
	if (m->camera == NULL)
		exit_error(ERROR_MEM, m);
	create_new_image(m);
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_meta	*m;

	m = (t_meta *)param;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		execute_projection_change(m);
	}
	handle_key2(keydata, m);
}

void	handle_scroll(double xdelta, double ydelta, void *param)
{
	t_meta	*m;

	(void)xdelta;
	m = (t_meta *)param;
	if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT_SUPER))
		translate_cam(m, 0, 0, (float)ydelta / 10.0);
	else
		translate_cam(m, 0, 0, ydelta);
}

void	handle_resize(int width, int height, void *param)
{
	t_meta	*m;

	m = (t_meta *)param;
	m->window_h = height;
	m->window_w = width;
	m->canvas_w = width / 100.0;
	m->canvas_h = height / 100.0;
	if (m->chrome == CHROME)
	{
		remove_chrome(m);
		draw_chrome(m);
	}
	create_new_image(m);
}
