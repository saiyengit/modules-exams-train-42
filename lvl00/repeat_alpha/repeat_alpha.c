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
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	int	i;
	int	i2;
	int	i3;
	int	x;
	char	*base1;
	char	*base2;

	base1 = " abcdefghijklmnopqrstuvwxyz";
	base2 = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	i = 0;
	if (argc != 2)
	{
		ft_putchar('\n');
		return (0);
	}
	while (argv[1][i])
	{
		if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
		{
			i2 = 0;
			while (base1[i2])
			{
				if (base1[i2] == argv[1][i])
				{
					x = 0;
					while (x < i2)
					{
						ft_putchar(argv[1][i]);
						x++;
					}
				}
				i2++;
			}
		}
		if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
		{
			i3 = 0;
			while (base2[i3])
			{
				if (base2[i3] == argv[1][i])
				{
					x = 0;
					while (x < i3)
					{
						ft_putchar(argv[1][i]);
						x++;
					}
				}
				i3++;
			}
		}
		if (!((argv[1][i] >= 'A' && argv[1][i] <= 'Z') || (argv[1][i] >= 'a' && argv[1][i] <= 'z')))
			ft_putchar(argv[1][i]);
		i++;
	}
	ft_putchar('\n');
	return (0);
}
