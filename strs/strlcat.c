unsigned int ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	i2;
	unsigned int	destlen;
	unsigned int	srclen;

	i = 0;
	i2 = 0;
	destlen = 0;
	srclen = 0;
	while (dest[destlen])
		destlen++;
	while (src[srclen])
		srclen++;
	if (size <= destlen)
		return srclen + size;
	while (dest[i])
		i++;
	while (i < size - 1 && src[i2])
	{
		dest[i++] = src[i2++];
	}
	dest[i] = '\0';
	return destlen + srclen;
}
