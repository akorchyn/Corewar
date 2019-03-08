/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 18:16:55 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/10/30 23:33:29 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	ft_nblen(int n)
{
	size_t out;

	out = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		out++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		out++;
	}
	return (out);
}

static char		*ft_min(int n)
{
	char	*out;
	char	*str;
	size_t	i;

	i = 0;
	if (n == -2147483648)
	{
		out = (char*)malloc(12);
		str = "-2147483648";
		if (!out)
			return (str);
		while (str[i])
		{
			out[i] = str[i];
			i++;
		}
	}
	if (!n)
	{
		out = (char*)malloc(2);
		out[i] = 48;
		i++;
	}
	out[i] = '\0';
	return (out);
}

char			*ft_itoa(int n)
{
	char	*out;
	size_t	i;

	if (n == -2147483648 || !n)
		return (ft_min(n));
	i = ft_nblen(n) - 1;
	out = (char*)malloc(i + 2);
	if (!out)
		return (NULL);
	if (n < 0)
	{
		out[0] = '-';
		n *= -1;
	}
	out[i + 1] = '\0';
	while (n)
	{
		out[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	return (out);
}
