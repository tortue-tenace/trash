#include <stdlib.h>

typedef struct      s_list
{
    struct s_list   *next;
    void            *data;
}                   t_list;

void    ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
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