/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 20:27:49 by albermud          #+#    #+#             */
/*   Updated: 2023/06/20 20:35:04 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

static int	read_heredoc(t_pipex *px)
{
	char	*line;
	int		fd;
	size_t	len;

	len = ft_strlen(px->limiter);
	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (error_handler(px, px->this, OPEN_FAIL, HEREDOC));
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (close(fd), READ_FAIL);
		if (!ft_strncmp(line, px->limiter, len))
			return (close(fd), free(line), EXIT_SUCCESS);
		if (write(fd, line, ft_strlen(line)) < 0)
			return (close(fd), free(line), WRITE_FAIL);
		free(line);
	}
}

int	ft_heredoc(t_pipex *px, int ac, const char **av)
{
	int	err;

	px->limiter = av[2];
	err = read_heredoc(px);
	if (err)
		return (error_handler(px, px->this, err, HEREDOC));
	px->infile = HEREDOC;
	px->outfile = av[ac - 1];
	px->ncmds = ac - 4;
	px->cmds = av + 3;
	return (EXIT_SUCCESS);
}
