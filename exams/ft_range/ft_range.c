#include <stdlib.h>
#include <stdio.h>

int     *ft_range(int start, int end)
{
	int	*tab;
	int	size;
	int	i;

	i = 0;
	if (start > end)
		size = start - end;
	else 
		size = end - start;

	tab = malloc(sizeof(int) * size);
	if (tab == 0)
		return NULL;
	while (i < size + 1)
	{
		tab[i] = start;
		if (start > end)
			start--;
		else if (end >= start)
			start++;
		i++;
	}
	return (tab);
}

int	main(void)
{
	int	*tab = ft_range(3, 3);
	int	size = 1;
	int	i;
	
	i = 0;
	while (i < size)
	{
		printf("%d", tab[i]);
		i++;
	}
	return (0);
}
