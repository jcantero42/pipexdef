/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcantero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:24:01 by jcantero          #+#    #+#             */
/*   Updated: 2025/02/06 13:24:02 by jcantero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	print_error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*temp;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		++i;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path, F_OK | X_OK) == 0)
		{
			ft_free_split(paths);
			return (path);
		}
		free(path);
	}
	return (ft_free_split(paths), NULL);
}

void	exec_cmd(char *full_cmd, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(full_cmd, ' ');
	if (cmd[0] == NULL)
	{
		ft_free_split(cmd);
		print_error("Error with command");
	}
	else if ((cmd[0][0] == '/' || cmd[0][0] == '.'))
		path = cmd[0];
	else
		path = get_path(cmd[0], envp);
	if (path == NULL)
	{
		ft_free_split(cmd);
		print_error("Error finding path");
	}
	if (execve(path, cmd, envp) == -1)
	{
		if (path != cmd[0])
			free(path);
		ft_free_split(cmd);
		print_error("Error with command");
	}
}

void	close_pipes(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (argc != 5)
	{
		write (2, "ERROR: Invalid arguments\n", 19);
		exit(1);
	}
	if (pipe(fd) == -1)
		print_error("Error with pipe");
	pid1 = fork();
	if (pid1 == -1)
		print_error("Error with fork");
	if (pid1 == 0)
		first_child(fd, argv, envp);
	pid2 = fork();
	if (pid2 == -1)
		print_error("Error with fork");
	if (pid2 == 0)
		second_child(fd, argv, envp);
	close_pipes(fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
