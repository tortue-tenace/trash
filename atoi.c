#include <unistd.h>

int	main(int ac, char **av){
	if (ac == 2)
	{
		int result = 0;
		int sign = 1;
		char	*str = av[1];

		while (*str == ' ' || (*str >= 9 && *str <= 13))
				str++;
		if (*str == '-')
			sign = -1;
		if (*str == '-' || *str == '+')
			str++;
		while (*str >= '0' && *str <= '9')
		{
			result = result * 10 + *str - '0';
			str++;
		}
		return (sign * result);
	}
}
