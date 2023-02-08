/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/02/08 23:24:54 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	hook(void *param)
{
	mlx_t	*mlx;

	mlx = (mlx_t *)param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

void	handle_mouse(mouse_key_t b, action_t a, modifier_key_t mod, void *param)
{
	t_meta			*m;
	static t_pixel	pix1;
	static t_pixel	pix2;
	static int		count;
	mlx_image_t		*new;

	b = 0;
	mod = 0;
	if (a == MLX_PRESS)
	{
		m = (t_meta *)param;

		// new = mlx_new_image(m->mlx, WIDTH, HEIGHT);
		// ft_memset(new->pixels, 100, new->width * new->height * sizeof(int));
		// mlx_image_to_window(m->mlx, new, 0, 0);
		// mlx_delete_image(m->mlx, m->img);
		// m->img = new;
		if (! (count++ % 2))
		{
			mlx_get_mouse_pos(m->mlx, &pix1.x, &pix1.y);
			mlx_put_pixel(m->img, pix1.x, pix1.y, 0XFF0000FF);
		}
		else
		{
			mlx_get_mouse_pos(m->mlx, &pix2.x, &pix2.y);
			mlx_put_pixel(m->img, pix2.x, pix2.y, 0XFF0000FF);
			draw_line(m->img, pix1, pix2);
			count = 0;
		}
	}
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

void	print_point(void *param)
{
	t_point	*point;
	static int	counter;

	point = (t_point *)param;
	ft_printf("% 3i: % 3i : % 3i : % 3i : %#x; \n", counter++, point->x, point->y, point->z, point->color);
}

t_list	*add_point(t_list **head, int x, int y, char **point_arr)
{
	t_list	*new;
	t_point	*point;

	point = malloc(sizeof(t_point));
	if (point == NULL)
		return (ft_lstclear(head, free), NULL);
	point->x = x;
	point->y = y;
	point->z = ft_atoi(point_arr[Z]);
	if (point_arr[COLOR])
		point->color = ft_atoi(point_arr[COLOR]); // FIX: GET COLOR FROM HEX
	else
		point->color = DEFAULT_COLOR;
	new = ft_lstnew(point);
	if (new == NULL)
		return (free(point), ft_lstclear(head, free), NULL);
	ft_lstadd_back(head, new);
	return (*head);
}


t_list	*parse_line(char *line, t_list *res, int y, t_meta *m)
{
	char		**line_arr;
	char		**point_arr;
	int			i;

	line_arr = ft_split(line, ' ');
	if (line_arr == NULL)
		return (NULL);
	i = 0;
	while (line_arr[i][0] != '\n')
	{
		point_arr = ft_split(line_arr[i], ',');
		res = add_point(&res, i + 1, y, point_arr);
		if (res == NULL)
			return (free_array(line_arr), NULL);
		free_array(point_arr);
		i++;
	}
	if (m->drawing_w == 0)
		m->drawing_w = i;
	if (m->drawing_w != i)
		return (ft_lstclear(&res, free), free_array(line_arr), NULL);
	free_array(line_arr);
	return (res);
}

t_list	*parse_file(char *filename, t_meta *m)
{
	int		fd;
	int		y;
	char	*line;
	t_list	*res;

	y = 0;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	res = NULL;
	while (line)
	{
		res = parse_line(line, res, y + 1, m);
		if (res == NULL)
			return (free(line), NULL);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	m->drawing_h = y;
	ft_lstiter(res, &print_point);
	return (res);
}

void	f(void)
{
	system("leaks fdf");
}

int32_t	main(int argc, char **argv)
{
	t_meta	*m;

	atexit(f);
	m = (t_meta *)ft_calloc(1, sizeof(t_meta));
	m->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!m->mlx)
		exit(EXIT_FAILURE);
	m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	ft_memset(m->img->pixels, 255, WIDTH * HEIGHT * sizeof(int));
	mlx_image_to_window(m->mlx, m->img, 0, 0);
	mlx_mouse_hook(m->mlx, &handle_mouse, m);
	mlx_loop_hook(m->mlx, &hook, m->mlx);
	if (argc == 2)
		m->points = parse_file(argv[1], m);
	// ft_printf("width %i, height %i\n", m->drawing_w, m->drawing_h);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	ft_lstclear(&(m->points), free);
	free(m);
	return (EXIT_SUCCESS);
}
