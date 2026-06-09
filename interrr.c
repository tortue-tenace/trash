#include <unistd.h>

int ft_strchr(char *str, char c){
	int	i = 0;
	while(str[i]){
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

#include <stdio.h>
int	main(int ac, char **av)
{
	int	i1 = 0;
	int	i2 = 0;
	int	k = 0;
	char	tab[200];
	if (ac != 3)
		return (1);
	while (av[1][i1])
	{
		if (av[2][i2] == av[1][i1] && av[2][i2])
		{
			// printf("c: %c	av2: %d	av1: %d \n", av[1][i1], i2, i1);
			if (ft_strchr(tab, av[1][i1]) == 0)
				tab[k++] = av[1][i1];
			i1++;
		}
		i2++;
	}

	write(1, &tab, k);
	write(1, "\n", 1);
}