/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:02:56 by aoperacz          #+#    #+#             */
/*   Updated: 2025/06/20 23:48:11 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	check_infile(char *path)
{
	int	infile_fd;

	if (access(path, X_OK) < 0 || access(path, R_OK) < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}
	infile_fd = open(path, O_RDONLY, 0644);
	if (infile_fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}
	return (infile_fd);
}

int	check_outfile(char *path)
{
	int	outfile_fd;

	outfile_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit(errno);
	}
	return (outfile_fd);
}
