/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbuisson <lbuisson@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 12:43:16 by lbuisson          #+#    #+#             */
/*   Updated: 2025/01/07 12:56:55 by lbuisson         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static int	ft_is_charset(char c, char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	countwords(char const *s, char *charset)
{
	size_t	count;
	size_t	i;

	if (!s)
		return (0);
	count = 0;
	i = 0;
	while (s[i])
	{
		if ((ft_is_charset(s[i], charset) == 0
				&& ft_is_charset(s[i + 1], charset) == 1)
			|| (!s[i + 1] && ft_is_charset(s[i], charset) == 0))
			count++;
		if (s[i] == '\'' && s[i + 1] == ' ' && s[i + 1])
			count++;
		i++;
	}
	return (count);
}

static char	*ft_createstr(const char *s, char *charset, size_t *index)
{
	char	*str;
	size_t	index_temp;
	size_t	len;

	index_temp = *index;
	len = 0;
	while ((ft_is_charset(s[index_temp], charset) == 0 && s[index_temp]))
	{
		index_temp++;
		len++;
	}
	if ((s[index_temp] == '\'' && s[index_temp + 1] == ' '
			&& s[index_temp + 1] && s[index_temp]))
	{
		(*index)++;
		len++;
	}
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + (*index), len + 1);
	(*index) += len;
	return (str);
}

static char	**ft_free(char **split)
{
	size_t	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			split[i] = NULL;
			i++;
		}
		free (split);
	}
	return (NULL);
}

char	**split_cmd(char const *s, char *charset)
{
	char	**split;
	size_t	index;
	size_t	j;

	split = (char **)malloc((countwords(s, charset) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	index = 0;
	j = 0;
	while (countwords(s, charset) > j)
	{
		while (ft_is_charset(s[index], charset) == 1 && s[index])
		{
			index++;
			if (s[index] == '\'' && s[index + 1] == ' '
				&& s[index + 1] && s[index])
				break ;
		}
		split[j] = ft_createstr(s, charset, &index);
		if (!split[j])
			return (ft_free(split));
		j++;
	}
	split[j] = NULL;
	return (split);
}
