/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>

unsigned int	lcm_tab(unsigned int *tab, unsigned int len);

int	main(int argc, char **argv)
{
	unsigned int	*tab;
	unsigned int	len;
	unsigned int	i;

	setvbuf(stdout, NULL, _IOLBF, 0);
	len = (unsigned int)(argc - 1);
	tab = NULL;
	if (len > 0)
	{
		tab = malloc(sizeof(unsigned int) * len);
		if (tab == NULL)
			return (1);
		i = 0;
		while (i < len)
		{
			tab[i] = (unsigned int)strtoul(argv[i + 1], NULL, 10);
			i++;
		}
		printf("lcm_tab({");
		i = 0;
		while (i < len)
		{
			if (i > 0)
				printf(", ");
			printf("%u", tab[i]);
			i++;
		}
		printf("}, %u) = ", len);
	}
	else
		printf("lcm_tab(NULL, 0) = ");
	fflush(stdout);
	printf("%u\n", lcm_tab(tab, len));
	free(tab);
	return (0);
}
