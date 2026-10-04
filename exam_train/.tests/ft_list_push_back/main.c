/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_list.h"

void	ft_list_push_back(t_list **begin_list, void *data);

#define MAX_NODES 4096

#ifndef NO_WRAP

void			*__real_malloc(size_t size);
void			*__wrap_malloc(size_t size);

# define TRACK_MAX 100000

static void		*g_ptr[TRACK_MAX];
static size_t	g_size[TRACK_MAX];
static int		g_count;
static int		g_tracking;
static int		g_fail;

void	*__wrap_malloc(size_t size)
{
	void	*p;

	if (g_tracking && g_fail)
		return (NULL);
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
static int	g_fail;

static long	alloc_size(void *p)
{
	(void)p;
	return (-2);
}

#endif

static t_list	*g_nodes[MAX_NODES];
static void		*g_datas[MAX_NODES];
static int		g_n;

static void	print_list(t_list *l)
{
	int	first;
	int	guard;

	first = 1;
	guard = 0;
	printf("[");
	while (l != NULL && guard < MAX_NODES + 2)
	{
		if (!first)
			printf(", ");
		printf("\"%s\"", (char *)l->data);
		first = 0;
		l = l->next;
		guard++;
	}
	if (l != NULL)
		printf(", ... (la liste ne finit jamais : boucle ?)");
	printf("]");
}

/* la liste doit commencer par g_nodes[0..count-1], avec les memes data */
static const char	*check_prefix(t_list *l, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (l != g_nodes[i])
			return ("les elements deja presents ont bouge ou disparu");
		if (l->data != g_datas[i])
			return ("la data d'un element deja present a change");
		l = l->next;
		i++;
	}
	return (NULL);
}

static t_list	*last_node(t_list *l, int *guard)
{
	*guard = 0;
	while (l != NULL && l->next != NULL && *guard < MAX_NODES + 2)
	{
		l = l->next;
		(*guard)++;
	}
	return (l);
}

static void	push_failing(t_list **begin, char *data)
{
	const char	*why;
	t_list		*expected_last;
	int			guard;

	printf("push \"%s\" (malloc echoue) -> ", data);
	fflush(stdout);
#ifndef NO_WRAP
	g_tracking = 1;
	g_fail = 1;
	ft_list_push_back(begin, data);
	g_tracking = 0;
	g_fail = 0;
#endif
	print_list(*begin);
	printf("\n");
	why = check_prefix(*begin, g_n);
	expected_last = NULL;
	if (g_n > 0)
		expected_last = g_nodes[g_n - 1];
	if (why == NULL && last_node(*begin, &guard) != expected_last)
		why = "un element a ete ajoute alors que malloc a echoue";
	if (why != NULL)
		printf("  verif : KO, malloc a echoue donc la liste devait rester intacte (%s)\n", why);
	else
		printf("  verif : ok\n");
}

static int	push(t_list **begin, char *data)
{
	t_list		*l;
	const char	*why;
	int			guard;

	printf("push \"%s\" -> ", data);
	fflush(stdout);
	g_tracking = 1;
	ft_list_push_back(begin, data);
	g_tracking = 0;
	print_list(*begin);
	printf("\n");
	l = last_node(*begin, &guard);
	if (l == NULL)
	{
		printf("  verif : KO, la liste est vide apres le push\n");
		return (1);
	}
	if (guard >= MAX_NODES + 2 || g_n >= MAX_NODES)
	{
		printf("  verif : KO, liste sans fin\n");
		return (1);
	}
	why = check_prefix(*begin, g_n);
	if (why == NULL && g_n > 0 && l == g_nodes[g_n - 1])
		why = "aucun element n'a ete ajoute a la fin";
	if (why == NULL && l->data != data)
		why = "le nouvel element doit garder le pointeur data tel quel (pas une copie)";
	if (why == NULL && alloc_size(l) == -1)
		why = "le nouvel element ne vient pas d'un malloc fait dans ft_list_push_back";
	g_nodes[g_n] = l;
	g_datas[g_n] = l->data;
	g_n++;
	if (why != NULL)
	{
		printf("  verif : KO, %s\n", why);
		return (1);
	}
	printf("  verif : ok\n");
	return (0);
}

static void	add_initial(t_list **begin, char *data)
{
	t_list	*node;
	t_list	*l;

	node = malloc(sizeof(t_list));
	if (node == NULL)
		exit(1);
	node->data = data;
	node->next = NULL;
	if (*begin == NULL)
		*begin = node;
	else
	{
		l = *begin;
		while (l->next != NULL)
			l = l->next;
		l->next = node;
	}
	g_nodes[g_n] = node;
	g_datas[g_n] = data;
	g_n++;
}

int	main(int argc, char **argv)
{
	t_list	*begin;
	int		i;

	setvbuf(stdout, NULL, _IOLBF, 0);
	if (argc < 2 || argc > MAX_NODES)
		return (1);
	begin = NULL;
	i = 2;
	if (strcmp(argv[1], "new") != 0)
	{
		while (i < argc && strcmp(argv[i], "+") != 0)
			add_initial(&begin, argv[i++]);
		i++;
	}
	printf("depart : ");
	print_list(begin);
	printf("\n");
	if (strcmp(argv[1], "fail") == 0 && i < argc)
		push_failing(&begin, argv[i]);
	while (i < argc)
	{
		if (push(&begin, argv[i]))
			return (0);
		i++;
	}
	i = 0;
	while (i < g_n)
		free(g_nodes[i++]);
	return (0);
}
