/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_other_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:19:03 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/08 22:53:32 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_exac(t_pipex *pipex, char **envp)
{
	if (!ft_strchr(pipex->str[0], '/'))
		pipex->str[0] = get_cmd(pipex, pipex->str[0]);
	ft_close(pipex);
	if (execve(pipex->str[0], pipex->str, envp) == -1)
		ft_perror("Ruzik_ERROR");
	exit(1);
}

void	file_a(t_pipex *pipex, char **argv)
{
	int		fd;
	char	*here;

	here = NULL;
	fd = open("here", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_perror("Ruzik_ERROR");
	while (1)
	{
		write(1, "here_doc>", 9);
		here = get_next_line(0);
		if (ft_strcmp(here, argv[2]) == 0)
			break ;
		write(fd, here, ft_strlen(here));
		free(here);
	}
	free(here);
	close(fd);
	pipex->a = open("here", O_RDONLY);
	unlink("here");
}

void	ft_close(t_pipex *pipex)
{
	int	n;

	if (pipex->a < 0)
	{
		close(pipex->pfd[0]);
		close(pipex->pfd[1]);
	}
	else
	{
		n = -1;
		while (++n != pipex->i)
		{
			close(pipex->fd[n][0]);
			close(pipex->fd[n][1]);
			free(pipex->fd[n]);
		}
		free(pipex->fd);
	}
}

char	*get_cmd(t_pipex *pipex, char *str)
{
	char	*here;
	char	*join;
	int		i;

	i = -1;
	join = ft_strjoin("/", str);
	here = NULL;
	while (pipex->path[++i])
	{
		free(here);
		here = ft_strjoin(pipex->path[i], join);
		if (access(here, X_OK) == 0)
		{
			free(join);
			return (here);
		}
	}
	free(here);
	free(join);
	return (NULL);
}

char	**get_path(char **envp)
{
	char		**str;
	int			i;
	const char	*here;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
	here = envp[i] + 5;
	str = ft_split(here, ':');
	return (str);
}
