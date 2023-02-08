/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-and <avan-and@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/02/08 15:06:06 by avan-and         ###   ########.fr       */
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

t_list	*add_point(int x, int y, int *z_color)
{
	
}

t_list	*parse_line(char *line, t_list *res, int y)
{
	int	*line_arr;
	int	i;

	line_arr = ft_split(line, ' ');
	i = 0;
	while (line_arr[i])
	{
		
		i++;
	}
}

t_list	*parse_file(char *filename)
{
	int		fd;
	int		y;
	char	*line;
	t_list	*res;

	y = 1;
	fd = open(filename, O_RDONLY);
	line = get_next_line(fd);
	res = parse_line(line, res, y);
	while (line)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	return (NULL);
}

void	f(void)
{
	system("leaks fdf");
}

int32_t	main(int argc, char **argv)
{
	t_meta	*m;

	atexit(f);
	m = (t_meta *)malloc(sizeof (t_meta));
	m->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!m->mlx)
		exit(EXIT_FAILURE);
	m->img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	ft_memset(m->img->pixels, 255, WIDTH * HEIGHT * sizeof(int));
	mlx_image_to_window(m->mlx, m->img, 0, 0);
	mlx_mouse_hook(m->mlx, &handle_mouse, m);
	mlx_loop_hook(m->mlx, &hook, m->mlx);
	if (argc == 2)
		parse_file(argv[1]);
	mlx_loop(m->mlx);
	mlx_terminate(m->mlx);
	free(m);
	return (EXIT_SUCCESS);
}
