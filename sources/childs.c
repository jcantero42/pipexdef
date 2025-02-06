/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcantero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 12:58:39 by jcantero          #+#    #+#             */
/*   Updated: 2025/02/06 12:58:41 by jcantero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	first_child(int *pipe_fd, char **argv, char **envp)
{
	int	read_file;

	read_file = open(argv[1], O_RDONLY, 0644);
	if (read_file == -1)
		print_error("Error opening file");
	close(pipe_fd[0]);
	dup2(read_file, STDIN_FILENO);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	close(read_file);
	exec_cmd(argv[2], envp);
}

void	second_child(int *pipe_fd, char **argv, char **envp)
{
	int	res_file;

	res_file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (res_file == -1)
		print_error("Error opening file");
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(res_file, STDOUT_FILENO);
	close(pipe_fd[0]);
	close(res_file);
	exec_cmd(argv[3], envp);
}
