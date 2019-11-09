#include <stdio.h>
#include <cstdlib>

#define TEST(cond, FuncName, Num)                        \
    if (cond)                                            \
        printf ("%s() test failed %d\n", #FuncName, Num);\
    else                                                 \
        count++;                                         \


const int Poison = -1;
const int Empty = -3;
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
    size_t max_size;
    bool   sorted;
};

void ListConstructor (list* lst);
int InsertAfter (list* lst, int pos, el_t value);
bool TestPushFront ();
void PushFront (list* lst, el_t value);
void Dump (list* lst, int limit = DefaultSize, char* str = "Information lst");
int main () {

//    list lst1;
//    ListConstructor (&lst1);
//
//    //Dump (&lst1, 20);
//
//    PushFront (&lst1, 10);
//    PushFront (&lst1, 23);
//    Dump (&lst1, 20);
//    lst1.data[1] = 15;
//    lst1.next[1] = 3;
//    lst1.next[2] = 4;
//    lst1.data[3] = 38;
//    lst1.next[3] = 0;
//    lst1.size = 2;
//    lst1.free = 2;
//    PushFront (&lst1, 12);
//    PushFront (&lst1, 11);
//    Dump (&lst1, 20);
    if (TestPushFront()) printf ("OK");

    return 0;
}

void ListConstructor (list* lst) {

    lst->data = (el_t*) calloc (DefaultSize, sizeof (el_t));
    lst->next = (int*)  calloc (DefaultSize, sizeof (int));
    lst->prev = (int*)  calloc (DefaultSize, sizeof (int));

    for (int i = 1; i < DefaultSize; i++) {
        lst->next[i] = i + 1;
    }

    for (int i = 1; i < DefaultSize; i++) {
        lst->data[i] = Empty;
    }

    lst->max_size = DefaultSize;
    lst->free   = 1;
    lst->head   = 0;
    lst->size   = 0;
    lst->sorted = true;
    lst->tail   = 1;

}

int InsertAfter (list* lst, int pos, el_t value) {
    el_t buf = lst->next[pos];
    lst->next[pos] = lst->free;
    lst->data[lst->free] = value;
    lst->free =buf;

    return lst->free;
}

bool TestPushFront () {
    list lst1;
    ListConstructor (&lst1);

    int count = 0;
    lst1.data[1] = 15;
    lst1.next[1] = 3;
    lst1.next[2] = 4;
    lst1.data[3] = 38;
    lst1.next[3] = 0;
    lst1.size = 2;
    lst1.free = 2;
    lst1.head = 1;
    PushFront (&lst1, 12);

    TEST (lst1.data[2] != 12, PushFront, 1)
    TEST (lst1.next[2] != 1, PushFront, 2)
    TEST (lst1.size != 3, PushFront, 3)
    TEST (lst1.head != 2, PushFront, 4)

    PushFront (&lst1, 11);

    TEST (lst1.data[4] != 11, PushFront, 5)
    TEST (lst1.next[4] != 2, PushFront, 6)
    TEST (lst1.size != 4, PushFront, 7)
    TEST (lst1.head != 4, PushFront, 8)

    //Dump (&lst1, 20);

    return count == 8;
}
void PushFront (list* lst, el_t value) {
    lst->size += 1;
    int pos = lst->free;
    lst->data[pos] = value;
    lst->free = lst->next[lst->free];
    lst->next[pos] = lst->head;
    lst->head = pos;
}

void Dump (list* lst, int limit, char* str) {
    printf ("LIST:\n"
            "{\n");
    for (int i = 0; i < limit; i++) {
        printf (" %2d ", i);
    }
    printf ("\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", lst->data[i]);
    }
    printf ("\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", lst->next[i]);
    }
    printf ("\n");
    printf ("head = %d\n", lst->head);
    printf ("free = %d\n", lst->free);
    printf ("size = %d\n", lst->size);
    printf ("}\n");
}
