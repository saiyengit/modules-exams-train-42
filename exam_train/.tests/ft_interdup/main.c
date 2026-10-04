/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*ft_interdup(char *s1, char *s2);

#ifndef NO_WRAP

void			*__real_malloc(size_t size);
void			*__wrap_malloc(size_t size);

# define TRACK_MAX 100000

static void		*g_ptr[TRACK_MAX];
static size_t	g_size[TRACK_MAX];
static int		g_count;
static int		g_tracking;

void	*__wrap_malloc(size_t size)
{
	void	*p;

	p = __real_malloc(size);
	if (g_tracking && p != NULL && g_count < TRACK_MAX)
	{
		g_ptr[g_count] = p;
		g_size[g_count] = size;
		g_count++;
	}
	return (p);
}

static long	alloc_size(void *p)
{
	int	i;

	i = g_count - 1;
	while (i >= 0)
	{
		if (g_ptr[i] == p)
			return ((long)g_size[i]);
		i--;
	}
	return (-1);
}

#else

static int	g_tracking;

static long	alloc_size(void *p)
{
	(void)p;
	return (-2);
}

#endif

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

int	main(int argc, char **argv)
{
	char	*s1;
	char	*s2;
	char	*res;
	long	size;

	setvbuf(stdout, NULL, _IOLBF, 0);
	if (argc != 3)
		return (1);
	s1 = dup_exact(argv[1]);
	s2 = dup_exact(argv[2]);
	printf("ft_interdup(\"%s\", \"%s\") = ", s1, s2);
	fflush(stdout);
	g_tracking = 1;
	res = ft_interdup(s1, s2);
	g_tracking = 0;
	if (res == NULL)
	{
		printf("NULL\n");
		return (0);
	}
	printf("\"%s\"\n", res);
	size = alloc_size(res);
	if (size == -1)
		printf("malloc : ce pointeur ne vient pas d'un malloc (chaine litterale ? tableau local ?)\n");
	else if (size >= 0 && (size_t)size < strlen(res) + 1)
		printf("malloc : %ld octets demandes, trop petit (il faut au moins %zu)\n", size, strlen(res) + 1);
	else
		printf("malloc : ok\n");
	if (size != -1)
		free(res);
	if (strcmp(s1, argv[1]) != 0 || strcmp(s2, argv[2]) != 0)
		printf("entree : MODIFIEE, s1 et s2 ne doivent pas changer\n");
	free(s1);
	free(s2);
	return (0);
}
