/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_other.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:40:43 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/08 20:52:05 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(t_pipex *pipex, char *str)
{
	char	*ptr;
	char	*join;
	int		i;

	i = -1;
	join = ft_strjoin("/", str);
	ptr = NULL;
	while (pipex->path[++i])
	{
		free(ptr);
		ptr = ft_strjoin(pipex->path[i], join);
		if (access(ptr, X_OK) == 0)
		{
			free(join);
			return (ptr);
		}
	}
	free(ptr);
	free(join);
	return (NULL);
}
