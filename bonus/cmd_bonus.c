/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:32:35 by albermud          #+#    #+#             */
/*   Updated: 2023/06/19 21:33:53 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

static t_cmd	*check_path(t_cmd *cmd, const char *path)
{
	cmd->path = ft_strjoin(path, cmd->args[0]);
	if (!cmd->path)
		return (NULL);
	if (!access(cmd->path, X_OK))
		return (cmd);
	free(cmd->path);
	cmd->path = NULL;
	return (NULL);
}

t_cmd	*ft_validatecmd(const char *bin, char **paths)
{
	int		i;
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = ft_split_blocks(bin, ' ', "\"\'");
	if (!cmd->args)
		return (free_cmd(cmd), NULL);
	if ((cmd->args[0][0] == '.') && check_path(cmd, ""))
		return (cmd);
	if (ft_strchr(cmd->args[0], '/') && check_path(cmd, ""))
		return (cmd);
	if (!paths)
		return (free_cmd(cmd), NULL);
	i = 0;
	while (paths[i])
		if (check_path(cmd, paths[i++]))
			return (cmd);
	return (free_cmd(cmd), NULL);
}
