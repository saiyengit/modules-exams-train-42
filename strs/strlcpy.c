unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	int	i;
	int	srclen;

	srclen = 0;
	i = 0;
	if (size == 0)
		return srclen;
	while (src[srclen])
		srclen++;
	while (i < size- 1 && src[i])
	{
		dest[i] = src[i];
		i++:
	}
	dest[i] = '\0';
	return srclen;
}
