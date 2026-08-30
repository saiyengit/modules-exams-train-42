int	main(int argc, char **argv)
{
	int	i;
	int	i2;

	i = argc - 1;
	i2 = 0;
	if (argc < 2)
	{
		ft_putchar('\n');
		return (0);
	}
	ft_putstr(argv[i]);
	ft_putchar('\n');
	return (0);
}
