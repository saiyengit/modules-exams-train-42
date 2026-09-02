#include <stdio.h>

char    *ft_strrev(char *str)
{
	int	i;
	int	f;
	int	d;
	char	temp;

	i = 0;
	while (str[i])
		i++;
	i--;
	d = 0;
	f = i;
	while (f > d)
	{
		temp = str[f];
		str[f] = str[d];
		str[d] = temp;
		f--;
		d++;
	}
	return (str);
}

int	main(void)
{
	char str[] = "salut";
	printf("%s", ft_strrev(str));
	return 0;
}
