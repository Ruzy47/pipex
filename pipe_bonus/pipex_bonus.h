/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rugrigor <rugrigor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:15:53 by rugrigor          #+#    #+#             */
/*   Updated: 2023/05/08 22:41:41 by rugrigor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_pipex
{
	pid_t	pid;
	pid_t	pid2;
	int		a;
	int		b;
	int		i;
	int		y;
	int		pfd[2];
	int		**fd;
	char	*here;
	char	**str;
	char	**pargv;
	char	**arg1;
	char	**arg2;
	char	**path;
}				t_pipex;

char		**get_path(char **envp);
char		*get_cmd(t_pipex *pipex, char *str);
void		main2(t_pipex *pipex, int argc, char **argv, int x);
void		ft_fork(t_pipex *pipex, int n, char **envp);
void		ft_exac(t_pipex *pipex, char **envp);
void		child(t_pipex *pipex, int fd, char **envp);
void		child2(t_pipex *pipex, int n, char **envp);
void		ft_close(t_pipex *pipex);
void		file_a(t_pipex *pipex, char **argv);
char		*get_next_line(int fd);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *str);
char		*ft_strchr(char *str, int n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*strn(char *ptr);
char		*strn2(char *ptr);
char		*ft_strdup(const char *str);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

#endif