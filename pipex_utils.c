/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoperacz <aoperacz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:22:52 by aoperacz          #+#    #+#             */
/*   Updated: 2025/06/20 23:48:25 by aoperacz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab || !*tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*cmd_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = ft_strjoin(cmd_path, cmd);
		free(cmd_path);
		if (access(paths[i], F_OK) == 0)
		{
			cmd_path = ft_strdup(paths[i]);
			free_tab(paths);
			return (cmd_path);
		}
		i++;
	}
	return (NULL);
}

char	**get_args(char *cmd)
{
	char	**args;

	if (*cmd == '\0')
		return (NULL);
	args = ft_split(cmd, ' ');
	return (args);
}
