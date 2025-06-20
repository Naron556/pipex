/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:33:04 by aoperacz          #+#    #+#             */
/*   Updated: 2025/06/21 00:18:29 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	lay_in_n_out1(int pipe_fds[2], int file_fd, int i_o)
{
	if (i_o == 0)
	{
		dup2(file_fd, STDIN_FILENO);
		close(file_fd);
		close(pipe_fds[0]);
		dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[1]);
	}
	else
	{
		dup2(file_fd, STDOUT_FILENO);
		close(file_fd);
		close(pipe_fds[1]);
		dup2(pipe_fds[0], STDIN_FILENO);
		close(pipe_fds[0]);
	}
}

int	child(char *cmd, int file_fd, int pipe_fds[2], int i_o, char **envp)
{
	char	**args;
	char	*cmd_path;

	args = get_args(cmd);
	cmd_path = NULL; 
	if (args != NULL)
		cmd_path = get_path(args[0], envp);
	if (!cmd_path || args == NULL)
	{
		free_tab(args);
		exit(127);
	}
	lay_in_n_out(pipe_fds, file_fd, i_o);
	execve(cmd_path, args, envp);
	if (args == NULL)
		free_tab(args);
	exit(errno);
}

pid_t	child1(char **argv, char **envp, int pipe_fds[2])
{
	pid_t	pid1;
	int		infile_fd;

	pid1 = fork();
	if (pid1 < 0)
		exit(1);
	if (pid1 == 0)
	{
		infile_fd = check_infile(argv[1]);
		child(argv[2], infile_fd, pipe_fds, 0, envp);
	}
	return (pid1);
}

pid_t	child2(char **argv, char **envp, int pipe_fds[2])
{
	pid_t	pid2;
	int		outfile_fd;

	pid2 = fork();
	if (pid2 < 0)
		exit(errno);
	if (pid2 == 0)
	{
		outfile_fd = check_outfile(argv[4]);
		child(argv[3], outfile_fd, pipe_fds, 1, envp);
	}
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
		ft_putstr_fd("Invalid number of arguments!", 2);
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
	if (WIFEXITED(stat_lock2))
		if (WEXITSTATUS(stat_lock2) != 0)
			ft_putstr_fd(strerror(errno), 2);
	return (WEXITSTATUS(stat_lock2));
}
