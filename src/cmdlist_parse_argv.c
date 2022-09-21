/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlist_parse_argv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:09:21 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/20 09:08:01 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

/* This functions allocates a new node*/
t_cmdlist	*cmdlist_new_node(int i, char **argv)
{
	t_cmdlist	*node;

	node = NULL;
	node = malloc(sizeof(t_cmdlist));
	if (node != NULL)
	{
		node->cmd = argv[i];
		node->next = NULL;
		return (node);
	}
	return (NULL);
}

/* This functions creates a new node and puts the cmd inside it*/
int	cmdlist_addcmd(int i, char **argv, t_cmdlist **cmdlist_head)
{
	t_cmdlist	*temp;

	if (*cmdlist_head == NULL)
		*cmdlist_head = cmdlist_new_node(i, argv);
	else
	{
		temp = *cmdlist_head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = cmdlist_new_node(i, argv);
		if (temp->next == NULL)
			return (-1);
	}
	return (0);
}

/* This function will create a linked list of all the arguments I have */
void	cmdlist_parse_argv(int argc, char **argv, t_cmdlist **cmdlist_head)
{
	int			i;

	*cmdlist_head = NULL;
	i = 1;
	while (i < argc)
		if (cmdlist_addcmd(i++, argv, cmdlist_head) == -1)
			malloc_err(NULL, NULL, cmdlist_head);
}
