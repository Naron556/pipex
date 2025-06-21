/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:33:04 by aoperacz          #+#    #+#             */
/*   Updated: 2025/06/21 16:55:48 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	lay_in_n_out(int pipe_fds[2], int file_fd, int i_o)
{
	if (i_o == 0)
	{
		dup2(file_fd, STDIN_FILENO);
		dup2(pipe_fds[1], STDOUT_FILENO);
	}
	else
	{
		dup2(file_fd, STDOUT_FILENO);
		dup2(pipe_fds[0], STDIN_FILENO);
	}
	close(file_fd);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
}

int	child(char **argv, int pipe_fds[2], int i_o, char **envp)
{
	char	**args;
	char	*cmd_path;
	int		file_fd;

	args = set_args(argv, &file_fd, i_o);
	if (args == NULL || file_fd <= 0)
	{
		close_fds(file_fd, pipe_fds);
		exit(1);
	}
	cmd_path = NULL;
	cmd_path = get_path(args[0], envp);
	if (cmd_path == NULL)
	{
		free_tab(args);
		close_fds(file_fd, pipe_fds);
		ft_putstr_fd("Command not found\n", 2);
		exit(127);
	}
	lay_in_n_out(pipe_fds, file_fd, i_o);
	execve(cmd_path, args, envp);
	close_fds(file_fd, pipe_fds);
	if (args != NULL)
		free_tab(args);
	exit(errno);
}

pid_t	child1(char **argv, char **envp, int pipe_fds[2])
{
	pid_t	pid1;

	pid1 = fork();
	if (pid1 < 0)
		exit(1);
	if (pid1 == 0)
		child(argv, pipe_fds, 0, envp);
	return (pid1);
}

pid_t	child2(char **argv, char **envp, int pipe_fds[2])
{
	pid_t	pid2;

	pid2 = fork();
	if (pid2 < 0)
		exit(errno);
	if (pid2 == 0)
		child(argv, pipe_fds, 1, envp);
	return (pid2);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		pipe_fds[2];
	int		stat_lock2;

	if (argc != 5)
	{
		ft_putstr_fd("Invalid number of arguments!\n", 2);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipe_fds) == -1)
		return (ft_putstr_fd(strerror(errno), 2), errno);
	pid1 = child1(argv, envp, pipe_fds);
	pid2 = child2(argv, envp, pipe_fds);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &stat_lock2, 0);
	return (WEXITSTATUS(stat_lock2));
}
