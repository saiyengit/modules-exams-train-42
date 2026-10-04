int	issorted(int *tab, int size)
{
	int	i;
	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			return (0);
		}
		i++;
	}
	return 1;
}

void	sort_int_tab(int *tab, int size)
{
	int	i;
	int	temp;

	i = 0;
	while (i < size - 1 && issorted(tab, size) == 0)
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

int		tab_spread(int *tab, unsigned int len)
{
	int	low;
	int	high;
	if (len == 0)
		return (0);
	sort_int_tab(tab, len);
	low = tab[0];
	high = tab[len - 1];

	return high - low;
}

