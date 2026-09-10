char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (dest[i])
		i++;
	while (src[i2])
	{
		dest[i++] = src[i2++];
	}
	dest[i] = '\0';
	return (dest);
}
