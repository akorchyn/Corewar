/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmlitvin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 15:07:47 by dmlitvin          #+#    #+#             */
/*   Updated: 2018/12/28 23:58:27 by dmlitvin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_del_listik(t_gnlist *to_delete, t_gnlist **begin_list)
{
	t_gnlist *tmp;

	tmp = *begin_list;
	if (to_delete == *begin_list)
	{
		*begin_list = (*begin_list)->next;
		ft_strdel(&(to_delete->ret_buf));
		free(to_delete);
		return (0);
	}
	while (tmp->next != to_delete)
		tmp = tmp->next;
	tmp->next = tmp->next->next;
	ft_strdel(&(to_delete->ret_buf));
	free(to_delete);
	return (0);
}

static void		ft_realloc(char **buf, char **ret_buf)
{
	char *new_buf;

	new_buf = ft_strcpy(ft_strnew(ft_strlen(*buf)
		+ ft_strlen(*ret_buf)), *ret_buf);
	new_buf = ft_strcat(new_buf, *buf);
	free(*ret_buf);
	*ret_buf = new_buf;
}

static int		ft_parse_line(char **line, t_gnlist *tmp)
{
	t_vars s;

	if (!ft_strchr(tmp->ret_buf, '\n'))
	{
		*line = ft_strcpy(ft_strnew(ft_strlen(tmp->ret_buf)), tmp->ret_buf);
		free(tmp->ret_buf);
		tmp->ret_buf = NULL;
		return (1);
	}
	s.i = ft_strchr(tmp->ret_buf, '\n') - tmp->ret_buf;
	*line = ft_strncpy(ft_strnew(s.i), tmp->ret_buf, s.i);
	s.new_buf = ft_strdup(tmp->ret_buf + (s.i + 1));
	free(tmp->ret_buf);
	tmp->ret_buf = s.new_buf;
	return (1);
}

static int		ft_reader(char **line, t_gnlist *tmp, t_gnlist **begin_list)
{
	t_vars s;

	if (!(tmp->ret_buf) || !(tmp->ret_buf[0]))
	{
		ft_strdel(&(tmp->ret_buf));
		tmp->ret_buf = ft_strnew(BUFF_SIZE);
		if (!(s.ret = read(tmp->fd, tmp->ret_buf, BUFF_SIZE)))
		{
			tmp->ret_buf[s.ret] = '\0';
			return (ft_del_listik(tmp, begin_list));
		}
	}
	s.buf = ft_strnew(BUFF_SIZE);
	while (!ft_strchr(tmp->ret_buf, '\n'))
	{
		s.ret = read(tmp->fd, s.buf, BUFF_SIZE);
		if (s.ret == -1)
			return (-1);
		if (!s.ret)
			break ;
		s.buf[s.ret] = '\0';
		ft_realloc(&s.buf, &(tmp->ret_buf));
	}
	ft_strdel(&s.buf);
	return (ft_parse_line(line, tmp));
}

int				get_next_line(const int fd, char **line)
{
	static t_gnlist	*list = NULL;
	t_gnlist		*tmp;

	if (!list)
	{
		if (!(list = (t_gnlist*)malloc(sizeof(t_gnlist))))
			return (-1);
		list->next = NULL;
		list->fd = fd;
		list->ret_buf = NULL;
	}
	tmp = list;
	while (tmp->fd != fd && tmp->next)
		tmp = tmp->next;
	if (tmp->fd != fd)
	{
		if (!(tmp->next = (t_gnlist*)malloc(sizeof(t_gnlist))))
			return (-1);
		tmp = tmp->next;
		tmp->fd = fd;
		tmp->next = NULL;
		tmp->ret_buf = NULL;
	}
	return (ft_reader(line, tmp, &list));
}
