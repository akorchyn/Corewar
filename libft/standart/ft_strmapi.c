/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:10 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:10 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		len;
	char	*ans;

	if (!s)
		return (NULL);
	i = -1;
	len = ft_strlen((char *)s);
	ans = (char *)malloc(len + 1);
	if (!ans)
		return (NULL);
	while (s[++i])
		ans[i] = f(i, s[i]);
	ans[i] = '\0';
	return (ans);
}
