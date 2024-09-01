/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ofilloux <ofilloux@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 09:43:17 by ofilloux          #+#    #+#             */
/*   Updated: 2024/08/31 12:11:23 by ofilloux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		i;

	if (!s1 && s1[0] == '\0')
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
		i++;
	cpy = malloc ((i + 1) * sizeof (char));
	if (!cpy)
		return (NULL);
	cpy[i--] = '\0';
	while (i >= 0)
	{
		cpy[i] = s1[i];
		i--;
	}
	return (cpy);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	int		t;
	char	*nw;

	l1 = (int)ft_strlen(s1);
	l2 = (int)ft_strlen(s2);
	nw = malloc((l1 + l2 + 1) * sizeof(char));
	if (!nw)
		return (NULL);
	t = 0;
	while (t <= l1 - 1)
	{
		nw[t] = s1[t];
		t++;
	}
	while (t <= l1 + l2 - 1)
	{
		nw[t] = s2[t - l1];
		t++;
	}
	nw[t] = '\0';
	return (nw);
}

bool	fill_content(t_file *file)
{
	char	buf[BUF_SIZE + 1];
	char	*tmp;
	int		flag;

	flag = 1;
	while (flag > 0)
	{
		flag = read(file->fd, buf, BUF_SIZE);
		buf[flag] = '\0';
		if (flag > 0)
			tmp = ft_strjoin(file->content, buf);
		if (flag > 0 && file->content != NULL)
			free(file->content);
		file->content = tmp;
	}
	if (flag == -1)
		return (false);
	return (true);
}
