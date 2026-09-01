int	iswhitespace(char c)
{
	if ((c >= 9 && c <= 13) || (c == 32))
		return (1);
	return (0);
}

int	char_to_int(char c)
{
	return (c - '0');
}

int	isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;
	int	digit;

	i = 0;
	sign = 1;
	result = 0;
	while (iswhitespace(str[i]) == 1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * - 1;
		i++;
	}
	while (isdigit(str[i]) == 1)
	{
		digit = char_to_int(str[i]);
		result = result * 10 + digit;
		i++
	}
	return (result * sign);
}
