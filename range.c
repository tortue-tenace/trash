#include <stdio.h>
#include <stdlib.h>

int     *ft_range(int start, int end)
{
	int i = 0;
	int len = end - start + 1;
	int *res;

	if (end < start)
		return (NULL);
	res = (int *)malloc(sizeof(int) * len);
	if (!res)
		return (NULL);
	while (start <= end)
		res[i++] = start++;
	return (res);
}

int main(){
	int start = -2;
	int end = 5;
	int len = end - start + 1;
	int *res = ft_range(start, end);

	if (!res)
		return (1);
	for (int i = 0; i < len; i++)
		printf("%d ", res[i]);
	printf("\n");
	free(res);
	return (0);
}