/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 18:26:04 by albermud          #+#    #+#             */
/*   Updated: 2023/06/19 21:29:38 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	ft_getpaths(char *const *envp, char ***ppaths)
{
	char	**paths;
	char	*path;
	int		i;

	path = NULL;
	i = 0;
	if (!envp)
		return (NO_ENVP);
	while (!path && *envp)
		path = ft_strnstr(*envp++, "PATH=", 5);
	if (!path)
		return (1);
	paths = ft_split(path + 5, ':');
	if (!paths)
		return (1);
	while (paths[i] && paths[i][ft_strlen(paths[i]) - 1] != '/')
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (free_paths(paths), 1);
		free(paths[i]);
		paths[i++] = path;
	}
	*ppaths = paths;
	return (0);
}
