/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:31:19 by aoperacz          #+#    #+#             */
/*   Updated: 2025/06/21 15:55:42 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

int		check_infile(char *path);
int		check_outfile(char *path);
char	*get_path(char *cmd, char **envp);
char	**get_args(char *cmd);
void	free_tab(char **tab);
char	**set_args(char **argv, int *file_fd, int i_o);
void	close_fds(int fd, int pipe_fds[2]);
#endif