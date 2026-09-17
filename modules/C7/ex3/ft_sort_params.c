#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		ft_putchar(str[i++]);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

void	ft_swap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

int	main(int argc, char **argv)
{
	int	i;
	int	i2;

	i = 1;
	while (i < argc)
	{
		i2 = i + 1;
		while (i2 < argc)
		{
			if (ft_strcmp(argv[i], argv[i2]) > 0)
				ft_swap(&argv[i], &argv[i2]);
			i2++;
		}
		i++;
	}
	i = 1;
	while (i < argc)
	{
		ft_putstr(argv[i++]);
		ft_putchar('\n');
	}
	return (0);
}
