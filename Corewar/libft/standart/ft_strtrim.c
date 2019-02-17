/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:19:14 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:19:14 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		len;
	char	*ans;
	int		start;
	int		end;
	int		memory;

	if (!s)
		return (NULL);
	start = 0;
	len = ft_strlen((char *)s);
	end = len - 1;
	while (s[start] == ' ' || s[start] == '\t' || s[start] == '\n')
		start++;
	while (s[end] == ' ' || s[end] == '\t' || s[end] == '\n')
		end--;
	memory = end - start + 2;
	if (start == len)
		memory = 1;
	ans = (char *)malloc(memory);
	if (!ans)
		return (NULL);
	ft_strncpy(ans, (char *)s + start, memory - 1);
	ans[memory - 1] = '\0';
	return (ans);
}
