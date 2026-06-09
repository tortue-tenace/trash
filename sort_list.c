#include <stdio.h>
#include <stdlib.h>

typedef struct s_list
{
	int				data;
	struct s_list	*next;
}	t_list;

t_list	*sort_list(t_list *lst, int (*cmp)(int, int)){
	int	swap;
	t_list *start;

	start = lst;
	while (lst != NULL && lst->next != NULL){
		if (cmp(lst->data, lst->next->data)){
			swap = lst->data;
			lst->data = lst->next->data;
			lst->next->data = swap;
			lst = start;
		}
		else
			lst = lst->next;
	}
	return (start);
}

t_list	*ft_new_node(int data){
	t_list	*node;

	node = malloc(sizeof(t_list));
	node->data = data;
	node->next = NULL;
	return (node);
}

int	ft_cmp(int a, int b){
	return (a >= b);
}

int	main(void){
	t_list *try;
	try = ft_new_node(4);
	try->next = ft_new_node(7);
	try->next->next = ft_new_node(5);
	try->next->next->next = ft_new_node(1);

	sort_list(try, ft_cmp);
	while (try != NULL){
		printf("%d\n", try->data);
		try = try->next;
	}
	return (0);
}