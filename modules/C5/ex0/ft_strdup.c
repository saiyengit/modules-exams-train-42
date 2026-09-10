/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 15:36:34 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/09 15:27:35 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*cpy;
	int	i;
	int	ic;

	i = 0;
	ic = 0;
	cpy = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (cpy == 0)
		return (0);
	while (src[i])
		cpy[ic++] = src[i++];
	cpy[ic] = '\0';
	return (cpy);
}
