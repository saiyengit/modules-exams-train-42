#include <stdio.h>

int	 is_power_of_2(unsigned int n)
{
	int	i;
	int	produit;

	produit = 1;
	i = 1;
	while (i <= n)
	{
		if (n == produit)
			return (1);
		produit = produit * 2;
		i++;
	}
	return (0);
}

int	main(void)
{
	int m;
	m = is_power_of_2(1);
	printf("%d", m);
}
