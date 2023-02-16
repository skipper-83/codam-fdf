/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/02/16 17:42:45 by avan-and         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <errno.h>

// void	draw_points(void *param)
// {
// 	t_point	*point;

// 	point = (t_point *)param;
// 	// ft_printf("x: %i, meta: %p\n", point->x, point->m);
// 	mlx_put_pixel(point->m->img, point->x, point->y, point->color);
// }
t_pixel	*point_to_pix(t_meta *m);

void	create_new_image(t_meta *m)
{
	t_list		*head;
	t_pixel		*map;
	t_point		*point;
	mlx_image_t	*new;
	float		**inverse;

	inverse = m44_invert(m->camera);
	if (inverse == NULL)
		exit_error(ERROR_MEM);
	// ft_printf("inverse\n");
	// m44_print(inverse);
	m->transformer = m44_dot_product(m->world, inverse, KEEP_M1);
	m44_free(inverse);
	head = m->points;
	while (head)
	{
		point = (t_point *)head->content;
		m44_multiply_point(m->transformer, point);
		head = head->next;
	}
	new = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	map = point_to_pix(m);
	draw_pixels(map, m, new);
	draw_raster(map, m, new);
	mlx_image_to_window(m->mlx, new, 0, 0);
	mlx_delete_image(m->mlx, m->img);
	free(map);
	m44_free(m->transformer);
	m44_to_identity_matrix(m->camera);
	m->img = new;
}

typedef void	(*t_transform_func)(t_meta *m);

void	zoom_in(t_meta *m)
{
	m44_translate(m->camera, 0, 0, 1);
	create_new_image(m);
}

void	zoom_out(t_meta *m)
{
	m44_translate(m->camera, 0, 0, -1);
	create_new_image(m);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_meta							*m;
	static const t_transform_func	trans_func[256] = {
	[MLX_KEY_COMMA] = zoom_in,
	[MLX_KEY_PERIOD] = zoom_out,
	};

	m = (t_meta *)param;
	// while (keydata.action > 0)
	if (keydata.action > 0)
		trans_func[keydata.key](m);
	// ft_printf("key pressed: %i, action: %i\n", keydata.key, keydata.action);
}

void	hook(void *param)
{
	t_meta		*m;
	float		**world;
	float		**inverse;
	t_list		*head;
	t_point		*point;
	mlx_image_t *new;
	static int 	count;
	t_pixel		*map;

	m = (t_meta *)param;
	// if (mlx_is_key_down(m->mlx, MLX_KEY_COMMA))
	// {
	// 	// ft_printf("comma %i\n", count++);
	// 	// m44_translate(m->camera, 0, 0, .01);
	// 	// ft_printf("zooming in\n");
	// 	m44_translate(m->camera, 0, 1, 0);
	// 	// m44_print(m->camera);
	// 	create_new_image(m);
	// 	// zoom_in(m);
	// 	// create_new_image(m);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_PERIOD))
	// {
	// 	// ft_printf("comma %i\n", count++);
	// 	// ft_printf("zooming out\n");
	// 	m44_translate(m->camera, 0, -1, 0);
	// 	// m44_print(m->camera);
	// 	create_new_image(m);
	// 	// zoom_out(m);
	// 	// world = m44_init();
	// 	// if (world == NULL)
	// 	// 	exit_error(ERROR_MEM);
	// 	// m44_translate(world, 0, 0, -.01);
	// 	// // m44_scale(world, 1.01, 1.01, 1);
	// 	// create_new_image(m, NULL, world);

	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_W))
	// {
	// 	world = m44_init();
	// 	if (world == NULL)
	// 		exit_error(ERROR_MEM);
	// 	m44_rotate(world, .01, 'x');
	// 	// m44_scale(world, 1.01, 1.01, 1);
	// 	create_new_image(m, world, NULL);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_S))
	// {
	// 	world = m44_init();
	// 	if (world == NULL)
	// 		exit_error(ERROR_MEM);
	// 	m44_rotate(world, -.01, 'x');
	// 	// m44_scale(world, 1.01, 1.01, 1);
	// 	create_new_image(m, world, NULL);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_A))
	// {
	// 	world = m44_init();
	// 	if (world == NULL)
	// 		exit_error(ERROR_MEM);
	// 	m44_rotate(world, .01, 'y');
	// 	// m44_scale(world, 1.01, 1.01, 1);
	// 	create_new_image(m, world, NULL);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_D))
	// {
	// 	world = m44_init();
	// 	if (world == NULL)
	// 		exit_error(ERROR_MEM);
	// 	m44_rotate(world, -.01, 'y');
	// 	// m44_scale(world, 1.01, 1.01, 1);
	// 	create_new_image(m, world, NULL);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_DOWN))
	// {
	// 	world = m44_init();
	// 	if (world == NULL)
	// 		exit_error(ERROR_MEM);
	// 	m44_translate(world, 0, -1, 0);
	// 	create_new_image(m, NULL, world);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_UP))
	// {
	// 	world = m44_init();
	// 	if (world == NULL)
	// 		exit_error(ERROR_MEM);
	// 	m44_translate(world, 0, 1, 0);
	// 	create_new_image(m, NULL, world);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_LEFT))
	// {
	// 	world = m44_init();
	// 	if (world == NULL)
	// 		exit_error(ERROR_MEM);
	// 	m44_translate(world, 1, 0, 0);
	// 	create_new_image(m, NULL, world);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_RIGHT))
	// {
	// 	world = m44_init();
	// 	if (world == NULL)
	// 		exit_error(ERROR_MEM);
	// 	m44_translate(world, -1, 0, 0);
	// 	create_new_image(m, NULL, world);
	// }
	// if (mlx_is_key_down(m->mlx, MLX_KEY_A) && mlx_is_key_down(m->mlx, MLX_KEY_S))
	// 	ft_printf("double tap\n");
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
			print_meta(m);
			map = point_to_pix(m);
			draw_pixels(map, m, m->img);
		}
		if (mod == 8)
		{
			draw_raster(map, m, m->img);
			free (map);
			ft_printf("map drawn\n");
		}
		// ft_printf("map parsed\n");

	}
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
	{
		ft_printf("left click\n");

		// new = mlx_new_image(m->mlx, WIDTH, HEIGHT);
		// ft_memset(new->pixels, 100, new->width * new->height * sizeof(int));
		// mlx_image_to_window(m->mlx, new, 0, 0);
		// mlx_delete_image(m->mlx, m->img);
		// m->img = new;
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


t_meta	*init_meta(char *filename)
{
	t_meta	*m;

	m = (t_meta *)ft_calloc(1, sizeof(t_meta));
	if (m == NULL)
		exit_error(ERROR_MEM);
	m->mlx = mlx_init(WIDTH, HEIGHT, WINDOW_NAME, true);
	if (m->mlx == NULL)
		exit_error(ERROR_MLX);
	m->filename = filename;
	m->max_z = INT32_MIN;
	m->min_z = INT32_MAX;
	m->world = m44_init();
	m->camera = m44_init();
	if (m->world == NULL || m->camera == NULL)
		exit_error(ERROR_MEM);
	// parse_file(m);
	// ft_lstiter(m->points, &print_point);
	// print_meta(m);
	return (m);
}

int32_t	main(int argc, char **argv)
{
	t_meta	*m;

	atexit(f);
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
	free(m);

	return (EXIT_SUCCESS);
}
