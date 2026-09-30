#include <stdlib.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
	{
		i++;
	}
	return i;
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar('-');
	}

	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

int	main(int argc, char **argv)
{
	int a, b, c, d, e;

	if (argc != 4)
	{
		ft_putchar('\n');
		return (0);
	}
	if ((ft_strlen(argv[2]) != 1)
		|| (argv[2][0] != '+' && argv[2][0] != '*' && argv[2][0] != '%'
			&& argv[2][0] != '/' && argv[2][0] != '-'))
	{
		write(1, "Error\n", 6);
		return (0);
	}

	if ((atoi(argv[3]) == 0) && (argv[2][0] == '%' || argv[2][0] == '/'))
	{
		write (1, "Error\n", 6);
		return 0;
	}

	a = atoi(argv[1]) + atoi(argv[3]);
	b = atoi(argv[1]) - atoi(argv[3]);

	if (atoi(argv[3]) != 0)
	{
		c = atoi(argv[1]) % atoi(argv[3]);
		d = atoi(argv[1]) / atoi(argv[3]);
	}
	e = atoi(argv[1]) * atoi(argv[3]);

	if (argv[2][0] == '+')
		ft_putnbr(a);
	else if (argv[2][0] == '-')
		ft_putnbr(b);
	else if (argv[2][0] == '%')
		ft_putnbr(c);
	else if (argv[2][0] == '/')
		ft_putnbr(d);
	else if (argv[2][0] == '*')
		ft_putnbr(e);
	ft_putchar('\n');
	return (0);
	}

