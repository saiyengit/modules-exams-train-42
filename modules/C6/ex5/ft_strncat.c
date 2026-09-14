/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/14 19:00:24 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/14 19:05:21 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	while (dest[i])
		i++;
	while (i2 < nb && src[i2])
		dest[i++] = src[i2++];
	dest[i] = '\0';
	return (dest);
}
