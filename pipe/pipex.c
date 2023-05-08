/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:53:17 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/09 00:04:31 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char		**str;
	int			i;
	const char	*ptr;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			break ;
	ptr = envp[i] + 5;
	str = ft_split(ptr, ':');
	return (str);
}

void	child1(t_pipex *pipex, char **argv, char **envp)
{
	char	**str;

	str = ft_split(argv[2], ' ');
	if (dup2(pipex->a, 0) == -1 || dup2(pipex->fd[1], 1) == -1)
	{
		if (pipex->fd[0])
			close(pipex->fd[0]);
		if (pipex->fd[1])
			close(pipex->fd[1]);
		ft_perror("Ruzik_ERROR");
	}
	if (!ft_strchr(str[0], '/'))
		str[0] = get_cmd(pipex, str[0]);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (execve(str[0], str, envp) == -1)
		ft_perror("Ruzik_ERROR");
	exit(1);
}

void	child2(t_pipex *pipex, char **argv, char **envp)
{
	char	**str;

	str = ft_split(argv[3], ' ');
	if (dup2(pipex->fd[0], 0) == -1 || dup2(pipex->b, 1) == -1)
	{
		if (pipex->fd[0])
			close(pipex->fd[0]);
		if (pipex->fd[1])
			close(pipex->fd[1]);
		ft_perror("Ruzik_ERROR");
	}
	if (ft_strchr(str[0], '/'))
		;
	else
		str[0] = get_cmd(pipex, str[0]);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (execve(str[0], str, envp) == -1)
		ft_perror("Ruzik_ERROR");
	exit(1);
}

void	main2(t_pipex *pipex, char **argv, char **envp)
{
	if (pipex->a == -1 && pipex->b > -1)
		;
	else
	{
		pipex->pid1 = fork();
		if (pipex->pid1 == -1)
			ft_perror("Ruzik_ERROR");
		if (pipex->pid1 == 0)
			child1(pipex, argv, envp);
	}
		pipex->pid2 = fork();
		if (pipex->pid2 == -1)
			ft_perror("Ruzik_ERROR");
		if (pipex->pid2 == 0)
			child2(pipex, argv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_perror("Ruzik_ERROR");
	pipex.a = open(argv[1], O_RDONLY);
	pipex.b = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex.b == -1 || pipe(pipex.fd) == -1)
		ft_perror("Ruzik_ERROR");
	pipex.path = get_path(envp);
	main2(&pipex, argv, envp);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	while (wait(NULL) != -1)
		;
	return (0);
}
