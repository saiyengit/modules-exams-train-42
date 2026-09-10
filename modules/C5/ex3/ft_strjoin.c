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

char	*ft_strjoin(int size, char **strs, char *sep)
{
	char	*res;
	int	i;
	int	i2;
	int	totalstrs;
	int	i3;
	int	ir;

	i = 0;
	i2 = 0;
	ir = 0;
	totalstrs = 0;
	if (size == 0)
		return (NULL);
	while (i < size)
	{
		totalstrs = totalstrs + ft_strlen(strs[i]);
		i++;
	}
	res = malloc(sizeof(char) * (totalstrs + ((size - 1) * ft_strlen(sep)) + 1));
	if (res == 0)
		return (NULL);
	i = 0;
	while (i < size)
	{
		i2 = 0;
		while (strs[i][i2])
		{
			res[ir] = strs[i][i2];
			ir++;
			i2++;
		}
		if (i < size - 1)
		{
			i3 = 0;
			while (sep[i3])
				res[ir++] = sep[i3++];
		}
		i++;
	}
	res[ir] = '\0';
	return (res);
}
