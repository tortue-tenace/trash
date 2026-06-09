#include <stdio.h>

void	sort_int_tab(int *tab, unsigned int size){
	int		swap;
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (j < size - 1){
		i = 0;
		while (i < size - 1 - j){
			if (tab[i] > tab[i + 1]){
				swap = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = swap;
			}
			i++;
		}
		j++;
	}
}

int	main(void){
	int		tab[] = {4, 6, 8, 1};
	unsigned int	i;

	sort_int_tab(tab, 4);
	i = 0;
	while (i < 4){
		printf("%d\n", tab[i]);
		i++;
	}
	return (0);
}