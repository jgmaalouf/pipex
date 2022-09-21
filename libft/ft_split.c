/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:12:40 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/09/10 12:27:57 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/libft.h"

static char	**free_all(char **res, int j)
{
	while (j >= 0)
	{
		free(res[j]);
		j--;
	}
	free(res);
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
			count += 1;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (count);
}

static int	word_len(char const *s, char c, size_t i)
{
	int	len;

	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static char	**ft_fill(char const *s, char c, char **res)
{
	size_t	i;
	size_t	len;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		len = 0;
		while (s[i] != '\0' && s[i] == c)
			i++;
		len = word_len(s, c, i);
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (s[i] == c || ((s[i] == '\0' && s[i - 1] != c)))
		{
			res[j] = (char *)malloc(sizeof(char) * (len + 1));
			if (res[j] == NULL)
				return (free_all(res, j));
			ft_strlcpy(res[j++], s + (i - len), len + 1);
		}
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	res = NULL;
	if (s != NULL)
	{
		res = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
		if (res != NULL)
			res = ft_fill(s, c, res);
	}
	return (res);
}
