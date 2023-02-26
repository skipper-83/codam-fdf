/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 00:40:08 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/02/26 14:12:15 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <errno.h>

void	welcome_msg(t_meta *m)
{
	mlx_image_t	*msg;

	msg = mlx_put_string(m->mlx, "Left click to start", \
					m->window_w / 2 - 100, m->window_h / 2 - 20);
	if (msg == NULL)
		exit_error(ERROR_MLX, m);
	m->strings = ft_lstnew(msg);
	if (m->strings == NULL)
		exit_error(ERROR_MEM, m);
}

void	f(void)
{
	system ("leaks fdf");
}

int	main(int argc, char **argv)
{
	t_meta	*m;

	errno = 0;
	atexit(f);
	if (argc != 2)
		exit_error(ERROR_NO_MAP, m);
	m = init_meta(argv[1]);
	welcome_msg(m);
	mlx_mouse_hook(m->mlx, handle_mouse, m);
	mlx_resize_hook(m->mlx, handle_resize, m);
	mlx_scroll_hook(m->mlx, handle_scroll, m);
	mlx_key_hook(m->mlx, handle_key, m);
	mlx_loop_hook(m->mlx, frame_hook, m);
	mlx_loop(m->mlx);
	free_strings_list(&m->strings, m);
	mlx_terminate(m->mlx);
	free_meta(m);
	return (EXIT_SUCCESS);
}
