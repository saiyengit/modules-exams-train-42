/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ft_list.h"

int	ft_list_count_if(t_list *begin_list, int (*f)(void *));

#define MAX_NODES 1024

static int	f_strlen(void *data)
{
	return ((int)strlen((char *)data));
}

static int	f_upper(void *data)
{
	char	c;

	c = *(char *)data;
	return (c >= 'A' && c <= 'Z');
}

static int	f_digits(void *data)
{
	char	*s;

	s = (char *)data;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (-1);
}

static void	print_list(t_list *l)
{
	int	first;

	first = 1;
	printf("[");
	while (l != NULL)
	{
		if (!first)
			printf(", ");
		printf("\"%s\"", (char *)l->data);
		first = 0;
		l = l->next;
	}
	printf("]");
}

int	main(int argc, char **argv)
{
	t_list		*begin;
	t_list		**last;
	t_list		*nodes[MAX_NODES];
	t_list		*cur;
	int			(*f)(void *);
	const char	*desc;
	int			n;
	int			i;

	setvbuf(stdout, NULL, _IOLBF, 0);
	if (argc < 2 || argc - 2 > MAX_NODES)
		return (1);
	if (strcmp(argv[1], "strlen") == 0)
	{
		f = f_strlen;
		desc = "f renvoie strlen(data)";
	}
	else if (strcmp(argv[1], "upper") == 0)
	{
		f = f_upper;
		desc = "f renvoie 1 si data commence par une majuscule, sinon 0";
	}
	else
	{
		f = f_digits;
		desc = "f renvoie -1 si data ne contient que des chiffres, sinon 0";
	}
	n = argc - 2;
	begin = NULL;
	last = &begin;
	i = 0;
	while (i < n)
	{
		nodes[i] = malloc(sizeof(t_list));
		if (nodes[i] == NULL)
			return (1);
		nodes[i]->data = argv[i + 2];
		nodes[i]->next = NULL;
		*last = nodes[i];
		last = &nodes[i]->next;
		i++;
	}
	printf("liste : ");
	print_list(begin);
	printf("\n%s\n", desc);
	printf("ft_list_count_if = ");
	fflush(stdout);
	printf("%d\n", ft_list_count_if(begin, f));
	cur = begin;
	i = 0;
	while (i < n && cur == nodes[i] && cur->data == argv[i + 2])
	{
		cur = cur->next;
		i++;
	}
	if (i != n || cur != NULL)
		printf("liste : MODIFIEE par ta fonction (elle doit juste la parcourir)\n");
	i = 0;
	while (i < n)
		free(nodes[i++]);
	return (0);
}
