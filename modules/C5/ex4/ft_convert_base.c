/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 01:08:00 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/16 01:36:21 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		allbasevalid(char *base_from, char *base_to);
int		ft_atoi_base(char *str, char *base);

int	nbr_len(long nbr, int baselen)
{
	int	compteur;

	compteur = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 0)
	{
		nbr = nbr / baselen;
		compteur++;
	}
	return (compteur);
}

int	ft_baselen(char *base_to)
{
	int	i;

	i = 0;
	while (base_to[i])
		i++;
	return (i);
}

int	ft_isneg(long nbr)
{
	if (nbr < 0)
		return (1);
	return (0);
}

char	*itoa_base(long nbr, char *base_to)
{
	int		baselen;
	int		neg;
	char	*str;
	int		index;

	baselen = ft_baselen(base_to);
	neg = ft_isneg(nbr);
	if (neg == 1)
		nbr = -nbr;
	index = nbr_len(nbr, baselen) + neg - 1;
	str = malloc(sizeof(char) * (index + 2));
	if (str == 0)
		return (NULL);
	str[index + 1] = '\0';
	while (index >= neg)
	{
		str[index] = base_to[nbr % baselen];
		nbr = nbr / baselen;
		index--;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}

char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	if (allbasevalid(base_from, base_to) == 0)
		return (NULL);
	return (itoa_base(ft_atoi_base(nbr, base_from), base_to));
}

// int	main(void)
// {
// 	printf("%s\n", ft_convert_base("42", "0123456789", "01"));
// 	return (0);
// }
