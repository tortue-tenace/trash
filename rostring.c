#include <unistd.h>

void	ft_rm_space(char tab[]){
	int	i = 0;
	int flag = 0;

	while (tab[i] == ' ' || tab[i] == '\t')
		i++;
	while (tab[i]){
		if (tab[i] == ' ' || tab[i] == '\t')
			flag = 1;
		if (flag == 1){
			write(1, " ", 1);
			while (tab[i] == ' ' || tab[i] == '\t')
				i++;
			flag = 0;
		}
		write(1, &tab[i], 1);
		i++;
	}
}

int	main(int ac, char **av){
	int	i = 0;
	int	k = 0;
	int	start;
	int end;
	char tab[200]; 

	if (ac == 2){
		while (av[1][i] == ' ' || av[1][i] == '\t')
			i++;
		start = i;
		while (av[1][i] != ' ' && av[1][i] != '\t')
			i++;
		end = i;
		while (av[1][end])
			tab[k++] = av[1][end++];
		end = i;
		tab[k++] = ' ';
		while (start < end){
			tab[k++] = av[1][start++];
		}
		ft_rm_space(tab);
		write(1, "\n", 1);
		return (0);
	}
	return (1);
}