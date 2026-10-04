/* main de test - ne pas modifier */
#include <stdio.h>
#include <stdlib.h>

unsigned char	rotate_bits(unsigned char octet, int n);

int	main(int argc, char **argv)
{
	unsigned char	octet;
	unsigned char	res;
	int				n;
	int				repeat;
	int				i;

	setvbuf(stdout, NULL, _IOLBF, 0);
	if (argc != 3 && argc != 4)
		return (1);
	octet = (unsigned char)atoi(argv[1]);
	n = (int)strtol(argv[2], NULL, 10);
	repeat = 1;
	if (argc == 4)
		repeat = atoi(argv[3]);
	printf("rotate_bits(%d, %d) = ", octet, n);
	fflush(stdout);
	res = rotate_bits(octet, n);
	i = 1;
	while (i < repeat)
	{
		if (rotate_bits(octet, n) != res)
			res = 0;
		i++;
	}
	printf("%d", res);
	if (repeat > 1)
		printf("   [appel repete %d fois : ca doit rester instantane]", repeat);
	printf("\n");
	return (0);
}
