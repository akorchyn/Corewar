/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freesplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:13:28 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:13:28 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freesplit(char **src)
{
	int	i;

	i = -1;
	if (!src || !*src)
		return ;
	while (src[++i])
		free(src[i]);
	free(src);
	src = NULL;
}
