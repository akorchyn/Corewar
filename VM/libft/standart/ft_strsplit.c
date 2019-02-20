/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorchyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:18:57 by akorchyn          #+#    #+#             */
/*   Updated: 2019/02/09 16:18:57 by akorchyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	words(char *s, char c)
{
	int i;
	int count;

	i = -1;
	count = 0;
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[++i] != '\0')
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
	return (count);
}

char		**ft_strsplit(char const *s, char c)
{
	int		i;
	int		len_word;
	int		ans_c;
	char	**ans;

	if (!s)
		return (NULL);
	i = -1;
	ans_c = 0;
	if (!(ans = (char **)malloc((words((char *)s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (s[++i])
	{
		len_word = 0;
		if (s[i] != c)
		{
			while ((s[i] != c && s[i]) && len_word++ >= 0)
				i++;
			ans[ans_c++] = ft_strsub(s, i - len_word, len_word);
		}
		if (s[i] == '\0')
			i--;
	}
	ans[ans_c] = NULL;
	return (ans);
}
