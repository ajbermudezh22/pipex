/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:26:23 by albermud          #+#    #+#             */
/*   Updated: 2023/06/19 22:05:43 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	init_pipex(int ac, const char **av, char *const *envp, t_pipex *px)
{
	px->this = av[0];
	px->paths = NULL;
	if (ft_getpaths(envp, &px->paths))
		return (MALLOC_FAIL);
	if (pipe(px->pd[0]) == -1 || pipe(px->pd[1]) == -1)
		return (PIPE_FAIL);
	if (!av[1] || av[1][0] == '-' || !ft_memcmp(av[1], "<<", 3) ||
	!ft_memcmp(av[1], "here_doc", 9))
		return (ft_heredoc(px, ac, av));
	px->limiter = NULL;
	px->infile = av[1];
	px->outfile = av[ac - 1];
	px->ncmds = ac - 3;
	px->cmds = av + 2;
	return (EXIT_SUCCESS);
}

int	pipex(t_pipex *px, char *const *envp)
{
	int	i;
	int	*pids;
	int	err;
	int	status;

	i = 0;
	pids = malloc(sizeof(int) * px->ncmds);
	if (!pids)
		return (MALLOC_FAIL);
	err = manage_child_processes(px, pids, i, envp);
	if (err)
		return (free(pids), err);
	if (closeallpipes(px))
		return (free(pids), CLOSE_FAIL);
	i = -1;
	status = 0;
	while (++i < px->ncmds)
	{
		if (waitpid(pids[i], &pids[i], 0)
			&& WIFEXITED(pids[i]) && WEXITSTATUS(pids[i]) > status)
			status = WEXITSTATUS(pids[i]);
	}
	free(pids);
	return (status);
}
