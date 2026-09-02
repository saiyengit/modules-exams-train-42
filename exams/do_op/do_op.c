#include <stdlib.h>
#include <stdio.h>

int	main(int argc, char **argv)
{	
	int	a;
	int	b;
	int	c;
	int	d;
	int	e;

	if (argc != 4)
	{
		printf("\n");
		return (0);
	}
	a = atoi(argv[1]) + atoi(argv[3]);
	b = atoi(argv[1]) - atoi(argv[3]);
	c = atoi(argv[1]) * atoi(argv[3]);
	if (atoi(argv[3]) != 0)
	{
		d = atoi(argv[1]) / atoi(argv[3]);
		e = atoi(argv[1]) % atoi(argv[3]);
	}
	if (argv[2][0] == '+')
		return printf("%d\n", a);
	else if (argv[2][0] == '-')
		return printf("%d\n", b);
	else if (argv[2][0] == '*')
		return printf("%d\n", c);
	else if (argv[2][0] == '/')
		return printf("%d\n", d);
	else if (argv[2][0] == '%')
		return printf("%d\n", e);
}
