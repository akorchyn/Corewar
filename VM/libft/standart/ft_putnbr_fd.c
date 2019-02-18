/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:16:40 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:16:40 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < -9 || n > 9)
		ft_putnbr_fd(n / 10, fd);
	if (n < 0)
	{
		if (n > -10 && n < 0)
			ft_putchar_fd('-', fd);
		ft_putnbr_fd(0 - n % 10, fd);
	}
	else
		ft_putchar_fd(n % 10 + '0', fd);
}
