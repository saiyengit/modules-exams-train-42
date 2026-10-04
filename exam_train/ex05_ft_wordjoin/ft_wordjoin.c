#include <stdlib.h>

int	spacetab(char c)
{
	if (c == '\t' || c == ' ')
		return 1;
	return 0;
}

int	ft_debutword(char *str, int i)
{
	if ((i == 0 && spacetab(str[i]) == 0)
		|| (i > 0 && spacetab(str[i]) == 0 && spacetab(str[i - 1]) == 1))
		return 1;
	return 0;
}

int	ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return i;
}

int	is_one_or_less_word(char *str)
{
	int	total;
	int	i;

	i = 0;
	total = 0;
	while (str[i])
	{
		if (ft_debutword(str, i))
			total++;
		i++;
	}
	if (total == 1 || total == 0)
		return 1;
	else
		return 0;
}

char	*epur_str2(char *dest, char *src)
{
	int	i;
	int	debut;
	int	fin;
	int	i2;

	i = 0;
	i2 = 0;
	while (spacetab(src[i]))
		i++;
	if (src[i] == '\0')
	{
		dest[0] = '\0';
		return dest;
	}
	debut = i;
	while (src[i])
		i++;
	i--;
	while (spacetab(src[i]))
		i--;
	fin = i;
	while (debut <= fin)
	{
		dest[i2] = src[debut];
		debut++;
		i2++;
	}
	dest[i2] = '\0';
	return dest;
}

char	*ft_wordjoin(char *str, char *sep)
{
	char	dest[10000];
	char 	*cpy;
	int	i;
	int	totalsep;
	int	totalstr;
	int	ic;
	int	isep;


	epur_str2(dest, str);
	if (is_one_or_less_word(dest) == 1)
	{
		int	o;
		o = 0;
		cpy = malloc(sizeof(char) * (ft_strlen(dest) + 1));
		if (cpy == NULL)
			return NULL;
		while (dest[o])
		{
			cpy[o] = dest[o];
			o++;
		}
		cpy[o] = '\0';
		return cpy;
	}
	i = 0;
	totalstr = 0;
	while (dest[i])
	{
		if (spacetab(dest[i]) == 0)
			totalstr++;
		i++;
	}
	totalsep = 0;
	ic = 0;
	i = 0;
	while (dest[i])
	{
		if (ft_debutword(dest, i))
			totalsep++;
		i++;
	}
	totalsep--;
	cpy = malloc(sizeof(char) * (totalstr + (totalsep * ft_strlen(sep)) + 1));
	if (cpy == NULL)
		return NULL;
	i = 0;
	while (dest[i])
	{
		if (!spacetab(dest[i]))
		{
			cpy[ic] = dest[i];
			ic++;
			i++;
		}
		else
		{
			isep = 0;
			while(sep[isep])
			{
				cpy[ic++] = sep[isep++];
			}
			while (spacetab(dest[i]))
				i++;
		}
	}
	cpy[ic] = '\0';
	return cpy;
}
