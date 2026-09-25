/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rosetta.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykadoun <ykadoun@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 18:17:34 by ykadoun           #+#    #+#             */
/*   Updated: 2026/09/13 18:17:36 by ykadoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROSETTA_H
# define ROSETTA_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(char *str);
int		ft_isdigit(char c);
int		ft_isspace(char c);
void	ft_putstr(char *str);
char	*ft_strdup(char *src);
int		ft_strcmp(char *s1, char *s2);
int		is_valid_number(char *str);
int		ft_strjoinlen(int size, char **strs, char *sep);
void	ft_strjoin_fill(char *res, int size, char **strs, char *sep);
char	*ft_strjoin(int size, char **strs, char *sep);
int		iswhitespace(char c);
int		char_to_int(char c);
int		isdigit(char c);
int		ft_atoi(const char *str);

#endif
