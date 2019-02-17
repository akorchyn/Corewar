/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:19:36 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:19:36 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delete_list(t_list *head, t_list *to_delete)
{
	t_list *prev;

	prev = head;
	if (head == to_delete)
	{
		head = head->next;
		free(to_delete->content);
		free(to_delete);
		to_delete = NULL;
		return ;
	}
	while (prev->next != to_delete)
		prev = prev->next;
	prev->next = to_delete->next;
	free(to_delete->content);
	free(to_delete);
	to_delete = NULL;
}

int		reading(int fd, t_list *buff)
{
	char	c[BUFF_SIZE + 1];
	int		i;
	char	*temp;

	while ((i = read(fd, c, BUFF_SIZE)) > 0)
	{
		c[i] = '\0';
		i += ft_strlen(buff->content);
		if (!(temp = ft_strnew(i)))
			return (-1);
		temp = ft_strcpy(temp, buff->content);
		temp = ft_strcat(temp, c);
		free(buff->content);
		buff->content = temp;
		if ((ft_strchr(c, '\n')))
			break ;
	}
	return (i);
}

int		getting(int fd, char **line, t_list *buff)
{
	char	*temp;
	int		i;

	if ((i = reading(fd, buff)) == -1)
		return (-1);
	if (!((char *)buff->content)[0])
		return (0);
	if ((temp = ft_strchr(buff->content, '\n')))
	{
		i = temp - ((char *)buff->content);
		*line = ft_strnew(i);
		*line = ft_strncpy(*line, buff->content, i);
		temp = ft_strdup(temp + 1);
		free(buff->content);
		buff->content = temp;
		return (1);
	}
	*line = ft_strdup(buff->content);
	free(buff->content);
	buff->content = ft_strnew(1);
	return (1);
}

/*
** Bus error while fd > 24657. As i understund becouse fd is limited.
*/

int		get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*run;
	int				answ;

	if (fd < 0 || !line || BUFF_SIZE < 0 || fd > 24657)
		return (-1);
	if (!head)
		head = ft_lstnew("", fd);
	run = head;
	while (run && run->next && (int)run->content_size != fd)
		run = run->next;
	if ((int)run->content_size != fd)
	{
		run->next = ft_lstnew("", fd);
		run = run->next;
	}
	answ = getting(fd, line, run);
	if (answ == -1)
		return (-1);
	else if (answ == 0)
	{
		ft_delete_list(head, run);
		return (0);
	}
	return (1);
}
