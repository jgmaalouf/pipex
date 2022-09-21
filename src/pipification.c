/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 08:30:43 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/21 10:59:44 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	first_cmd(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd)
{
	int	pid;
	int	openfd;

	if (pipe(fd->fd1) == -1)
		pipe_err(cmdlist_head);
	pid = fork();
	if (pid == -1)
		fork_err(cmdlist_head);
	if (pid == 0)
	{
		openfd = open((*tmp)->cmd, O_RDONLY);
		if (openfd == -1)
			free_and_error_access(cmdlist_head);
		if (dup2(openfd, STDIN_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		close(openfd);
		if (dup2(fd->fd1[1], STDOUT_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		close(fd->fd1[1]);
		close(fd->fd1[0]);
		*tmp = (*tmp)->next;
		exec_cmd(tmp, envp, cmdlist_head);
	}
	close(fd->fd1[1]);
}

void	middle_cmd1(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd)
{
	int	pid;

	if (pipe(fd->fd2) == -1)
		pipe_err(cmdlist_head);
	pid = fork();
	if (pid == -1)
		fork_err(cmdlist_head);
	if (pid == 0)
	{
		if (dup2(fd->fd1[0], STDIN_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		close(fd->fd1[0]);
		if (dup2(fd->fd2[1], STDOUT_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		close(fd->fd2[1]);
		close(fd->fd2[0]);
		exec_cmd(tmp, envp, cmdlist_head);
	}
	close(fd->fd1[0]);
	close(fd->fd2[1]);
}

void	middle_cmd2(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd)
{
	int	pid;

	if (pipe(fd->fd1) == -1)
		pipe_err(cmdlist_head);
	pid = fork();
	if (pid == -1)
		fork_err(cmdlist_head);
	if (pid == 0)
	{
		if (dup2(fd->fd2[0], STDIN_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		close(fd->fd2[0]);
		if (dup2(fd->fd1[1], STDOUT_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		close(fd->fd1[1]);
		close(fd->fd1[0]);
		exec_cmd(tmp, envp, cmdlist_head);
	}
	close(fd->fd2[0]);
	close(fd->fd1[1]);
}

void	last_cmd1(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd)
{
	int	pid;
	int	openfd;

	pid = fork();
	if (pid == -1)
		fork_err(cmdlist_head);
	if (pid == 0)
	{
		if (dup2(fd->fd1[0], STDIN_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		close(fd->fd1[0]);
		openfd = open((*tmp)->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (openfd == -1)
			free_and_error_access(cmdlist_head);
		if (dup2(openfd, STDOUT_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		exec_cmd(tmp, envp, cmdlist_head);
	}
	close(fd->fd1[0]);
}

void	last_cmd2(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head,
			t_fd *fd)
{
	int	pid;
	int	openfd;

	pid = fork();
	if (pid == -1)
		fork_err(cmdlist_head);
	if (pid == 0)
	{
		if (dup2(fd->fd2[0], STDIN_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		close(fd->fd2[0]);
		openfd = open((*tmp)->next->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (openfd == -1)
			free_and_error_access(cmdlist_head);
		if (dup2(openfd, STDOUT_FILENO) == -1)
			free_and_error_dup2(cmdlist_head);
		exec_cmd(tmp, envp, cmdlist_head);
	}
	close(fd->fd2[0]);
}
