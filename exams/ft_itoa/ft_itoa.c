#include <stdlib.h>

char	*ft_strrev(char *str)
{
	int		i;
	int		m;
	int		n;
	char	temp;

	i = 0;
	while (str[i])
		i++;
	i--;
	m = i;
	n = 0;
	while (m > n)
	{
		temp = str[m];
		str[m] = str[n];
		str[n] = temp;
		m--;
		n++;
	}
	return (str);
}

char	*ft_strdup(char *src)
{
	char	*cpy;
	int		srclen;
	int		i;

	if (src == NULL)
		return (NULL);
	srclen = 0;
	i = 0;
	while (src[srclen] != '\0')
		srclen++;
	cpy = malloc(sizeof(char) * (srclen + 1));
	if (cpy == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		cpy[i] = src[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_itoa(int nbr)
{
	int		is;
	int		tempnbr;
	int		neg;
	int		totaln;
	char	*str;

	is = 0;
	totaln = 1;
	neg = 0;
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
	str = malloc(sizeof(char) *(totaln + neg + 1));
	if (str == NULL)
		return NULL;
	while (totaln > 0)
	{
		str[is] = nbr % 10 + '0';
		nbr = nbr / 10;
		is++;
		totaln--;
	}
	if (neg == 1)
		str[is++] = '-';
	str[is] = '\0';
	ft_strrev(str);
	return (str);
}
