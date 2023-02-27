/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_frame_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 23:37:30 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/27 21:34:11 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static	void	do_rot(t_meta *m, t_angle angle, float ***view, t_angle *axis)
{
	int			draw;

	draw = 0;
	if (m->mouse_x && angle.x)
	{
		axis->x += angle.x;
		apply_rotate(view, m->transformer, angle.x, 'x');
		draw = 1;
	}
	if (view == NULL)
		exit_error(ERROR_MEM, m);
	if (m->mouse_y && angle.y)
	{
		axis->y += angle.y;
		apply_rotate(view, m->transformer, angle.y, 'y');
		draw = 1;
	}
	if (view == NULL)
		exit_error(ERROR_MEM, m);
	if (draw)
		create_new_image(m);
}

static void	mouse_rotate(t_meta *m, t_angle *rot_axis, float ***view, float p)
{
	int			x_now;
	int			y_now;
	t_angle		angle;

	mlx_get_mouse_pos(m->mlx, &x_now, &y_now);
	angle.x = (y_now - m->mouse_y) / p;
	angle.y = -(x_now - m->mouse_x) / p;
	do_rot(m, angle, view, rot_axis);
	m->mouse_x = x_now;
	m->mouse_y = y_now;
}

static void	frame_hook2(t_meta *m)
{
	if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT_BRACKET))
		rotate_world(m, 1, 'z');
	if (mlx_is_key_down(m->mlx, MLX_KEY_RIGHT_BRACKET))
		rotate_world(m, -1, 'z');
	if (mlx_is_key_down(m->mlx, MLX_KEY_MINUS))
		expand_world(m, 0.99);
	if (mlx_is_key_down(m->mlx, MLX_KEY_EQUAL))
		expand_world(m, 1.01);
	if (mlx_is_key_down(m->mlx, MLX_KEY_W))
		translate_cam(m, 0, -.1, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_S))
		translate_cam(m, 0, .1, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_A))
		translate_cam(m, -.1, 0, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_D))
		translate_cam(m, .1, 0, 0);
	if (mlx_is_mouse_down(m->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT_SHIFT))
			mouse_rotate(m, &m->cam_rotation, &m->camera, 5);
		else
			mouse_rotate(m, &m->world_rotation, &m->world, 5);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(m->mlx);
}

void	frame_hook(void *param)
{
	t_meta		*m;

	m = (t_meta *)param;
	if (mlx_is_key_down(m->mlx, MLX_KEY_COMMA))
		scale_world(m, 0.99, 0.99, 0.99);
	if (mlx_is_key_down(m->mlx, MLX_KEY_PERIOD))
		scale_world(m, 1.01, 1.01, 1.01);
	if (mlx_is_key_down(m->mlx, MLX_KEY_UP))
		translate_cam(m, 0, 0, -1);
	if (mlx_is_key_down(m->mlx, MLX_KEY_DOWN))
		translate_cam(m, 0, 0, 1);
	if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT))
		rotate_cam(m, 1, 'z');
	if (mlx_is_key_down(m->mlx, MLX_KEY_RIGHT))
		rotate_cam(m, -1, 'z');
	frame_hook2(m);
}

void	handle_mouse(mouse_key_t b, action_t a, modifier_key_t mod, void *prm)
{
	t_meta			*m;

	m = (t_meta *)prm;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
	{
		if (mod == 0)
		{
			if (!m->is_rendered)
			{
				parse_file(m);
				m->is_rendered = 1;
				free_strings_list(&m->strings, m);
				create_new_image(m);
				if (m->chrome == CHROME)
					draw_chrome(m);
			}
		}
	}
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_RELEASE)
	{
		m->mouse_y = 0;
		m->mouse_x = 0;
	}
}
