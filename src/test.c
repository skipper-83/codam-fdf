/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/02/22 22:54:53 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <errno.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_meta	*m;

	m = (t_meta *)param;
	if (keydata.key == MLX_KEY_P && keydata.action == MLX_PRESS)
	{
		if (m->projection == PARALLEL)
		{
			apply_rotate(&m->camera, m->transformer, 180, 'z');
			m->projection = PERSPECTIVE;
			create_new_image(m);
		}
		else
		{
			apply_rotate(&m->camera, m->transformer, 180, 'z');
			m->projection = PARALLEL;
			create_new_image(m);
		}
	}
	if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
	{
		if (m->fade_alpha)
		{
			m->fade_alpha = 0;
			create_new_image(m);
		}
		else
		{
			m->fade_alpha = 1;
			create_new_image(m);
		}
	}

}

void	mouse_rotate(t_meta *m, t_angle *rotation_axis, float ***view, float p)
{
	int			x_now;
	int			y_now;
	int			draw;
	t_angle		angle;

	draw = 0;
	mlx_get_mouse_pos(m->mlx, &x_now, &y_now);
	angle.x = (y_now - m->mouse_y) / p;
	angle.y = -(x_now - m->mouse_x) / p;
	if (m->mouse_x && angle.x)
	{
		rotation_axis->x += angle.x;
		apply_rotate(view, m->transformer, angle.x, 'x');
		draw = 1;
	}
	if (m->mouse_y && angle.y)
	{
		rotation_axis->y += angle.y;
		apply_rotate(view, m->transformer, angle.y, 'y');
		draw = 1;
	}
	if (draw)
		create_new_image(m);
	m->mouse_x = x_now;
	m->mouse_y = y_now;
}

void	frame_hook(void *param)
{
	t_meta		*m;
	float		coeff;

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
	if (mlx_is_key_down(m->mlx, MLX_KEY_MINUS))
		scale_world(m, 1, 1, .99);
	if (mlx_is_key_down(m->mlx, MLX_KEY_EQUAL))
		scale_world(m, 1, 1, 1.01);
	if (mlx_is_key_down(m->mlx, MLX_KEY_W))
		translate_cam(m, 0, -.1, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_S))
		translate_cam(m, 0, .1, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_A))
		translate_cam(m, -.1, 0, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_D))
		translate_cam(m, .1, 0, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_L))
	// 	translate_world(m, .1, 0, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_J))
	// 	translate_world(m, -.1, 0, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_I))
	// 	translate_world(m, 0, -.1, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_K))
	// 	translate_world(m, 0, .1, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_T))
	// 	translate_cam(m, 0, -.1, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_G))
	// 	translate_cam(m, 0, .1, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_F))
	// 	translate_cam(m, -.1, 0, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_H))
	// 	translate_cam(m, .1, 0, 0);
	// if (mlx_is_key_down(m->mlx, MLX_KEY_SEMICOLON))
	// 	rotate_cam(m, 1, 'z');
	// if (mlx_is_key_down(m->mlx, MLX_KEY_APOSTROPHE))
	// 	rotate_cam(m, -1, 'z');
	if (mlx_is_key_down(m->mlx, MLX_KEY_0))
	{
		reset_cam(m);
		// m44_to_identity_matrix(m->world);
		// m44_to_identity_matrix(m->camera);
		// apply_rotate(&m->camera, m->transformer, 180, 'x');
		// apply_rotate(&m->camera, m->transformer, 135, 'z');
		// coeff = m->drawing_w;
		// if (m->drawing_d * .3 > m->drawing_w)
		// 	coeff = m->drawing_d * .3;
		// m44_translate(m->camera, 0, 0, (coeff) * 1.8);
		// create_new_image(m);
	}
	// if (mlx_is_key_down(m->mlx, MLX_KEY_9))
	// {
	// 	m44_to_identity_matrix(m->world);
	// 	m44_to_identity_matrix(m->camera);
	// 	coeff = m->drawing_w;
	// 	if (m->drawing_d * .3 > m->drawing_w)
	// 		coeff = m->drawing_d * .3;
	// 	m44_translate(m->camera, 0, 0, -2 * (coeff));
	// 	apply_rotate(&m->camera, m->transformer, 60, 'x');
	// 	apply_rotate(&m->camera, m->transformer, -60, 'y');
	// 	create_new_image(m);
	// }
	if (mlx_is_mouse_down(m->mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT_SUPER))
			mouse_rotate(m, &m->world_rotation, &m->camera, 20);
		else
			mouse_rotate(m, &m->cam_rotation, &m->camera, 5);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(m->mlx);
}

void handle_resize(int width, int height, void* param)
{
	t_meta	*m;

	m = (t_meta *)param;
	m->window_h = height;
	m->window_w = width;
	m->canvas_h = height / 100.0;
	m->canvas_w = width / 100.0;
	create_new_image(m);
}

void	handle_mouse(mouse_key_t b, action_t a, modifier_key_t mod, void *param)
{
	t_meta			*m;
	static t_pixel	pix1;
	static t_pixel	pix2;
	static int		count;

	m = (t_meta *)param;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
	{
		if (mod == 0)
		{
			if (!m->is_rendered)
			{
				parse_file(m);
				m->is_rendered = 1;
				create_new_image(m);
			}
		}
		if (mod == 8)
		{
			if (! (count++ % 2))
			{
				mlx_get_mouse_pos(m->mlx, &pix1.x, &pix1.y);
				pix1.color = 0xFF0000FF;
				mlx_put_pixel(m->img, pix1.x, pix1.y, 0XFF0000FF);
			}
			else
			{
				mlx_get_mouse_pos(m->mlx, &pix2.x, &pix2.y);
				mlx_put_pixel(m->img, pix2.x, pix2.y, 0XFF0000FF);
				pix2.color = 0xFF0000FF;
				pix1.enabled = 1;
				pix2.enabled = 1;
				draw_line(m->img, pix1, pix2);
				count = 0;
			}
		}
	}
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_RELEASE)
	{
		m->mouse_y = 0;
		m->mouse_x = 0;
	}
}

void handle_scroll(double xdelta, double ydelta, void* param)
{
	t_meta	*m;

	m = (t_meta *)param;
	if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT_SUPER))
		translate_cam(m, 0, 0, (float)ydelta / 10.0);
	else
		translate_cam(m, 0, 0, ydelta);
}

void	f(void)
{
	system("leaks fdf");
}

int32_t	main(int argc, char **argv)
{
	t_meta	*m;

	atexit(f);
	errno = 0;
	if (argc != 2)
		exit_error(ERROR_NO_MAP, m);
	m = init_meta(argv[1]);
	m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	// ft_memset(m->img->pixels, 255, WIDTH * HEIGHT * sizeof(int));
	mlx_image_to_window(m->mlx, m->img, 0, 0);
	mlx_mouse_hook(m->mlx, handle_mouse, m);
	mlx_resize_hook(m->mlx, handle_resize, m);
	mlx_scroll_hook(m->mlx, handle_scroll, m);
	mlx_key_hook(m->mlx, key_hook, m);
	mlx_loop_hook(m->mlx, frame_hook, m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	free_meta(m);

	return (EXIT_SUCCESS);
}
