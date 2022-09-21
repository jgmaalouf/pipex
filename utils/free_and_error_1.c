/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:24:21 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/21 11:01:14 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	freelist(t_cmdlist **cmdlist_head)
{
	t_cmdlist	*temp;

	temp = *cmdlist_head;
	while (temp != NULL)
	{
		temp = temp->next;
		free(*cmdlist_head);
		*cmdlist_head = temp;
	}
}

void	malloc_err(char **paths, char **cmd, t_cmdlist **cmdlist)
{
	int	i;

	if (paths != NULL)
	{
		i = 0;
		while (paths[i] != NULL)
			free(paths[i++]);
		free(paths);
	}
	if (cmd != NULL)
	{
		i = 0;
		while (cmd[i] != NULL)
			free(cmd[i++]);
		free(cmd);
	}
	if (cmdlist != NULL)
		freelist(cmdlist);
	perror("malloc");
	exit(EXIT_FAILURE);
}

void	free_and_error_exec(char *path, char **paths, char **cmd,
			t_cmdlist **cmdlist)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	i = 0;
	while (cmd[i] != NULL)
		free(cmd[i++]);
	free(cmd);
	freelist(cmdlist);
	free(path);
	perror("execve");
	exit(127);
}

void	free_and_error_access(t_cmdlist **cmdlist)
{
	freelist(cmdlist);
	perror("file not found");
	exit(EXIT_FAILURE);
}

void	free_and_error_command(char **cmd, char **paths, t_cmdlist **cmdlist)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL)
		free(cmd[i++]);
	free(cmd);
	i = 0;
	while (paths[i] != NULL)
		free(paths[i++]);
	free(paths);
	freelist(cmdlist);
	perror("input error");
	exit(EXIT_FAILURE);
}
