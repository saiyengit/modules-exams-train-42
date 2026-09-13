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

#endif
