/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 11:53:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/21 10:59:22 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	pipification(t_cmdlist **tmp, char **envp, t_cmdlist **cmdlist_head, int i)
{
	t_fd		fd;

	if (i == 0)
		first_cmd(tmp, envp, cmdlist_head, &fd);
	else if ((*tmp)->next->next == NULL && i % 2 == 0)
		last_cmd2(tmp, envp, cmdlist_head, &fd);
	else if ((*tmp)->next->next == NULL)
		last_cmd1(tmp, envp, cmdlist_head, &fd);
	else if (i % 2 == 0)
		middle_cmd2(tmp, envp, cmdlist_head, &fd);
	else
		middle_cmd1(tmp, envp, cmdlist_head, &fd);
	i++;
	return (i);
}

int	here_doc_pipification(t_cmdlist **tmp, char **envp,
		t_cmdlist **cmdlist_head, int i)
{
	t_fd		fd;

	if (i == 0)
		first_cmd_heredoc(tmp, envp, cmdlist_head, &fd);
	else if ((*tmp)->next->next == NULL && i % 2 == 0)
		last_cmd2_heredoc(tmp, envp, cmdlist_head, &fd);
	else if ((*tmp)->next->next == NULL)
		last_cmd1_heredoc(tmp, envp, cmdlist_head, &fd);
	else if (i % 2 == 0)
		middle_cmd2(tmp, envp, cmdlist_head, &fd);
	else
		middle_cmd1(tmp, envp, cmdlist_head, &fd);
	i++;
	return (i);
}

void	pipex(t_cmdlist **cmdlist, char **envp)
{
	t_cmdlist	*tmp;
	int			i;

	i = 0;
	tmp = *cmdlist;
	if (ft_strncmp(tmp->cmd, "here_doc", 9) == 0)
	{
		while (tmp->next != NULL)
		{
			i = here_doc_pipification(&tmp, envp, cmdlist, i);
			tmp = tmp->next;
		}
		unlink("here_doc");
	}
	else
	{
		while (tmp->next != NULL)
		{
			i = pipification(&tmp, envp, cmdlist, i);
			tmp = tmp->next;
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int			status;
	t_cmdlist	*cmdlist;

	if (argc < 5 || (argc < 6 && ft_strncmp(argv[1], "here_doc", 9) == 0))
		return (write(2, "Error: invalid input\n", 22));
	cmdlist_parse_argv(argc, argv, &cmdlist);
	pipex(&cmdlist, envp);
	while (wait(&status) != -1)
		continue ;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (EXIT_SUCCESS);
}
