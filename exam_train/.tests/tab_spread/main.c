/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>

int	tab_spread(int *tab, unsigned int len);

int	main(int argc, char **argv)
{
	int				*tab;
	unsigned int	len;
	unsigned int	i;

	setvbuf(stdout, NULL, _IOLBF, 0);
	len = (unsigned int)(argc - 1);
	tab = NULL;
	if (len > 0)
	{
		tab = malloc(sizeof(int) * len);
		if (tab == NULL)
			return (1);
		i = 0;
		while (i < len)
		{
			tab[i] = (int)strtol(argv[i + 1], NULL, 10);
			i++;
		}
		printf("tab_spread({");
		i = 0;
		while (i < len)
		{
			if (i > 0)
				printf(", ");
			printf("%d", tab[i]);
			i++;
		}
		printf("}, %u) = ", len);
	}
	else
		printf("tab_spread(NULL, 0) = ");
	fflush(stdout);
	printf("%d\n", tab_spread(tab, len));
	free(tab);
	return (0);
}
