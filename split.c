#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str){
	int	i = 0;

	while (str[i])
		i++;
	return (i);
}

int	main(int ac, char **av){
	int	i = 0;
	int	j = 0;
	int	k = 0;
	char	**split;

	if (ac == 2){
		split = malloc(sizeof(char*) * (ft_strlen(av[1]) + 1));
		if (!split)
			return (1);
		while (av[1][i]){
			k = 0;
			if (av[1][i] != '\n' && av[1][i] != ' ' && av[1][i] != '\t')
			{
				split[j] = malloc(sizeof(char) * (ft_strlen(av[1]) + 1));
				if (!split[j])
					return (1);
				while (av[1][i] && av[1][i] != '\n' && av[1][i] != ' ' && av[1][i] != '\t')
					split[j][k++] = av[1][i++];
				split[j][k] = '\0';
				j++;
			}
			while (av[1][i] == '\n' || av[1][i] == '\t' || av[1][i] == ' ')
				i++;
		}
		split[j] = NULL;
		i = 0;
		while (split[i])
		{
			printf("split[%d] = %s\n", i, split[i]);
			i++;
		}
		i = 0;
		while (split[i])
			free(split[i++]);
		free(split);
		return (0);
	}
	return (1);
}