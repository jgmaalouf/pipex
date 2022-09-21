/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:11:41 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/10 12:39:03 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ptr = NULL;
	ptr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (ptr != NULL)
	{
		i = 0;
		while (s1[i] != '\0')
		{
			ptr[i] = s1[i];
			i++;
		}
		j = 0;
		while (s2[j] != '\0')
			ptr[i++] = s2[j++];
		ptr[i] = '\0';
	}
	return (ptr);
}
