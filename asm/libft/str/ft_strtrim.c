/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 22:57:40 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/28 15:17:18 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*out;
	size_t	from_right;
	size_t	from_left;

	if (s)
	{
		from_left = 0;
		while (s[from_left] == ' ' || s[from_left] == '\t'
			|| s[from_left] == '\n')
			from_left++;
		from_right = ft_strlen(s);
		while (from_right != from_left && (s[from_right - 1] == ' '
			|| s[from_right - 1] == '\t' || s[from_right - 1] == '\n'))
			from_right--;
		out = ft_strnew(from_right - from_left);
		return (out) ?
		ft_memcpy(out, s + from_left, from_right - from_left) : out;
	}
	return (NULL);
}
