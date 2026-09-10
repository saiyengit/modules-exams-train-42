char	*itoa(int nbr)
{
	int	is;
	int	tempnbr;
	char	*str;
	int	totaln;
	int	neg;

	totaln = 1;
	neg = 0;
	is = 0;
	if (nbr == -2147483648)
		return (ft_strdup("-2147483648"));
	if (nbr < 0)
	{
		nbr = -nbr;
		neg = 1;
	}
	tempnbr = nbr;
	while (tempnbr >= 10)
	{
		tempnbr = tempnbr / 10;
		totaln++;
	}
	str = malloc(sizeof(char) * (totaln + neg + 1));
	if (str == 0)
		return (NULL);
	while (is < totaln)
	{
		str[is] = nbr % 10 + '0';
		nbr = nbr / 10;
		is++;
	}
	if (neg == 1)
		str[is++] = '-';
	str[is] = '\0';
	ft_strrev(str);
	return str;
}
