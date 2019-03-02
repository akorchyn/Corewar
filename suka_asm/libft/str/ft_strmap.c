/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:35:32 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/26 21:08:36 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*out;

	i = 0;
	if (s && f && (out = (char*)ft_strnew(ft_strlen(s))))
	{
		while (s[i])
		{
			out[i] = f(s[i]);
			i++;
		}
		return (out);
	}
	return (NULL);
}
