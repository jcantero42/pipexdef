/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcantero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:27:53 by jcantero          #+#    #+#             */
/*   Updated: 2025/02/06 13:27:54 by jcantero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_split(char	**strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		++i;
	}
	free(strs);
}

void	ft_strncpy(char	*word, char *str, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		word[i] = str[i];
		++i;
	}
}

int	ft_wordcount(char *str, int c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			++word;
			while (str[i] && str[i] != c)
			{
				++i;
				if (str[i] == '\0')
				{
					return (word);
				}
			}
		}
		++i;
	}
	return (word);
}

char	*ft_stralloc(char *str, int c, int *k)
{
	int		i;
	int		len;
	char	*word;

	i = *k;
	len = 0;
	while (str[i] == c)
		++i;
	while (str[i + len] && str[i + len] != c)
		++len;
	if (len == 0)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	ft_strncpy(word, &str[i], len);
	word[len] = '\0';
	*k = i + len;
	return (word);
}

char	**ft_split(const char *str, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		pos;

	i = 0;
	pos = 0;
	j = ft_wordcount((char *)str, c);
	if (str == NULL)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (j + 1));
	if (strs == NULL)
		return (NULL);
	while (i < j)
	{
		strs[i] = ft_stralloc((char *)str, c, &pos);
		if (strs[i] == NULL)
		{
			ft_free_split(strs);
			return (NULL);
		}
		++i;
	}
	strs[j] = NULL;
	return (strs);
}
