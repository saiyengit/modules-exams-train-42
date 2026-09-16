/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 15:52:18 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/14 19:09:31 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	isdoublon(char *base)
{
	int	i;
	int	i2;

	i = 0;
	while (base[i])
	{
		i2 = 0;
		while (i2 < i)
		{
			if (base[i] == base[i2])
				return (1);
			i2++;
		}
		i++;
	}
	return (0);
}

int	checkbase(char *base)
{
	int	i;

	i = 0;
	if (isdoublon(base) == 1)
		return (0);
	if (base[0] == '\0' || base[1] == '\0')
		return (0);
	while (base[i])
	{
		if (base[i] == ' ' || base[i] == '-' || base[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

int	allbasevalid(char *base_from, char *base_to)
{
	if (checkbase(base_from) == 1 && checkbase(base_to) == 1)
		return (1);
	return (0);
}

int	getcharvalue(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	i;
	int	result;
	int	baselen;
	int	sign;

	i = 0;
	baselen = 0;
	sign = 1;
	result = 0;
	while (base[baselen])
		baselen++;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (getcharvalue(str[i], base) != -1)
	{
		result = result * baselen + getcharvalue(str[i], base);
		i++;
	}
	return (result * sign);
}

// int	main(void)
// {
// 	printf("%d\n", ft_atoi_base("101010", "01"));
// 	return (0);
// }
