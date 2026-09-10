/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:49:33 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/07 19:28:21 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strjoinlen(int size, char **strs, char *sep)
{
	int	totalstrssep;
	int	i;

	i = 0;
	totalstrssep = 0;
	if (size == 0)
		return (0);
	while (i < size)
	{
		totalstrssep = totalstrssep + ft_strlen(strs[i]);
		if (i < size - 1)
			totalstrssep = totalstrssep + ft_strlen(sep);
		i++;
	}
	return (totalstrssep);
}

void	ft_strjoin_fill(char *res, int size, char **strs, char *sep)
{
	int	i;
	int	i2;
	int	i3;
	int	ir;

	i = 0;
	ir = 0;
	while (i < size)
	{
		i2 = 0;
		while (strs[i][i2])
			res[ir++] = strs[i][i2++];
		if (i < size - 1)
		{
			i3 = 0;
			while (sep[i3])
				res[ir++] = sep[i3++];
		}
		i++;
	}
	res[ir] = '\0';
}

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strjoinlen(size, strs, sep) + 1));
	if (res == 0)
		return (NULL);
	ft_strjoin_fill(res, size, strs, sep);
	return (res);
}
