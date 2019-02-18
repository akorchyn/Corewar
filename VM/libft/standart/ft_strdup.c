/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:17:31 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:17:31 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ans;
	int		i;

	i = 0;
	ans = (char *)malloc(ft_strlen(src) + 1);
	if (!ans)
		return (NULL);
	while (src[i] != '\0')
	{
		ans[i] = ((char *)src)[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
