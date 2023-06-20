/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albermud <albermud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 18:37:18 by albermud          #+#    #+#             */
/*   Updated: 2023/06/20 18:37:21 by albermud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include "ft_printf.h"
# include "get_next_line.h"

# define USAGE "[file1 | here_doc LIMITER] cmd1 cmd2 ... cmdN file2"
# define NO_CMD "command not found"
# define HEREDOC ".temp_pipex_heredoc_file"
# define MAX_PATH_SIZE		1024
# define NO_ENVP			0 // change to 1 to refuse to run without envp
# define MALLOC_FAIL		42
# define OPEN_FAIL			2
# define CLOSE_FAIL			3
# define FORK_FAIL			4
# define PIPE_FAIL			5
# define DUP_FAIL			6
# define EXECVE_FAIL		127
# define WRITE_FAIL			8
# define READ_FAIL			9
# define TOO_FEW_ARGS		10
# define WAIT_FAIL			11
# define ARGS_FAIL			12
# define CMD_FAIL			-1

typedef struct s_cmd
{
	char	**args;
	char	*path;
}	t_cmd;

typedef struct s_pipex
{
	char const	*this;
	int			ncmds;
	int			infd;
	char const	*infile;
	char const	*outfile;
	int			outfd;
	int			pd[2][2];
	char const	**cmds;
	char const	*limiter;
	char		**paths;
}	t_pipex;

/* childs_bonus.c*/
int		closeallpipes(t_pipex *px);
void	handle_first_child(t_pipex *px, char *const *envp, int *pid);
void	handle_middle_child(t_pipex *px, int n, char *const *envp, int *pid);
void	handle_last_child(t_pipex *px, char *const *envp, int *pid);
int		manage_child_processes(t_pipex *px, int *pid, int i, char *const *envp);

/* cmd_bonus.c */
t_cmd	*ft_validatecmd(const char *bin, char **paths);

/* error_bonus.c */
int		error_handler(t_pipex *px, char const *name, int err, void const *arg);

/* free_bonus.c */
void	free_pipex(t_pipex *px);
void	free_cmd(t_cmd *cmd);
void	free_paths(char **paths);

/* heredoc_bonus.c */
int		ft_heredoc(t_pipex *px, int ac, const char **av);

/* paths_bonus.c */
int		ft_getpaths(char *const *envp, char ***ppaths);

/* pipex_bonus.c */
int		init_pipex(int ac, const char **av, char *const *envp, t_pipex *px);
int		pipex(t_pipex *px, char *const *envp);

#endif
