#include <unistd.h>

void	ftputchar(char c)
{
	write(1, &c, 1);
}

int	main(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		ftputchar('\n');
		return (0);
	}
	while (argv[1][i])
	{
		if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
			argv[1][i] = argv[1][i] - 32;
		else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			argv[1][i] = argv[1][i] + 32;
		ftputchar(argv[1][i]);
		i++;
	}
        ftputchar('\n');
	return (0);
}
