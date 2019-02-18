/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:06 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:06 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ans;
	int		len_s;
	int		i;

	i = -1;
	if (!s)
		return (NULL);
	len_s = ft_strlen((char *)s);
	ans = (char *)malloc(len_s + 1);
	if (!ans)
		return (NULL);
	while (s[++i])
		ans[i] = f(s[i]);
	ans[i] = '\0';
	return (ans);
}
