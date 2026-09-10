char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (dest[i])
		i++:
	while (i2 < nb && src[i2])
		dest[i++] = src[i2++];
	
	dest[i] = '\0';
	return dest;
}
