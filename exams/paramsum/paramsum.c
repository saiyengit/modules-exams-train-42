int	iwhitespace(char `c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	else
		return (0);
}

int	char_to_int(char c)
{
	return (c - '0');
}

int	iisdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int	atoi(const char *str)
{
	int	result;
	int	digit;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	result = 0;
	while (iwhitespace(str[i]) == 1)
	{
		i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-' )
			sign = sign * -1;
		i++;
	}
	while (iisdigit(str[i]) == 1)
	{
		digit = char_to_int(str[i]);
		result = result * 10 + digit;
		i++;
	}
	return (result * sign);
}

int	main(int argc, char **argv)
{
	int	somme;
	int	i;
	int	i2;

	i = 0;
	i2 = 1;
	somme = 0;
	if (argc > 1)
	{
		while (i < argc - 2)
		{
			somme = somme + atoi(argv[i2]);
			i++;
			i2++;
		}
	}
	putnbrpos(somme);
	return (somme);
}
