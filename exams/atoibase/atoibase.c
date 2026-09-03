

char	*cpymaxbase(char *dest, char *src, int sizebase)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (i2 < sizebase && src[i2] != '\0')
		dest[i++] = src[i2++];
	dest[i] = '\0';
	return (dest);
}

int	getcharvalue(char c, char *dest)
{
	int	i;

	i = 0;
	if (c >= 'A' && c <= 'F')
		c = c + 32;
	while (dest[i] != '\0')
	{
		if (c == dest[i])
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int		i;
	int		result;
	int		sign;
	char	dest[100];
	char	*base;

	base = "0123456789abcdef";
	cpymaxbase(dest, base, str_base);
	i = 0;
	result = 0;
	sign = 1;
	if (str[i] == '-')
	{
		sign = sign * -1;
		i++;
	}
	while (getcharvalue(str[i], dest) != -1)
	{
		result = result * str_base + getcharvalue(str[i], dest);
		i++;
	}
	return (result * sign);
