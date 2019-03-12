/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 20:09:19 by dmlitvin          #+#    #+#             */
/*   Updated: 2019/01/30 17:33:28 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;

	return ((s1 && s2 && (out = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
			? (ft_strcat(ft_strcat(out, s1), s2)) : NULL);
}
