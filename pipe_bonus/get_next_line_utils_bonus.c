/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:42:26 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/07 10:51:20 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	char	*s1;
	size_t	n;

	n = 0;
	s1 = (char *) s;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	if (len == 0 || ft_strlen(s1) < len || ft_strlen(s1) < start)
	{
		ptr[n] = '\0';
		return (ptr);
	}
	while (s1 && n < len)
		ptr[n++] = s1[start++];
	ptr[n] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	a;
	size_t	b;
	size_t	i;
	size_t	n;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	i = 0;
	n = 0;
	ptr = (char *)malloc(sizeof(char) * (a + b + 1));
	if (s1 == 0 || s2 == 0 || ptr == 0)
		return (0);
	while (i < a)
		ptr[n++] = s1[i++];
	i = 0;
	while (i < b)
		ptr[n++] = s2[i++];
	ptr[n] = '\0';
	return (ptr);
}

char	*ft_strchr(char *str, int n)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if ((char)n == '\0')
		return (&str[ft_strlen(str)]);
	while (str[i] != '\0')
	{
		if (str[i] == (char)n)
			return (&str[i]);
		i++;
	}
	return (0);
}

char	*ft_strdup(const char *str)
{
	char	*p;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	p = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!p)
		return (NULL);
	while (str[i])
	{
		p[i] = str[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
