#include <stdlib.h>

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

int     ft_doublon_base(char *base)
{
        int     i;
        int     i2;

        i = 0;
        i2 = 0;
        while (base[i] != '\0')
        {
                i2 = i + 1;
                while (base[i2] != '\0')
                {
                        if (base[i2] == base[i])
                                return (0);
                        i2++;
                }
                i++;
        }
        return (1);
}

int     ft_is_base_valid(char *base)
{
        int     i;

        i = 0;
        if (base[0] == '\0' || base[1] == '\0')
                return (0);
        while (base[i] != '\0')
        {
                if ((base[i] >= 9 && base[i] <= 13) || (base[i] == 32)
                        || (base[i] == '-') || (base[i] == '+'))
                        return (0);
                i++;
        }
        i = 0;
        if (ft_doublon_base(base) == 0)
                return (0);
        return (1);
}

char	*ft_itoa_base(long nbr, char *base)
{
	int		is;
	long		tempnbr;
	int		neg;
	int		totaln;
	char	*str;
	int	baselen;

	if (ft_is_base_valid(base) == 0)
		return (NULL);
	baselen = 0;
	while (base[baselen])
		baselen++;
	neg = 0;
	if (nbr < 0)
	{
		neg = 1;
		nbr = -nbr;
	}
	is = 0;
	tempnbr = nbr;
	totaln = 1;
	while (tempnbr >= baselen)
	{
		tempnbr = tempnbr / baselen;
		totaln++;
	}
	str = malloc(sizeof(char) * (totaln + neg + 1));
	if (str == NULL)
		return (NULL);
	while (totaln > 0)
	{
		str[is] = base[nbr % baselen];
		nbr = nbr / baselen;
		totaln--;
		is++;
	}
	if (neg == 1)
		str[is++] = '-';
	str[is] = '\0';
	ft_strrev(str);
	return (str);
}
