/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   useful_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 09:49:17 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/21 22:16:20 by akorchyn         ###   ########.fr       */
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
									int8_t bytes)
{
	while (bytes--)
	{
		placement[bytes] = value & 255;
		value >>= 8;
	}
}

/*
** Function translate from some bytes to one united number;
**
** EXAMPLE: 1th byte - ff 2nd byte - ff
** 			Result of work 65535 (0xffff)
*/

int32_t					bytes_to_dec(unsigned char const *str,
									int32_t bytes)
{
	uint32_t		res;
	int32_t			i;
	int32_t			number;

	res = 0;
	i = -1;
	while (++i < bytes)
	{
		number = str[i];
		res <<= 8;
		res |= number;
	}
	return (res);
}

t_carriage				*extract_list(t_carriage **head, t_carriage *target)
{
	t_carriage		*prev;
	t_carriage		*tmp;

	tmp = *head;
	prev = NULL;
	if (*head == target)
	{
		*head = (*head)->next;
		return (*head);
	}
	while (tmp)
	{
		if (tmp == target)
		{
			if (prev)
				prev->next = tmp->next;
			return (*head);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (*head);
}

void					sort_list(t_carriage **head, t_corewar *corewar)
{
	t_carriage	*new_list;
	t_carriage	*tmp;
	int8_t		id;

	id = corewar->players_count;
	tmp = *head;
	new_list = NULL;
	while (tmp)
	{
		if (id == tmp->id)
		{
			*head = extract_list(head, tmp);
			tmp->next = new_list;
			new_list = tmp;
			id--;
			tmp = *head;
		}
		else
			tmp = tmp->next;
	}
	*head = new_list;
}
