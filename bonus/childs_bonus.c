/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:19:35 by albermud          #+#    #+#             */
/*   Updated: 2023/06/19 22:04:55 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	closeallpipes(t_pipex *px)
{
	return (close(px->pd[0][0]) || close(px->pd[0][1]) ||
			close(px->pd[1][0]) || close(px->pd[1][1]));
}

void	handle_first_child(t_pipex *px, char *const *envp, int *pid)
{
	t_cmd	*cmd;

	free(pid);
	px->infd = open(px->infile, O_RDONLY);
	if (px->infd < 0)
		error_handler(px, px->this, OPEN_FAIL, px->infile);
	if (dup2(px->pd[0][1], STDOUT_FILENO) < 0)
		exit(DUP_FAIL);
	if (dup2(px->infd, STDIN_FILENO) < 0)
		exit(DUP_FAIL);
	if (closeallpipes(px) || close(px->infd))
		exit(CLOSE_FAIL);
	cmd = ft_validatecmd(px->cmds[0], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	else
		error_handler(px, px->this, CMD_FAIL, px->cmds[0]);
	free_cmd(cmd);
	error_handler(px, px->this, EXECVE_FAIL, NULL);
}

void	handle_middle_child(t_pipex *px, int n, char *const *envp, int *pid)
{
	t_cmd	*cmd;

	free(pid);
	if (dup2(px->pd[n & 1][1], STDOUT_FILENO) < 0)
		exit(DUP_FAIL);
	if (dup2(px->pd[(n - 1) & 1][0], STDIN_FILENO) < 0)
		exit(DUP_FAIL);
	if (closeallpipes(px))
		exit(CLOSE_FAIL);
	cmd = ft_validatecmd(px->cmds[n], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	else
		error_handler(px, px->this, CMD_FAIL, px->cmds[n]);
	free_cmd(cmd);
	error_handler(px, px->this, EXECVE_FAIL, NULL);
}

void	handle_last_child(t_pipex *px, char *const *envp, int *pid)
{
	t_cmd	*cmd;

	free(pid);
	if (!ft_strncmp(px->infile, HEREDOC, ft_strlen(HEREDOC)))
		px->outfd = open(px->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		px->outfd = open(px->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (px->outfd < 0)
		error_handler(px, px->this, OPEN_FAIL, px->outfile);
	if (dup2(px->outfd, STDOUT_FILENO) < 0)
		exit(DUP_FAIL);
	if (dup2(px->pd[px->ncmds & 1][0], STDIN_FILENO) < 0)
		exit(DUP_FAIL);
	if (closeallpipes(px) || close(px->outfd))
		exit(CLOSE_FAIL);
	cmd = ft_validatecmd(px->cmds[px->ncmds - 1], px->paths);
	if (cmd)
		execve(cmd->path, cmd->args, envp);
	else
		error_handler(px, px->this, CMD_FAIL, px->cmds[px->ncmds - 1]);
	free_cmd(cmd);
	error_handler(px, px->this, EXECVE_FAIL, NULL);
}

int	manage_child_processes(t_pipex *px, int *pid, int i, char *const *envp)
{
	pid[i] = fork();
	if (pid[i] < 0)
		return (FORK_FAIL);
	if (!pid[i])
		handle_first_child(px, envp, pid);
	while (++i < px->ncmds - 1)
	{	
		pid[i] = fork();
		if (pid[i] < 0)
			return (FORK_FAIL);
		if (!pid[i])
			handle_middle_child(px, i, envp, pid);
		if (close(px->pd[(i - 1) & 1][0]) || close(px->pd[(i - 1) & 1][1]))
			return (CLOSE_FAIL);
		if (pipe(px->pd[(i - 1) & 1]))
			return (PIPE_FAIL);
	}	
	pid[i] = fork();
	if (pid[i] < 0)
		return (FORK_FAIL);
	if (!pid[i])
		handle_last_child(px, envp, pid);
	return (EXIT_SUCCESS);
}
