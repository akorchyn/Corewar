/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kpshenyc <kpshenyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 09:49:17 by akorchyn          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/02/27 15:41:39 by kpshenyc         ###   ########.fr       */
=======
/*   Updated: 2019/02/27 16:05:42 by akorchyn         ###   ########.fr       */
>>>>>>> ead1d02ca79b7d1bfa9d37ca673f299020b82318
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int32_t					error(int code, char *msg, char *argument)
{
	ft_putstr_fd(msg, 2);
	if (argument)
	{
		ft_putstr_fd(" on argument:\n", 2);
		ft_putstr_fd(argument, 2);
	}
	ft_putstr_fd("\n", 2);
	exit(code);
	return (1);
}

void					put_bytes(uint32_t value, unsigned char *placement,
									int16_t position, int8_t bytes)
{
	while (bytes--)
	{
		placement[(position + bytes + MEM_SIZE) % MEM_SIZE] = value & 255;
		value >>= 8;
	}
}

/*
** Function translate from some bytes to one united number;
**
** EXAMPLE: 1th byte - ff 2nd byte - ff
** 			Result of work 65535 (0xffff)
*/

int32_t					bytes_to_dec(unsigned char const *str, int16_t position,
									int32_t bytes)
{
	int32_t			res;
	int32_t			i;
	int32_t			number;
	int8_t			sign;

	res = 0;
	sign = (str[position] & 0b10000000) ? 1 : 0;
	i = -1;
	while (++i < bytes)
	{
		number = str[(position + i + MEM_SIZE) % MEM_SIZE];
		(sign) ? number ^= 255 : 0;
		res <<= 8;
		res |= number;
	}
	if (sign)
		res = ~(res);
	return (res);
}

t_carriage				*extract_list(t_carriage **head, t_carriage *target)
{
	t_carriage		*prev;
	t_carriage		*tmp;

	tmp = (*head)->next;
	prev = *head;
	if (*head == target)
	{
		*head = (*head)->next;
		return (*head);
	}
	while (tmp)
	{
		if (tmp == target)
		{
			prev->next = tmp->next;
			return (*head);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (*head);
}

void					sort_list(t_carriage **head)
{
	t_carriage	*new_list;
	t_carriage	*tmp;
	int8_t		id;

	id = 1;
	tmp = *head;
	new_list = NULL;
	while (tmp)
	{
		if (id == tmp->id)
		{
			*head = extract_list(head, tmp);
			tmp->next = new_list;
			(new_list) ? new_list->prev = tmp : 0;
			tmp->prev = NULL;
			new_list = tmp;
			id++;
			tmp = *head;
		}
		else
			tmp = tmp->next;
	}
	*head = new_list;
}
