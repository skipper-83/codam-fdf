/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/02/05 23:52:52 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		g_img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		g_img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		g_img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		g_img->instances[0].x += 5;
}

void	handle_mouse(mouse_key_t b, action_t a, modifier_key_t m, void *param)
{
	mlx_t			*mlx;
	static t_pixel	pix1;
	static t_pixel	pix2;
	static int		count;

	if (a == MLX_PRESS)
	{
		mlx = (mlx_t *)param;
		if (! (count++ % 2))
		{
			mlx_get_mouse_pos(mlx, &pix1.x, &pix1.y);
			mlx_put_pixel(g_img, pix1.x, pix1.y, 0XFF0000FF);
		}
		else
		{
			mlx_get_mouse_pos(mlx, &pix2.x, &pix2.y);
			mlx_put_pixel(g_img, pix2.x, pix2.y, 0XFF0000FF);
			draw_line(pix1, pix2);
			count = 0;
		}
	}
}

int32_t	main(void)
{
	mlx_t	*mlx;

	ft_printf("Printf test %22f\n", 25443.);
	mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!mlx)
		exit(EXIT_FAILURE);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	memset(g_img->pixels, 255, g_img->width * g_img->height * sizeof(int));
	mlx_image_to_window(mlx, g_img, 0, 0);
	mlx_mouse_hook(mlx, &handle_mouse, mlx);
	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
