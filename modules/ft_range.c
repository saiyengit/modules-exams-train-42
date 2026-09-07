int	*ft_range(int min, int max)
{
	int	*tab;
	int	i;
	int	size;

	i = 0;
	if (min >= max)
		return (NULL);
	size = max - min;
	tab = malloc(sizeof(int) * size);
	if (tab == 0)
		return (NULL);
	while (min < max)
	{
		tab[i] = min;
		i++;
		min++;
	}
	return (tab);
}
