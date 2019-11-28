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
void ListDistructor (list* lst);
int InsertAfter (list* lst, int pos, el_t value);
bool TestPushFront ();
int PushFront (list* lst, el_t value);
void Dump (list* lst, int limit = DefaultSize, char* str = "Information lst");

int main () {

    list lst1;
    ListConstructor (&lst1);

    InsertAfter (&lst1,InsertAfter (&lst1, InsertAfter (&lst1, 2, 76), 98), 67);
    int h = PushFront (&lst1, 25);
    InsertAfter (&lst1, h, 78);
    PushFront (&lst1, 35);
    PushFront (&lst1, 42);
    PushFront (&lst1, 42);
    PushFront (&lst1, 42);
    PushFront (&lst1, 42);
    InsertAfter (&lst1, PushFront (&lst1, 35), 22);
    InsertAfter (&lst1, PushFront (&lst1, 35), 22);
    InsertAfter (&lst1, PushFront (&lst1, 35), 22);
    Dump (&lst1, 20);
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
        lst->prev[i] = -1;
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

void ListDistructor (list* lst) {

    free (lst->data);
    free (lst->next);
    free (lst->prev);
}

int InsertAfter (list* lst, int pos, el_t value) {

    if (lst->size == 0) return PushFront (lst, value);

    lst->size += 1;

    lst->data[lst->free] = value;
    int buf = lst->free;
    lst->free = lst->next[lst->free];

    lst->next[buf] = lst->next[pos];
    lst->prev[buf] = pos;
    if (lst->next[buf] != 0) lst->prev[lst->next[buf]] = buf;
    if (lst->next[buf] == 0) lst->tail = buf;
    lst->next[pos] = buf;


    return buf;
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

    ListDistructor (&lst1);

    list lst2;
    ListConstructor (&lst2);

    PushFront (&lst2, 25);

    TEST (lst2.data[1] != 25, PushFront, 9)
    TEST (lst2.next[1] != 0, PushFront, 10)
    TEST (lst2.size != 1, PushFront, 11)
    TEST (lst2.head != 1, PushFront, 12)

    ListDistructor (&lst2);

    return count == 12;
}

int PushFront (list* lst, el_t value) {

    lst->size += 1;
    int pos = lst->free;
    lst->data[pos] = value;
    lst->free = lst->next[lst->free];
    lst->next[pos] = lst->head;
    lst->head = pos;
    if (lst->next[pos] != 0) lst->prev[lst->next[pos]] = pos;
    lst->prev[pos] = 0;
    return pos;
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
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", lst->prev[i]);
    }
    printf ("\n");

    printf ("head = %d\n", lst->head);
    printf ("free = %d\n", lst->free);
    printf ("size = %d\n", lst->size);
    printf ("tail = %d\n", lst->tail);
    printf ("sorted = %d\n", lst->sorted);
    printf ("}\n");

    FILE* f_out = fopen ("F:\\Graphs\\output.dot", "w");
    fprintf (f_out, "digraph G {\n"
                    "ranksep = 1.8;\n"
                    "subgraph Head {\n"
                    "\tHEAD [label = \"head\"]\n"
                    "\tedge[color=\"Orange\"]\n"
                    "HEAD->A:%d1\n"
                    "\tlabel = \"\";\n"
                    "}\n"
                    "subgraph Empty {\n"
                    "\tEMPTY [label = \"empty\"]\n"
                    "\tedge [color=\"gray\", arrowsize=\"0.5\", penwidth=\"1\", constrain = \"false\", weigth = \"0.1\"];\n",
                    lst->head);

    for (int i = lst->free; i < limit; i = lst->next[i]) {
        fprintf (f_out, "EMPTY->A:i%d\n", i);
    }

    fprintf (f_out,"\tlabel = \"\";\n"
                   "}\n"
                   "\n"
                   "subgraph List {\n"
                   "\tA [shape = \"record\", label = \"{{<01> | <02> } |<i0> %d |<val0> %d | {<03> | <04> }}",
                   0, lst->data[0]);

    for (int i = 1; i < limit; i++) {
        fprintf (f_out,"| {{<%d1> | <%d2> } |<i%d> %d |<val%d> %d | {<%d3> | <%d4> }}", i, i, i, i, i, lst->data[i], i, i);
    }
    fprintf (f_out, "\"]\n");
    fprintf (f_out, "    lebel = \"\";\n"
                    "}\n"
                    "\n"
                    "{rank = same; HEAD; EMPTY;}\n"
                    "{rank = same; A;}\n"
                    "subgraph Next {\n"
                    "\tedge[color=\"#ffcbdb\"]\n");
    fprintf (f_out, "A:%d2", lst->head);

    for (int i = lst->next[lst->head]; i != 0 ; i = lst->next[i]) {
        fprintf (f_out, "->A:%d1\n", i);\
        if (lst->next[i] != 0) fprintf (f_out, "A:%d2", i);
    }

    fprintf (f_out, "\n\tlebel = \"\";\n"
                    "}\n"
                    "subgraph Prev {\n"
                    "\tedge[color=\"#98ff98\"]\n");

    //Prev
    fprintf (f_out, "A:%d3", lst->tail);
    for (int i = lst->prev[lst->tail]; i != 0 ; i = lst->prev[i]) {
        fprintf (f_out, "->A:%d4\n", i);
        if (lst->prev[i] != 0) fprintf (f_out, "A:%d3", i);
    }


    fprintf (f_out, "\tlabel = \"\";\n"
                    "}\n"
                    "}\n");

    fclose (f_out);
}
