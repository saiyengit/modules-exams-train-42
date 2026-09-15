/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 15:32:05 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/16 01:34:06 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	issep(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	debut_word(char *str, int i, char *charset)
{
	if ((i == 0 && issep(str[i], charset) == 0) || (i > 0 && issep(str[i],
				charset) == 0 && issep(str[i - 1], charset) == 1))
		return (1);
	return (0);
}

int	count_words(char *str, char *charset)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (debut_word(str, i, charset) == 1)
			total++;
		i++;
	}
	return (total);
}

char	*extract_word(char *str, int start, char *charset)
{
	char	*cpy;
	int		ic;
	int		len;
	int		memostart;

	memostart = start;
	len = 0;
	while (str[start] && issep(str[start], charset) == 0)
	{
		start++;
		len++;
	}
	ic = 0;
	cpy = malloc(sizeof(char) * (len + 1));
	if (cpy == 0)
		return (NULL);
	while (str[memostart] && issep(str[memostart], charset) == 0)
		cpy[ic++] = str[memostart++];
	cpy[ic] = '\0';
	return (cpy);
}

char	**ft_split(char *str, char *charset)
{
	char	**res;
	int		i;
	int		ir;

	i = 0;
	ir = 0;
	res = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (res == NULL)
		return (NULL);
	while (str[i])
	{
		if (debut_word(str, i, charset) == 1)
		{
			res[ir] = extract_word(str, i, charset);
			if (res[ir] == NULL)
				return (NULL);
			ir++;
		}
		i++;
	}
	res[ir] = NULL;
	return (res);
}
