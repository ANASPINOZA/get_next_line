/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aadnane <aadnane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:48:22 by aadnane           #+#    #+#             */
/*   Updated: 2022/03/24 19:10:09 by aadnane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*makeline(char *buf, char **s)
{
	char	*ptr;

	ptr = ft_strdupi(buf, ft_linelen(buf));
	if (!ptr)
		return (NULL);
	if (ft_strlen(ptr) < ft_strlen(buf))
		*s = ft_strdup(ft_strchr(buf, '\n') + 1);
	return (ptr);
}

char	*ft_checkline(int fd, char *buf, int n, char **s)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!tmp)
		return (NULL);
	while (ft_strchr(buf, '\n') == NULL && n > 0)
	{
		n = read(fd, tmp, BUFFER_SIZE);
		tmp[n] = '\0';
		buf = ft_strjoin(buf, tmp);
		if (!buf)
			return (NULL);
	}
	free (tmp);
	if (*s != NULL)
	{
		tmp = buf;
		buf = ft_strjoin(*s, buf);
		if (!buf)
			return (NULL);
		*s = NULL;
		free (tmp);
	}
	return (buf);
}

char	*ft_strdupi(char *str, int len)
{
	char	*ptr;

	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ptr[len] = '\0';
	while (len)
	{
		len--;
		ptr[len] = str[len];
	}
	return (ptr);
}

int	ft_linelen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	int				n;
	static char		*s;
	char			*buf;
	char			*line;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	n = 1;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	n = read(fd, buf, BUFFER_SIZE);
	if (n < 0 || (s == NULL && n == 0))
	{
		free(buf);
		return (NULL);
	}
	buf[n] = '\0';
	buf = ft_checkline (fd, buf, n, &s);
	if (!buf)
		return (NULL);
	line = makeline(buf, &s);
	free(buf);
	return (line);
}
