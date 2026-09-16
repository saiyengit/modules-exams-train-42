/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 14:51:02 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/07 16:02:22 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_ultimate_range(int **range, int min, int max)
{
	int	size;
	int	i;

	i = 0;
	size = max - min;
	if (min >= max)
	{
		*range = NULL;
		return (0);
	}
	*range = malloc(sizeof(int) * size);
	if (*range == 0)
		return (-1);
	while (max > min)
	{
		(*range)[i] = min;
		min++;
		i++;
	}
	return (size);
}

// int	main(void)
// {
// 	int	*range;
// 	int	size;
//
// 	size = ft_ultimate_range(&range, 0, 3);
// 	printf("%d: %d %d %d\n", size, range[0], range[1], range[2]);
// 	return (0);
// }
