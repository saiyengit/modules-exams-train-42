int	spacetab(char c)
{
	if (c == ' ' || c == '\t')
		return 1;
	return 0;
}

char 	*cpy(char *dest, char *src)
{
	int	i;
	int	i2;
	
	i = 0;
	i2 = 0;
	while (spacetab(src[i]) == 1)
		i++;
	while (src[i] != '\0')
	{
		if (spacetab(src[i]) == 0)
		dest[i2++] = src[i++];
		if (src[i] != '/0')
		{
			if (spacetab(src[i]) == 1)
				dest[i2++] = src[i]
		}
		i++;
	}
	dest[i2] = '\0';
	return (dest);
}
