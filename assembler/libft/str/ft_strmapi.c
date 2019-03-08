/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 17:56:20 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/26 21:09:02 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	char			*out;
	unsigned int	i;

	i = 0;
	if (s && f && (out = ft_strnew(ft_strlen(s))))
	{
		while (s[i])
		{
			out[i] = f(i, s[i]);
			i++;
		}
		return (out);
	}
	return (NULL);
}
