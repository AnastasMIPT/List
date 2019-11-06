#include <stdio.h>
#include <cstdlib>

const int Poison = -1;
const int DefaultSize = 50;

typedef int el_t;

struct list
{
    el_t*  data;
    int*   next;
    int*   prev;
    int    head;
    int    free;
    int    tail;
    size_t size;
    bool   sorted;
};

void ListConstructor (list* lst) {

    lst->data = (el_t*) calloc (DefaultSize, sizeof (el_t));
    lst->next = (int*)  calloc (DefaultSize, sizeof (int));
    lst->prev = (int*)  calloc (DefaultSize, sizeof (int));

    for (int i = 0; i < DefaultSize; i++) {
        lst->next[i] = -1;
    }

    lst->free = 1;
    lst->head = 1;
    lst->size = DefaultSize;
    lst->sorted = true;
    lst->tail = 1;

}
int main () {

    list lst1;
    ListConstructor (&lst1);

    return 0;
}