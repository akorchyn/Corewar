/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:17:50 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:17:50 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ans;
	int		k;
	int		i;

	i = -1;
	if (!s1 || !s2)
		return (NULL);
	k = ft_strlen((char *)s1) + ft_strlen((char *)s2) - 1;
	if (s1[0] == '\0' && s2[0] == '\0')
		k = 1;
	ans = (char *)malloc(k);
	if (!ans)
		return (NULL);
	while (s1[++i])
		ans[i] = ((char *)s1)[i];
	k = -1;
	while (s2[++k])
		ans[i++] = ((char *)s2)[k];
	ans[i] = '\0';
	return (ans);
}
