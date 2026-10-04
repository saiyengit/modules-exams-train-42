#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t')
		return 1;
	return 0;
}

int	ft_debutword(char *str, int i)
{
	if ((i == 0 && ft_isspace(str[i]) == 0)
		|| (i > 0 && ft_isspace(str[i]) == 0 && ft_isspace(str[i - 1]) == 1))
		return 1;
	return 0;
}

int	ft_char_to_int(char c)
{
	return (c - '0');
}

int	ft_atoi(char *str)
{
	int	result;
	int	digit;
	int	sign;
	int	i;

	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	while (str[i])
	{
		digit = ft_char_to_int(str[i]);
		result = result * 10 + digit;
		i++;
	}
	return (result * sign);
}

int	main(int argc, char **argv)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	if (argc != 3 || ft_atoi(argv[2]) < 0)
	{
		ft_putchar('\n');
		return 0;
	}
	while (argv[1][i])
	{
		if (ft_debutword(argv[1], i) == 1)
		{
			total++;
			if (ft_atoi(argv[2]) == total)
			{
				while (argv[1][i] && ft_isspace(argv[1][i]) == 0)
				{
					ft_putchar(argv[1][i]);
					i++;
				}
			}
		}
		i++;
	}
	ft_putchar('\n');
	return 0;
}
