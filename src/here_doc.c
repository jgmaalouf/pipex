/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 14:33:11 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/20 12:32:50 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

int	here_doc(t_cmdlist **cmdlist)
{
	int		heredoc_wfd;
	int		heredoc_rfd;
	char	*input;

	heredoc_wfd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	heredoc_rfd = open("here_doc", O_RDONLY);
	if (heredoc_wfd == -1 || heredoc_rfd == -1)
		free_and_error_access(cmdlist);
	while (1)
	{
		write(1, "pipe heredoc> ", 15);
		input = get_next_line(STDIN_FILENO);
		if (ft_strlen(input) - 1 == ft_strlen((*cmdlist)->next->cmd)
			&& ft_strncmp(input, (*cmdlist)->next->cmd,
				ft_strlen((*cmdlist)->next->cmd)) == 0)
			break ;
		write(heredoc_wfd, input, ft_strlen(input));
		free(input);
	}
	free(input);
	close(heredoc_wfd);
	return (heredoc_rfd);
}
