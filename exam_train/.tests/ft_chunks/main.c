/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char	**ft_chunks(char *str, int n);

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

static int	points_into(char *p, char *str)
{
	if (str == NULL)
		return (0);
	return ((uintptr_t)p >= (uintptr_t)str
		&& (uintptr_t)p <= (uintptr_t)(str + strlen(str)));
}

static long	same_as_before(char **res, long i)
{
	long	j;

	j = 0;
	while (j < i)
	{
		if (res[j] == res[i])
			return (j);
		j++;
	}
	return (-1);
}

static void	check_and_free(char **res, char *str)
{
	long	i;
	int		errors;

	errors = 0;
	if (alloc_size(res) == -1)
	{
		printf("tableau : pas alloue avec malloc\n");
		errors++;
	}
	i = 0;
	while (res[i] != NULL)
	{
		if (same_as_before(res, i) >= 0)
		{
			printf("morceau %ld : meme pointeur que le morceau %ld (un seul buffer pour tout ?)\n",
				i, same_as_before(res, i));
			errors++;
		}
		else if (points_into(res[i], str))
		{
			printf("morceau %ld : pointe DANS str, ce n'est pas une copie\n", i);
			errors++;
		}
		else if (alloc_size(res[i]) == -1)
		{
			printf("morceau %ld : pas alloue avec malloc\n", i);
			errors++;
		}
		else
			free(res[i]);
		i++;
	}
	if (errors == 0)
		printf("copies : ok\n");
	if (alloc_size(res) != -1)
		free(res);
}

int	main(int argc, char **argv)
{
	char	*str;
	char	*save;
	char	**res;
	int		n;
	long	i;

	setvbuf(stdout, NULL, _IOLBF, 0);
	if (argc != 3)
		return (1);
	n = atoi(argv[2]);
	str = NULL;
	save = NULL;
	if (strcmp(argv[1], "--null") != 0)
	{
		str = dup_exact(argv[1]);
		save = dup_exact(argv[1]);
		printf("ft_chunks(\"%s\", %d) = ", str, n);
	}
	else
		printf("ft_chunks(NULL, %d) = ", n);
	fflush(stdout);
	g_tracking = 1;
	res = ft_chunks(str, n);
	g_tracking = 0;
	if (res == NULL)
		printf("NULL\n");
	else
	{
		printf("{");
		i = 0;
		while (res[i] != NULL)
		{
			printf("\"%s\", ", res[i]);
			i++;
		}
		printf("NULL}\n");
		check_and_free(res, str);
	}
	if (str != NULL && strcmp(str, save) != 0)
		printf("str : MODIFIEE -> \"%s\"\n", str);
	free(str);
	free(save);
	return (0);
}
