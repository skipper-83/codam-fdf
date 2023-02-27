/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 10:44:37 by albertvanan       #+#    #+#             */
/*   Updated: 2023/02/27 21:27:47 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

void	free_strings_list(t_list **list, t_meta *m)
{
	t_list	*head;
	t_list	*next;

	head = *list;
	while (head)
	{
		next = head->next;
		mlx_delete_image(m->mlx, (mlx_image_t *)head->content);
		free (head);
		head = next;
	}
	*list = NULL;
}

void	free_meta(t_meta *m)
{
	if (m == NULL)
		return ;
	if (m->world)
		m44_free(m->world);
	if (m->camera)
		m44_free(m->camera);
	if (m->transformer)
		m44_free(m->transformer);
	if (m->line_arr)
	{
		free_array(m->line_arr);
		m->line_arr = NULL;
	}
	if (m->point_arr)
	{
		free_array(m->point_arr);
		m->point_arr = NULL;
	}
	free_strings_list(&m->strings, m);
	ft_lstclear(&(m->points), free);
	free(m);
}

void	exit_error(char *error_msg, t_meta *m)
{
	free_meta(m);
	ft_putendl_fd(error_msg, 2);
	exit (1);
}

void	*exit_on_null(void *ptr, t_meta *m)
{
	if (ptr == NULL)
		exit_error(ERROR_MEM, m);
	return (ptr);
}
