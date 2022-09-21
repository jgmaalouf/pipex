/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:01:32 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/20 11:46:50 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

/* This function joins the "/" at the end of the path, then joins
	cmd[0] to the end of the path */
char	*join_path_cmd(char **paths, char **cmd, int i)
{
	char	*join_fslash;
	char	*join_cmd;

	join_fslash = ft_strjoin(paths[i], "/");
	if (join_fslash == NULL)
		return (NULL);
	join_cmd = ft_strjoin(join_fslash, cmd[0]);
	free(join_fslash);
	if (join_cmd == NULL)
		return (NULL);
	return (join_cmd);
}

/* This function takes the environment variable and parses the different 
	binary paths (i.e. where the commands are stored) */
char	**parse_paths(char **envp)
{
	int		i;
	char	*path_variable;
	char	**paths;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path_variable = envp[i];
		i++;
	}
	paths = ft_split(path_variable + 5, ':');
	return (paths);
}

/* This function takes a node from a linked list and executes the command
	that the node holds */
void	exec_cmd(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist)
{
	int		i;
	char	**cmd;
	char	**paths;
	char	*path;

	cmd = ft_split((*tmp)->cmd, ' ');
	paths = parse_paths(envp);
	if (cmd == NULL || paths == NULL)
		malloc_err(paths, cmd, cmdlist);
	i = 0;
	while (paths[i] != NULL)
	{
		path = join_path_cmd(paths, cmd, i);
		if (path == NULL)
			malloc_err(paths, cmd, cmdlist);
		if (access(path, F_OK) == 0)
			if (execve(path, cmd, envp) == -1)
				free_and_error_exec(path, paths, cmd, cmdlist);
		i++;
		free(path);
	}
	free_and_error_command(cmd, paths, cmdlist);
}
