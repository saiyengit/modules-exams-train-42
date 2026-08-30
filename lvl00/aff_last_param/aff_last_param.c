int	main(int argc, char **argv)
{
	int	i;

	i = argc - 1;
	if (argc < 2)
	{
		ft_putchar('\n');
		return (0);
	}
	ft_putstr(argv[i]);
	ft_putchar('\n');
	return (0);
}
