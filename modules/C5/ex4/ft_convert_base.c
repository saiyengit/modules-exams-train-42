#include <stdlib.h>

int	allbasevalid(char *base_from, char *base_to);
int	ft_atoi_base(char *str, char *base);

char	*itoa(int nbr)
{
	char	*str;
	int	is;
	int	totaln;
	int	neg;
	int	tempnbr;

	totaln = 1;
	neg = 0;
	if (nbr == INT_MIN)
		return (ft_strdup("INT_MIN"));
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
		return NULL;
	while (is < totaln)
	{
		str[is++] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	if (neg == 1)
		str[is++] = '-';
	str[is] = '\0';
	ft_strrev(str[is]);
	return str;
}
