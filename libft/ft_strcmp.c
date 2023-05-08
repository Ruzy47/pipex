/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:45:13 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/07 11:13:24 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*s3;
	unsigned char	*s4;
	size_t			i;
    size_t          n;

	i = 0;
	s3 = (unsigned char *) s1;
	s4 = (unsigned char *) s2;
	if (!s1 || !s2)
		return (0);
	if (s3 == NULL && s4 == NULL)
		return (0);
    if (ft_strlen(s1) > ft_strlen(s2))
        n = ft_strlen(s1) - 1;
    else
        n = ft_strlen(s2) - 1;
	while (s3[i] && s4[i] && i < n && s3[i] == s4[i])
		i++;
	if (i < n || i == 0)
		return (1);
	else
		return (0);
}
