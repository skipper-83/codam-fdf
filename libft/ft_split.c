/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:07:48 by avan-and          #+#    #+#             */
/*   Updated: 2023/02/11 20:54:54 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_items(char const *s, char c);
static char		**free_stuff(char **stuff);
static char		**store_strs(char **s_arr, const char *s, char c, size_t amnt);

/**
 * @brief split string s into array of strings, with char c as delimiter
 * 
 * @param s 
 * @param c 
 * @return char** 
 */
char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	amount;

	if (!s)
		return (NULL);
	amount = count_items(s, c);
	res = (char **)ft_calloc(sizeof(char *), amount + 1);
	if (!res)
		return (NULL);
	res = store_strs(res, s, c, amount);
	return (res);
}

/**
 * @brief	write amount strings to string array s_arr
 * 			with s as source and c as delimiter
 * 
 * @param s_arr 
 * @param s 
 * @param c 
 * @param amnt 
 * @return char** 
 */
static char	**store_strs(char **s_arr, const char *s, char c, size_t amnt)
{
	size_t	start;
	size_t	end;
	size_t	i;

	start = 0;
	i = 0;
	while (i < amnt)
	{
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		s_arr[i] = ft_substr(s, start, end - start);
		if (!s_arr[i])
			return (free_stuff(s_arr));
		start = end;
		i++;
	}
	return (s_arr);
}

/**
 * @brief	free content being worked on in case of error
 * 
 * @param stuff 
 * @return char** 
 */
static char	**free_stuff(char **stuff)
{
	size_t	i;

	i = 0;
	while (stuff[i])
		free(stuff[i++]);
	free(stuff);
	return (NULL);
}

/**
 * @brief 	count how many strings delimited by c ar in 
 * 			input sting s
 * 
 * @param s 
 * @param c 
 * @return size_t 
 */
static size_t	count_items(char const *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s == c)
		{
			while (*s == c && *s)
				s++;
		}
		else
		{
			ret++;
			while (*s != c && *s)
				s++;
		}
	}
	return (ret);
}



// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ft_strsplit.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: vbrazhni <marvin@42.fr>                    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2018/07/02 19:09:23 by vbrazhni          #+#    #+#             */
// /*   Updated: 2018/07/02 19:09:24 by vbrazhni         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "libft.h"
// #include <stdlib.h>

// static size_t	ft_count_words(char const *s, char c)
// {
// 	size_t words;

// 	words = 0;
// 	while (*s)
// 	{
// 		while (*s == c)
// 			s++;
// 		if (*s)
// 		{
// 			words++;
// 			while (*s && *s != c)
// 				s++;
// 		}
// 	}
// 	return (words);
// }

// static char		*ft_get_word(char *word, char c)
// {
// 	char *start;

// 	start = word;
// 	while (*word && *word != c)
// 		word++;
// 	*word = '\0';
// 	return (ft_strdup(start));
// }

// void	ft_strdel(char **as)
// {
// 	if (as && *as)
// 	{
// 		free(*as);
// 		*as = NULL;
// 	}
// }

// static void		ft_free_words(char **words, size_t i)
// {
// 	while (i--)
// 		ft_strdel(&(words[i]));
// 	free(*words);
// }

// static char		**ft_get_words(char *s, char c, size_t words_count)
// {
// 	char	**words;
// 	char	*word;
// 	size_t	i;

// 	i = 0;
// 	if ((words = (char **)ft_calloc((words_count + 1), sizeof(char *))))
// 	{
// 		while (i < words_count)
// 		{
// 			while (*s == c)
// 				s++;
// 			if (*s)
// 			{
// 				if (!(word = ft_get_word(s, c)))
// 				{
// 					ft_free_words(words, i);
// 					return (NULL);
// 				}
// 				words[i++] = word;
// 				s += (ft_strlen(word) + 1);
// 			}
// 		}
// 		words[i] = NULL;
// 	}
// 	return (words);
// }

// char			**ft_split(char const *s, char c)
// {
// 	char	**words;
// 	char	*line;

// 	if (!s || !(line = ft_strdup((char *)s)))
// 		return (NULL);
// 	words = ft_get_words(line, c, ft_count_words(line, c));
// 	free(line);
// 	return (words);
// }
