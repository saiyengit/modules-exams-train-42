#include <unistd.h>

int	count_visible(int tab[4])
{
	int	max;
	int	compteur;
	int	i2;

	max = 0;
	compteur = 0; // cb dimmeubles visible du cote donne
	i = 0;
	while (i < 4)
	{
		if (tab[i] > max)
		{
			max = tab[i];
			compteur++;
		}
		i++;
	}
	return (compteur);
}


int	main(int argc, char **argv)
{
	int	valeurs[16]; //les indices de visibilite, les argu, correspondant a col1up etc
	int	grille[4][4]; 
	int	i;
	int	i2;
	int	l;
	int	c;

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	i = 0;
	i2 = 0;
	while (argv[1][i] != '\0')
	{
		if (argv[1][i] >= '1' && argv[1][i] <= '4')
		{
			if (i2 >= 16)
			{
				write(1, "Error\n", 6);
				return (0);
			}
			valeurs[i2] = argv[1][i] - '0';
			i2++;
		}
		else if (argv[1][i] != ' ')
		{
			write(1, "Error\n", 6);
			return (0);
		}
		i++;
	}
	if (i2 != 16)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	l = 0;
	while (l < 4)
	{
		c = 0;
		while (c < 4)
		{
			grille[l][c] = 0;
			c++;
		}
		l++;
	} //ini toutes grilles a 0 pour eviter valeur aleatoire et dysfonctionnement

