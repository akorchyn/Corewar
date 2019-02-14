/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:45 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:45 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int i;
	int safe_position;

	safe_position = -1;
	i = -1;
	while (str[++i] != '\0')
		if (str[i] == c)
			safe_position = i;
	if (str[i] == c)
		safe_position = i;
	if (safe_position == -1)
		return (NULL);
	return ((char *)str + safe_position);
}
