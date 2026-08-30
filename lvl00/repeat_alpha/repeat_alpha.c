/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   repeat_alpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/30 10:09:54 by ykadoun           #+#    #+#             */
/*   Updated: 2026/08/30 10:34:36 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c 1);
}

int	main(int argc, char **argv)
{
	int	i;
	int	i2;
	char	*base1;
	char	*base2;

	base1[] = " abcdefghijklmnopqrstuvwxyz";
	base2[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	i = 0;
	i2 = 0;
	if (argc != 2)
	{
		ft_putchar('\n');
		return (0);
	}
	while (argv[1][i])
	{
		if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
		{
			while (base[i2])
			{
				if (base[i2] == argv[1][i])
				{
				}
			}
		}

		else si c chiffre etc affiche normal
	}
}
