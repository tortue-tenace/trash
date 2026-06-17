#include <stdio.h>
#include <stdlib.h>

typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;

int ft_lst_add_new(t_list **lst, int data){
	t_list *head = *lst;
	t_list *new_node = malloc(sizeof(t_list));
	if (!new_node)
		return(1);
	int *data_ptr = malloc(sizeof(int));
	if (!data_ptr)
		return(1);
	*data_ptr = data;
	new_node->data = data_ptr;
	new_node->next = NULL;
	if (!*lst){
		*lst = new_node;
		return (0);
	}
	while (*lst && (*lst)->next){
		*lst = (*lst)->next;
	}
	(*lst)->next = new_node;
	*lst = head;
	return (0);
}

void    ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(void *, void *))
{
    t_list  *current;
    t_list  *to_free;

    if (!begin_list || !*begin_list)
        return ;
    while (*begin_list && cmp((*begin_list)->data, data_ref) == 0)
    {
        to_free = *begin_list;
        *begin_list = (*begin_list)->next;
        free(to_free);
    }
    current = *begin_list;
    while (current && current->next)
    {
        if (cmp(current->next->data, data_ref) == 0)
        {
            to_free = current->next;
            current->next = to_free->next;
            free(to_free);
        }
        else
            current = current->next;
    }
}
int cmp(void *lst, void *data_ref){
	if (*(int *)lst == *(int *)data_ref)
		return (0);
	return (1);
}
int main(){
	t_list *lst = NULL;
	int lol;

	lol = 12;
	ft_lst_add_new(&lst, 8);
	ft_lst_add_new(&lst, 86);
	ft_lst_add_new(&lst, 45);
	ft_lst_add_new(&lst, 4442);
	ft_lst_add_new(&lst, 12);
	ft_lst_add_new(&lst, 5888);
	t_list *head = lst;
	while (lst){
		printf("%d ", *(int *)lst->data);
		lst = lst->next;
	}
	lst = head;
	printf("-------------\n");
	ft_list_remove_if(&lst, &lol, cmp);
	while (lst){
		printf("%d ", *(int *)lst->data);
		lst = lst->next;
	}	
}