/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 18:18:40 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/13 18:20:16 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

static void	select_args(int argc, char **argv, char **path, char **nb)
{
	if (argc == 3)
	{
		*path = argv[1];
		*nb = argv[2];
	}
	else
	{
		*path = "numbers.dict";
		*nb = argv[1];
	}
}

int	main(int argc, char **argv)
{
	char	*path;
	char	*nb;

	if (argc != 2 && argc != 3)
	{
		ft_putstr("Error\n");
		return (1);
	}
	select_args(argc, argv, &path, &nb);
	if (is_valid_number(nb) == 0)
	{
		ft_putstr("Error\n");
		return (1);
	}
	ft_putstr(path);
	ft_putstr("\n");
	return (0);
}
