#include <stdio.h>

int		max(int* tab, unsigned int len)
{
	int	i;
	int	max;

	max = tab[0];
	i = 0;
	while (i < len)
	{
		if (tab[i] >= max)
			max = tab[i];
		i++;
	}
	return (max);
}

int	main(void)
{
	int a;
	int tab[7] = {0, 1, 2, 3, 6, 9, 5};
	a = max(tab, 7);
	printf("%d",a);
	return (0);
}
