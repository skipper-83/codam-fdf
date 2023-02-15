/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/02/15 15:56:22 by avan-and         ###   ########.fr       */
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

void	create_new_image(t_meta *m, float **world, float **camera)
{
	mlx_image_t	*new;
	t_list		*head;
	t_pixel		*map;
	t_point		*point;
	float		**inverse;

	inverse = NULL;
	if (world == NULL)
		world = m44_init();
	if (world == NULL)
		exit_error(ERROR_MEM);
	if (camera)
	{
		inverse = m44_invert(camera);
		if (inverse == NULL)
			exit_error(ERROR_MEM);
		world = m44_dot_product(world, inverse, FREE_M1);
		m44_free(inverse);
	}	
	head = m->points;
	while (head)
	{
		point = (t_point *)head->content;
		m44_multiply_point(world, point);
		head = head->next;
	}
	new = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	map = point_to_pix(m);
	draw_pixels(map, m, new);
	draw_raster(map, m, new);
	mlx_image_to_window(m->mlx, new, 0, 0);
	mlx_delete_image(m->mlx, m->img);
	free(map);
	m->img = new;
	m44_free(world);
	if (camera)
		m44_free(camera);
}

t_pixel	*point_to_pix(t_meta *m)
{
	int		cols;
	int		rows;
	int		i;
	t_list	*head;
	t_pixel	*res;
	t_point	*point;

// ft_printf("ptp1\n");
	cols = m->drawing_w;
	rows = m->drawing_h;
	head = m->points;
	res = malloc(sizeof(t_pixel) * (m->drawing_w * m->drawing_h));
	i = m->drawing_w * m->drawing_h - 1;
	// ft_printf("size: %i\n", m->drawing_w * m->drawing_h);
	if (res == NULL)
		exit_error(ERROR_MEM);
		// ft_printf("ptp2\n");
	while (rows > 0)
	{
		while (cols > 0)
		{
			point = (t_point *)head->content;
			// ft_printf("point: %f, %f, %f\n", point->x, point->y, point->z);
			res[i].x = point->x / point->z;
			res[i].y = point->y / point->z;
			res[i].color = point->color;
			res[i].enabled = 1;
			if (point->z < 0)
				res[i].enabled = 0;
			// ft_printf("%i: %i, %i @ %#x\n", i, res[i].x, res[i].y, res[i].color);
			head = head->next;
			i--;
			cols--;
		}
		rows--;
		cols = m->drawing_w;
	}	
	// ft_printf("ptp3: %i\n", i);
	return (res);
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
	if (mlx_is_key_down(m->mlx, MLX_KEY_COMMA))
	{
		// ft_printf("comma %i\n", count++);
		world = m44_init();
		if (world == NULL)
			exit_error(ERROR_MEM);
		m44_translate(world, 0, 0, .01);
		create_new_image(m, NULL, world);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_PERIOD))
	{
		// ft_printf("comma %i\n", count++);
		world = m44_init();
		if (world == NULL)
			exit_error(ERROR_MEM);
		m44_translate(world, 0, 0, -.01);
		// m44_scale(world, 1.01, 1.01, 1);
		create_new_image(m, NULL, world);

	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_W))
	{
		world = m44_init();
		if (world == NULL)
			exit_error(ERROR_MEM);
		m44_rotate(world, .1, 'x');
		// m44_scale(world, 1.01, 1.01, 1);
		create_new_image(m, NULL, world);
	}
	if (mlx_is_key_down(m->mlx, MLX_KEY_S))
	{
		world = m44_init();
		if (world == NULL)
			exit_error(ERROR_MEM);
		m44_rotate(world, -.1, 'x');
		// m44_scale(world, 1.01, 1.01, 1);
		create_new_image(m, NULL, world);
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

	// b = 0;
	// mod = 0;
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
			// for (int i=0; i<m->drawing_w * m->drawing_h; i++)
			// {
			// 	ft_printf("%i, %i\n", map[i].x, map[i].y);
			// }
			draw_pixels(map, m, m->img);
			// ft_lstiter(m->points, &draw_points);
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
			ft_printf("mouse count: %i\n", count);
			mlx_get_mouse_pos(m->mlx, &pix2.x, &pix2.y);
			mlx_put_pixel(m->img, pix2.x, pix2.y, 0XFF0000FF);
			pix2.color = 0xFF0000FF;
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
	mlx_loop_hook(m->mlx, &hook, m);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	ft_lstclear(&(m->points), free);
	free(m);

	return (EXIT_SUCCESS);
}
