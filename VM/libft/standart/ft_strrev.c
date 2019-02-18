/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:53 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:53 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *string)
{
	int		start;
	int		end;
	char	temp;

	end = ft_strlen(string) - 1;
	start = 0;
	while (start < end)
	{
		temp = string[end];
		string[end--] = string[start];
		string[start++] = temp;
	}
	return (string);
}
