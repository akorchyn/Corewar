/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:14:12 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:14:12 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isxdigit(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 70) || (c >= 97 && c <= 102))
		return (1);
	return (0);
}