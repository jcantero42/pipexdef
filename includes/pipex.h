/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcantero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:29:04 by jcantero          #+#    #+#             */
/*   Updated: 2025/02/06 13:29:05 by jcantero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(const char *str, char c);
void	ft_free_split(char **strs);
void	ft_strncpy(char *word, char *str, int len);
int		ft_wordcount(char *str, int c);
char	*ft_stralloc(char *str, int c, int *k);
void	ft_free_split(char **strs);
void	first_child(int *pipe_fd, char **argv, char **envp);
void	second_child(int *pipe_fd, char **argv, char **envp);
void	exec_cmd(char *full_cmd, char **envp);
char	*get_path(char *cmd, char **envp);
void	print_error(const char *str);

#endif
