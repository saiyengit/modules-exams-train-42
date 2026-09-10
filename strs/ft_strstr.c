char 	*ft_strstr(char *str, char *tofind)
{
	int	i;
	int	i2;

	if (tofind[0] == '\0')
		return str;
	i = 0;
	while (str[i])
	{
		i2 = 0;
		while (str[i + i2] == tofind[i2])
		{
			i2++;
			if (tofind[i2] == '\0')
				return (str + i);
		}
		i++;
	}
	return NULL;
}
