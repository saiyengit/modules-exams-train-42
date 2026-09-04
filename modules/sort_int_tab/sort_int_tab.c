#include <stdio.h>

int	is_sorted(int *tab, int size)
{
	int	i;

	i = 1;
	while (i < size)
	{
		if (tab[i] >= tab[i - 1])
			i++;
		else
			return (0);
	}
	return (1);
}

void	ft_sort_int_tab(int *tab, int size)
{
	int	i;
	int	temp;

	i = 0;
	while (i < size - 1 && is_sorted(tab, 7) == 0)
	{
		while (tab[i + 1] < tab[i])
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		i++;
	}
}

int	main(void)
{
	int i = 0;
	int	tab[] = {3, 8, 6, 2, 9, 2, 6};
	ft_sort_int_tab(tab, 7);
	while (i < 7)
	{
		printf("%d", tab[i]);
		i++;
	}
	return 0;
}
