/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 09:24:21 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/21 11:01:28 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

void	free_and_error_dup2(t_cmdlist **cmdlist)
{
	freelist(cmdlist);
	perror("dup2");
	exit(EXIT_FAILURE);
}

void	fork_err(t_cmdlist **cmdlist)
{
	freelist(cmdlist);
	perror("fork");
	exit(EXIT_FAILURE);
}

void	pipe_err(t_cmdlist **cmdlist)
{
	freelist(cmdlist);
	perror("pipe");
	exit(EXIT_FAILURE);
}
