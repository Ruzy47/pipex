/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:17:42 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/08 22:48:21 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	child(t_pipex *pipex, int fd, char **envp)
{
	pipex->str = ft_split(pipex->pargv[pipex->y], ' ');
	if (fd == 0)
	{
		if (dup2(pipex->a, 0) == -1 || dup2(pipex->fd[fd][1], 1) == -1)
			ft_perror("Ruzik_ERROR");
	}
	else if (fd == pipex->i - 1)
	{
		if (dup2(pipex->fd[fd - 1][0], 0) == -1 || dup2(pipex->b, 1) == -1)
			ft_perror("Ruzik_ERROR");
	}
	else
	{
		if (dup2(pipex->fd[fd - 1][0], 0) == -1
			|| dup2(pipex->fd[fd][1], 1) == -1)
			ft_perror("Ruzik_ERROR");
	}
	ft_exac(pipex, envp);
}

void	child2(t_pipex *pipex, int n, char **envp)
{
	char	**str;

	str = ft_split(pipex->pargv[n], ' ');
	if (dup2(pipex->pfd[0], 0) == -1 || dup2(pipex->b, 1) == -1)
	{
		if (pipex->pfd[0])
			close(pipex->pfd[0]);
		if (pipex->pfd[1])
			close(pipex->pfd[1]);
		ft_perror("Ruzik_ERROR");
	}
	if (ft_strchr(str[0], '/'))
		;
	else
		str[0] = get_cmd(pipex, str[0]);
	close(pipex->pfd[0]);
	close(pipex->pfd[1]);
	if (execve(str[0], str, envp) == -1)
		ft_perror("Ruzik_ERROR");
	exit(1);
}

void	ft_fork(t_pipex *pipex, int n, char **envp)
{
	int	x;

	if (pipex->a == -1 && pipex->b > -1)
	{
		pipex->pid2 = fork();
		if (pipe(pipex->pfd) == -1 || pipex->pid2 == -1)
			ft_perror("Ruzik_ERROR");
		if (pipex->pid2 == 0)
			child2(pipex, n, envp);
	}
	else 
	{
		x = -1;
		while (++x != pipex->i)
		{
			pipex->pid = fork();
			if (pipex->pid == -1)
				ft_perror("Ruzik_ERROR");
			if (pipex->pid == 0)
				child(pipex, x, envp);
			pipex->y = pipex->y + 1;
		}
	}
}

void	main2(t_pipex *pipex, int argc, char **argv, int x)
{
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		pipex->i = argc - 4;
		pipex->y = 3;
	}
	else
	{
		pipex->i = argc - 3;
		pipex->y = 2;
	}
	pipex->fd = (int **)malloc(sizeof(int *) * pipex->i);
	if (!pipex->fd)
		ft_perror("Ruzik_ERROR");
	while (++x != pipex->i)
	{
		pipex->fd[x] = (int *)malloc(sizeof(int) * 2);
		if (!pipex->fd[x])
			ft_perror("Ruzik_ERROR");
		if (pipe(pipex->fd[x]) == -1)
			ft_perror("Ruzik_ERROR");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;

	if (argc < 5)
		ft_perror("Ruzik_ERROR");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		file_a(&pipex, argv);
	else
		pipex.a = open(argv[1], O_RDONLY);
	if (pipex.a > -1)
		main2(&pipex, argc, argv, -1);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		pipex.b = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex.b = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((pipex.a == -1 && pipex.b > -1 && argv[argc - 2][0] != 'l'
		&& argv[argc - 2][1] != 's') || pipex.b == -1)
		ft_perror("Ruzik_ERROR");
	pipex.path = get_path(envp);
	pipex.pargv = argv;
	ft_fork(&pipex, argc - 2, envp);
	ft_close(&pipex);
	while (wait(NULL) != -1)
		;
	return (0);
}
