/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:02:56 by aoperacz          #+#    #+#             */
/*   Updated: 2025/06/21 16:37:36 by aoperacz         ###   ########.fr       */
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
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	infile_fd = open(path, O_RDONLY, 0644);
	if (infile_fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	return (infile_fd);
}

int	check_outfile(char *path)
{
	int	outfile_fd;

	if (access(path, X_OK) < 0 || access(path, R_OK) < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (-1);
	}
	outfile_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	return (outfile_fd);
}
