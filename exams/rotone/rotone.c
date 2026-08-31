#include <unistd.h>

void    ft_putchar(char c)
{
        write(1, &c, 1);
}

int     main(int argc, char **argv)
{
        int     i;

        i = 0;
        if (argc != 2)
        {
                ft_putchar('\n');
                return (0);
        }
	while (argv[1][i])
	{
		if ((argv[1][i] >= 'a' && argv[1][i] <= 'y') || (argv[1][i] >= 'A' && argv[1][i] <= 'Y'))
			argv[1][i] = argv[1][i] + 1;
		else if (argv[1][i] == 'z' || argv[1][i] == 'Z')
			argv[1][i] = argv[1][i] - 25;
		ftputchar(argv[1][i])
			i++
	}
	put\n
	ret
}
