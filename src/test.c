/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/02/21 10:58:53 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <errno.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
}

void	hook(void *param)
{
	t_meta		*m;
	float		coeff;

	m = (t_meta *)param;
	if (mlx_is_key_down(m->mlx, MLX_KEY_COMMA))
		translate_cam(m, 0, 0, -1);
	if (mlx_is_key_down(m->mlx, MLX_KEY_PERIOD))
		translate_cam(m, 0, 0, 1);
	if (mlx_is_key_down(m->mlx, MLX_KEY_UP))
		rotate_cam(m, .1, 'x');
	if (mlx_is_key_down(m->mlx, MLX_KEY_DOWN))
		rotate_cam(m, -.1, 'x');
	if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT))
		rotate_cam(m, .1, 'y');
	if (mlx_is_key_down(m->mlx, MLX_KEY_RIGHT))
		rotate_cam(m, -.1, 'y');
	if (mlx_is_key_down(m->mlx, MLX_KEY_MINUS))
		scale_world(m, 1, 1, .99);
	if (mlx_is_key_down(m->mlx, MLX_KEY_EQUAL))
		scale_world(m, 1, 1, 1.01);
	if (mlx_is_key_down(m->mlx, MLX_KEY_W))
		rotate_world(m, -.1, 'x');
	if (mlx_is_key_down(m->mlx, MLX_KEY_S))
		rotate_world(m, .1, 'x');
	if (mlx_is_key_down(m->mlx, MLX_KEY_A))
		rotate_world(m, -.1, 'y');
	if (mlx_is_key_down(m->mlx, MLX_KEY_D))
		rotate_world(m, .1, 'y');
	if (mlx_is_key_down(m->mlx, MLX_KEY_L))
		translate_world(m, .1, 0, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_J))
		translate_world(m, -.1, 0, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_I))
		translate_world(m, 0, -.1, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_K))
		translate_world(m, 0, .1, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_T))
		translate_cam(m, 0, -.1, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_G))
		translate_cam(m, 0, .1, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_F))
		translate_cam(m, -.1, 0, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_H))
		translate_cam(m, .1, 0, 0);
	if (mlx_is_key_down(m->mlx, MLX_KEY_SEMICOLON))
		rotate_cam(m, 1, 'z');
	if (mlx_is_key_down(m->mlx, MLX_KEY_APOSTROPHE))
		rotate_cam(m, -1, 'z');
	if (mlx_is_key_down(m->mlx, MLX_KEY_0))
	{
		m44_to_identity_matrix(m->world);
		m44_to_identity_matrix(m->camera);
		apply_rotate(&m->camera, m->transformer, 180, 'x');
		apply_rotate(&m->camera, m->transformer, 135, 'z');
		coeff = m->drawing_w;
		if (m->drawing_d * .3 > m->drawing_w)
			coeff = m->drawing_d * .3;
		m44_translate(m->camera, 0, 0, (coeff) * 1.8);
		create_new_image(m);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_9))
	{
		m44_to_identity_matrix(m->world);
		m44_to_identity_matrix(m->camera);
		coeff = m->drawing_w;
		if (m->drawing_d * .3 > m->drawing_w)
			coeff = m->drawing_d * .3;
		m44_translate(m->camera, 0, 0, -2 * (coeff));
		apply_rotate(&m->camera, m->transformer, 60, 'x');
		apply_rotate(&m->camera, m->transformer, -60, 'y');
		create_new_image(m);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_P))
	{
		if (m->projection != PERSPECTIVE)
		{
			apply_rotate(&m->camera, m->transformer, 180, 'z');
			m->projection = PERSPECTIVE;
			create_new_image(m);
		}
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_O))
	{
		if (m->projection != PARALLEL)
		{
			apply_rotate(&m->camera, m->transformer, 180, 'z');
			m->projection = PARALLEL;
			create_new_image(m);
		}
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(m->mlx);
}

void	handle_mouse(mouse_key_t b, action_t a, modifier_key_t mod, void *param)
{
	t_meta			*m;
	static t_pixel	pix1;
	static t_pixel	pix2;
	static int		count;
	mlx_image_t		*new;
	static t_pixel			*map;

	ft_printf("mod: %i\n", mod);
	m = (t_meta *)param;
	if (b == MLX_MOUSE_BUTTON_RIGHT && a == MLX_PRESS)
	{
		if (mod == 0)
		{
			ft_printf("Right click\n");
			parse_file(m);
			map = points_to_pixels(m);
			draw_pixels(map, m, m->img);
		}
		if (mod == 8)
		{
			draw_raster(map, m, m->img);
			free (map);
			ft_printf("map drawn\n");
		}

	}
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
	{
		ft_printf("left click\n");

		if (! (count++ % 2))
		{
			ft_printf("mouse count: %i\n", count);
			mlx_get_mouse_pos(m->mlx, &pix1.x, &pix1.y);
			pix1.color = 0xFF0000FF;
			mlx_put_pixel(m->img, pix1.x, pix1.y, 0XFF0000FF);
		}
		else
		{
			ft_printf("mouse count: %i - drawing\n", count);
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

void	f(void)
{
	system("leaks fdf");
}

int32_t	main(int argc, char **argv)
{
	t_meta	*m;

	// atexit(f);
	errno = 0;
	if (argc != 2)
		exit_error(ERROR_NO_MAP);
	m = init_meta(argv[1]);
	m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	// ft_memset(m->img->pixels, 255, WIDTH * HEIGHT * sizeof(int));
	mlx_image_to_window(m->mlx, m->img, 0, 0);
	mlx_mouse_hook(m->mlx, &handle_mouse, m);
	mlx_key_hook(m->mlx, key_hook, m);
	mlx_loop_hook(m->mlx, &hook, m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	ft_lstclear(&(m->points), free);
	m44_free(m->world);
	m44_free(m->camera);
	m44_free(m->transformer);
	free(m);

	return (EXIT_SUCCESS);
}
