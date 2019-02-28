/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/28 11:44:14 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/11/01 12:35:34 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_maker(char const *s, char c)
{
	size_t	words;
	char	**out;

	words = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		words++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	out = (char**)malloc(sizeof(char*) * (words + 1));
	if (!out)
		return (NULL);
	out[words] = NULL;
	return (out);
}

static char	**filler(char const *s, char c, char **out)
{
	size_t len;
	size_t i;

	i = 0;
	len = 0;
	while (*s == c && *s)
		s++;
	while (*s)
	{
		while (*s != c && *s)
		{
			len++;
			s++;
		}
		out[i] = ft_strsub(s - len, 0, len);
		i++;
		len = 0;
		while (*s && *s == c)
			s++;
	}
	return (out);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**out;

	if (!s)
		return ((char**)s);
	out = ft_maker(s, c);
	if (!out)
		return (out);
	return (filler(s, c, out));
}
