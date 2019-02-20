/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:19:09 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:19:09 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s1;

	if (!s)
		return (NULL);
	s1 = (char *)malloc(len + 1);
	if (!s1)
		return (NULL);
	ft_strncpy(s1, s + start, len);
	s1[len] = '\0';
	return (s1);
}
