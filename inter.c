#include <unistd.h>

int	main(int ac, char **av){
	if (ac != 2)
		return (0);
	int	i = 0;
	int flag = 0;
	char	*str;

	while (av[1][i] == ' ')
		i++;
	while (av[1][i] != '\0')
	{
		if (av[1][i] == ' ')
			flag = 1;
		if (flag == 1){
			write(1, " ", 1);
			while(av[1][i] == ' ' && av[1][i] != '\0')
				i++;
			flag = 0;
			if (av[1][i] == '\0')
				break;
		}
		write(1, &av[1][i], 1);
		i++;
	}
	write(1, "\n", 1);
}