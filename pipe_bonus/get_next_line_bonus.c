/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:59:44 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/08 18:35:30 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*strn(char *ptr)
{
	int		i;
	char	*p;

	i = 0;
	while (ptr && ptr[i] && ptr[i] != '\n')
		i++;
	p = ft_substr(ptr, 0, i + 1);
	return (p);
}

char	*strn2(char *ptr)
{
	int		i;
	char	*p;

	i = 0;
	while (ptr && ptr[i] && ptr[i] != '\n')
		i++;
	p = ft_substr(ptr, i + 1, ft_strlen(ptr) - i + 1);
	free(ptr);
	ptr = ft_strdup(p);
	free(p);
	p = (NULL);
	return (ptr);
}

static char	*go_go(char *buff, int fd, char *str)
{
	int		i;
	char	*p;

	if (ft_strchr(str, '\n'))
		return (str);
	i = read(fd, buff, BUFFER_SIZE);
	while (i > 0)
	{
		buff[i] = '\0';
		if (!str)
			str = ft_strdup("");
		p = ft_strdup(str);
		free(str);
		str = ft_strjoin(p, buff);
		free(p);
		p = (NULL);
		if (ft_strchr(str, '\n'))
			break ;
		i = read(fd, buff, BUFFER_SIZE);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*ptr;
	char		*buff;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	str[fd] = go_go(buff, fd, str[fd]);
	ptr = strn(str[fd]);
	free(buff);
	buff = NULL;
	if (!str[fd])
		return (NULL);
	str[fd] = strn2(str[fd]);
	if (*ptr == 0)
	{
		free(str[fd]);
		str[fd] = (NULL);
		free(ptr);
		ptr = (NULL);
		return (NULL);
	}
	return (ptr);
}
