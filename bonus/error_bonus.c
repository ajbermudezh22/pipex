/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 20:19:17 by albermud          #+#    #+#             */
/*   Updated: 2023/06/19 21:52:28 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

int	error_handler(t_pipex *px, char const *name, int err, void const *arg)
{
	int	exitcode;

	exitcode = EXIT_FAILURE;
	if ((err == OPEN_FAIL || err == WRITE_FAIL || err == READ_FAIL) && arg)
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", name, (char *)arg, \
		strerror(errno));
	else if (err == TOO_FEW_ARGS)
		ft_printf("Usage: %s %s\n", name, USAGE);
	else if (err == CMD_FAIL)
	{
		exitcode = 127;
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n", name, NO_CMD, (char *)arg);
	}
	else if (err > EXECVE_FAIL)
		exitcode = 2;
	else if (err && errno)
		ft_fprintf(STDERR_FILENO, "%s: %s\n", name, strerror(errno));
	if (px)
		free_pipex(px);
	exit(exitcode);
}
