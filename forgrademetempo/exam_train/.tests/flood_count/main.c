/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t_point.h"

int	flood_count(char **tab, t_point size, t_point begin);

static char	*dup_exact(const char *s)
{
	size_t	n;
	char	*d;

	n = strlen(s);
	d = malloc(n + 1);
	if (d == NULL)
		exit(1);
	memcpy(d, s, n + 1);
	return (d);
}

static void	print_row(const char *row, int width)
{
	int	x;
	int	weird;

	x = 0;
	weird = 0;
	while (x < width)
	{
		if (row[x] >= 32 && row[x] < 127)
			printf("%c", row[x]);
		else
		{
			printf("?");
			weird = 1;
		}
		x++;
	}
	if (weird)
		printf("   (? = caractere non affichable)");
	printf("\n");
}

int	main(int argc, char **argv)
{
	char	**tab;
	char	**save;
	t_point	size;
	t_point	begin;
	int		y;
	int		changed;

	setvbuf(stdout, NULL, _IOLBF, 0);
	if (argc < 4)
		return (1);
	begin.x = atoi(argv[1]);
	begin.y = atoi(argv[2]);
	size.y = argc - 3;
	size.x = (int)strlen(argv[3]);
	tab = malloc(sizeof(char *) * size.y);
	save = malloc(sizeof(char *) * size.y);
	if (tab == NULL || save == NULL)
		return (1);
	y = 0;
	while (y < size.y)
	{
		tab[y] = dup_exact(argv[y + 3]);
		save[y] = dup_exact(argv[y + 3]);
		y++;
	}
	printf("flood_count(tab, size = {%d, %d}, begin = {%d, %d}) = ",
		size.x, size.y, begin.x, begin.y);
	fflush(stdout);
	printf("%d\n", flood_count(tab, size, begin));
	changed = 0;
	y = 0;
	while (y < size.y)
	{
		if (memcmp(tab[y], save[y], size.x + 1) != 0)
		{
			if (!changed)
				printf("tab : MODIFIE, il devait rester intact\n");
			printf("  ligne %2d avant : %s\n  ligne %2d apres : ", y, save[y], y);
			print_row(tab[y], size.x);
			changed = 1;
		}
		y++;
	}
	if (!changed)
		printf("tab : intact\n");
	printf("tab :\n");
	y = 0;
	while (y < size.y)
	{
		printf("  %s\n", save[y]);
		free(tab[y]);
		free(save[y]);
		y++;
	}
	free(tab);
	free(save);
	return (0);
}
