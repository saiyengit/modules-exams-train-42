/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chunks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <yannis.kadoun@learner.42.tech>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 20:02:13 by ykadoun           #+#    #+#             */
/*   Updated: 2026/10/06 03:03:58 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**ft_chunks(char *str, int n)
{
	char	**cpy;
	int		s;
	int		z;
	int		stock;
	int		ic;
	int		i2;
	int		i;
	int		i3;

	if (str == NULL || n <= 0)
		return (NULL);
	s = ft_strlen(str);
	z = s / n;
	if (s % n != 0)
		z++;
	cpy = malloc(sizeof(char *) * (z + 1));
	if (cpy == NULL)
		return (NULL);
	stock = s;
	i = 0;
	ic = 0;
	i2 = 0;
	while (stock >= n)
	{
		cpy[ic++] = malloc(sizeof(char) * (n + 1));
		i3 = 0;
		while (i3 < n)
			cpy[i2][i3++] = str[i++];
		cpy[i2][i3] = '\0';
		i2++;
		stock = stock - n;
	}
	if (stock > 0)
	{
		cpy[ic++] = malloc(sizeof(char) * (stock + 1));
		i3 = 0;
		while (i3 < stock)
			cpy[i2][i3++] = str[i++];
		cpy[i2][i3] = '\0';
	}
	cpy[ic] = NULL;
	return (cpy);
}
