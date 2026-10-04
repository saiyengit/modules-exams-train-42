/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_list.h"

void	ft_list_reverse(t_list **begin_list);

#define MAX_NODES 4096

#ifndef NO_WRAP

void		*__real_malloc(size_t size);
void		*__wrap_malloc(size_t size);

static int	g_tracking;
static int	g_calls;

void	*__wrap_malloc(size_t size)
{
	if (g_tracking)
		g_calls++;
	return (__real_malloc(size));
}

#else

static int	g_tracking;
static int	g_calls;

#endif

static t_list	*g_nodes[MAX_NODES];
static void		*g_datas[MAX_NODES];

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

static int	index_of(t_list *node, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (g_nodes[i] == node)
			return (i);
		i++;
	}
	return (-1);
}

static const char	*check(t_list *l, int n)
{
	int	k;
	int	j;
	int	data_moved;

	k = 0;
	data_moved = 0;
	while (l != NULL && k <= n)
	{
		j = index_of(l, n);
		if (j < 0)
			return ("un element inconnu est apparu dans la liste");
		if (l->data != g_datas[j])
			data_moved = 1;
		else if (j != n - 1 - k)
			return ("les elements ne sont pas dans l'ordre inverse");
		l = l->next;
		k++;
	}
	if (data_moved)
		return ("tu as deplace les data d'un element a l'autre : il faut rebrancher les next, pas echanger les data");
	if (k != n || l != NULL)
		return ("la liste n'a plus le bon nombre d'elements");
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_list		*begin;
	t_list		**last;
	const char	*why;
	int			n;
	int			i;

	setvbuf(stdout, NULL, _IOLBF, 0);
	n = argc - 1;
	if (n > MAX_NODES)
		return (1);
	begin = NULL;
	last = &begin;
	i = 0;
	while (i < n)
	{
		g_nodes[i] = malloc(sizeof(t_list));
		if (g_nodes[i] == NULL)
			return (1);
		g_nodes[i]->data = argv[i + 1];
		g_nodes[i]->next = NULL;
		g_datas[i] = argv[i + 1];
		*last = g_nodes[i];
		last = &g_nodes[i]->next;
		i++;
	}
	printf("avant : ");
	print_list(begin);
	printf("\napres : ");
	fflush(stdout);
	g_tracking = 1;
	ft_list_reverse(&begin);
	g_tracking = 0;
	print_list(begin);
	printf("\n");
	why = check(begin, n);
	if (why != NULL)
		printf("maillons : KO, %s\n", why);
	else
		printf("maillons : ok\n");
	if (g_calls > 0)
		printf("malloc : appele %d fois, interdit ici (Allowed functions est vide)\n", g_calls);
	i = 0;
	while (i < n)
		free(g_nodes[i++]);
	return (0);
}
