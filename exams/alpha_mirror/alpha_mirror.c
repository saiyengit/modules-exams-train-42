int	main(int argc, char **argv)
{
	int	i;
	int	i2;
	int	n;
	char 	base1[] = "abcdefghijklmnopqrstuvwxyz";
	char	base2[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (argc != 2)
	{
		ft_putchar('\n');
		return (0); 
	}
	i2 = 0;
	n = 25;
	while (i2 < 26)
	{
		base1[i2] = base1[i2] + n;
		i2 ++;
		n = n - 2;
	}
	i2 = 0;
	n = 25;
	while (i2 < 26)
	{
		base2[i2] = base2[i2] + n;
		i2 ++;
		n = n - 2;
	}
	i = 0;
	while (argv[1][i])
	{
		if (argv[1][i] >= 'a' && argv[1][i] <= 'z')
			argv[1][i] = base1[argv[1][i] - 'a']; //argv[1][i] = 'c' admettons, ca prend son nombreascii 99, donc en gros ca veut juste dire prend le c - a, 99 - 97m, 2, et affiche le donc base[2], quon a change taleure
		else if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			 argv[1][i] = base2[argv[1][i] - 'A'];
		ft_putchar(argv[1][i]);
		i++:
	}
	ft_putchar('\n');
	return 0;
}
