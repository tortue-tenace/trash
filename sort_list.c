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
	int		data[] = {4, 7, 5, 1};
	t_list	*head = NULL;
	t_list	**cur = &head;

	for (int i = 0; i < 4; i++){
		*cur = ft_new_node(data[i]);
		cur = &(*cur)->next;
	}
	sort_list(head, ft_cmp);
	while (head != NULL){
		printf("%d\n", head->data);
		head = head->next;
	}
	return (0);
}