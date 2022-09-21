/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 11:51:42 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/21 10:57:16 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "../get_next_line/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_cmdlist
{
	char				*cmd;
	struct s_cmdlist	*next;
}						t_cmdlist;

typedef struct s_fd
{
	int	fd1[2];
	int	fd2[2];
}		t_fd;

void	cmdlist_parse_argv(int argc, char **argv, t_cmdlist **cmdlist_head);
void	exec_cmd(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist);
int		here_doc(t_cmdlist **cmdlist);

// utils functions
void	freelist(t_cmdlist **cmdlist_head);
void	malloc_err(char **paths, char **cmd, t_cmdlist **cmdlist);
void	free_and_error_exec(char *path, char **paths, char **cmd,
			t_cmdlist **cmdlist);
void	free_and_error_command(char **cmd, char **paths, t_cmdlist **cmdlist);
void	free_and_error_dup2(t_cmdlist **cmdlist);
void	free_and_error_access(t_cmdlist **cmdlist);
void	fork_err(t_cmdlist **cmdlist);
void	pipe_err(t_cmdlist **cmdlist);

// pipex.c functions
void	first_cmd(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd);
void	last_cmd1(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd);
void	last_cmd2(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd);
void	middle_cmd1(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd);
void	middle_cmd2(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd);

// here_doc related
void	first_cmd_heredoc(t_cmdlist **tmp, char **envp,
			t_cmdlist **cmdlist_head, t_fd *fd);
void	last_cmd1_heredoc(t_cmdlist **tmp, char **envp,
			t_cmdlist **cmdlist_head, t_fd *fd);
void	last_cmd2_heredoc(t_cmdlist **tmp, char **envp,
			t_cmdlist **cmdlist_head, t_fd *fd);
#endif