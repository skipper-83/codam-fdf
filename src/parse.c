/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:41:20 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/27 22:00:45 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	has_digits(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}

static void	add_point(t_meta *m, int x, int y, char **point_arr)
{
	t_list	*new;
	t_point	*point;

	point = exit_on_null(malloc(sizeof(t_point)), m);
	point->x = x;
	point->y = y;
	point->z = ft_atoi(point_arr[Z]);
	if (point_arr[COLOR])
	{
		point->color = (int)ft_atou_base(point_arr[COLOR], HEX_BASE, "0x");
		point->color = (point->color << 8) + 0xFF;
	}
	else
		point->color = DEFAULT_COLOR;
	if (point->z > m->max_z)
		m->max_z = point->z;
	if (point->z < m->min_z)
		m->min_z = point->z;
	new = exit_on_null(ft_lstnew(point), m);
	ft_lstadd_front(&(m->points), new);
}

static void	parse_line(char *line, int y, t_meta *m)
{
	int			i;

	m->line_arr = exit_on_null(ft_split(line, ' '), m);
	i = 0;
	while (m->line_arr[i] && m->line_arr[i][0] != '\n')
	{
		m->point_arr = exit_on_null(ft_split(m->line_arr[i], ','), m);
		if (!has_digits(m->point_arr[Z]))
			exit_error(ERROR_MAP_NUMBERS, m);
		add_point(m, i + 1, y, m->point_arr);
		free_array(m->point_arr);
		m->point_arr = NULL;
		i++;
	}
	free_array(m->line_arr);
	m->line_arr = NULL;
	if (m->drawing_w == 0)
		m->drawing_w = i;
	if (m->drawing_w != i)
		exit_error(ERROR_MAP_SQUARE, m);
}

void	spread_drawing(t_meta *m)
{
	t_list		*head;
	t_point		*point;
	float		coeff;

	coeff = 5 + (m->drawing_d / m->drawing_w);
	m44_scale(m->transformer, coeff, coeff, 1);
	m44_translate(m->transformer, -((m->drawing_w * coeff) / 2) - 1, \
									-((m->drawing_h * coeff) / 2) - 1, 0);
	head = m->points;
	while (head)
	{
		point = (t_point *)head->content;
		m44_multiply_point(m->transformer, point);
		head = head->next;
	}
	reset_cam(m);
}

void	parse_file(t_meta *m)
{
	int		fd;
	int		y;
	char	*line;

	y = 0;
	fd = open(m->filename, O_RDONLY);
	if (fd < 0)
		exit_error(ERROR_PATH, m);
	line = get_next_line(fd);
	while (line)
	{
		parse_line(line, y + 1, m);
		free(line);
		line = get_next_line(fd);
		y++;
	}
	close(fd);
	if (y == 0 || m->drawing_w == 0)
		exit_error(ERROR_MAP_CORRUPT, m);
	m->drawing_h = y;
	m->drawing_d = m->max_z - m->min_z;
	m->total_px = m->drawing_h * m->drawing_w;
	spread_drawing(m);
}
