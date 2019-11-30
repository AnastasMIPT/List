#include <stdio.h>
#include <cstdlib>
#include <assert.h>

#define TEST(cond, FuncName, Num)                        \
    if (cond)                                            \
        printf ("%s() test failed %d\n", #FuncName, Num);\
    else                                                 \
        count++;                                         \


const int Empty = -1;
const int Poison = -3;
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
int InsertBefore (list* lst, int pos, el_t value);
int DeleteAfter (list* lst, int pos);
bool TestDeleteAfter ();
int DeleteBefore (list* lst, int pos);
bool TestDeleteBefore ();
int DeleteFront (list* lst);
bool TestDeleteFront();
int DeleteBack (list* lst);
bool TestDeleteBack ();
void ListElementInit (list* lst, int pos, el_t data, int next, int prev);
bool TestPushFront ();
int PushFront (list* lst, el_t value);
int PushBack (list* lst, el_t value);
bool TestPushBack ();
void ListSort (list* lst);
int Dump (list* lst, int limit = DefaultSize, char* str = "Information lst");
void Swap (int* a, int* b);
void SwapElements (list* lst, int pos, int cur_el);
int Testing ();

int main () {

    list lst1;
    ListConstructor (&lst1);


    if (Testing()) printf ("ALL IS OK\n");

    InsertAfter (&lst1,InsertAfter (&lst1, InsertAfter (&lst1, 0, 76), 98), 67);

    PushFront (&lst1, 42);
    PushFront(&lst1, 88);
    PushFront(&lst1, 88);
    PushFront(&lst1, 88);PushFront(&lst1, 88);PushFront(&lst1, 88);PushFront(&lst1, 88);PushFront(&lst1, 88);PushFront(&lst1, 88);PushFront(&lst1, 88);
    DeleteAfter(&lst1, 1);
    DeleteAfter(&lst1, 5);
    DeleteAfter(&lst1, 9);
    DeleteAfter(&lst1, 11);
    DeleteAfter(&lst1, 14);
    //ListSort (&lst1);
    Dump (&lst1, 30);

    ListDistructor (&lst1);
    return 0;
}

/*! Функция, запускающая тестирующие функции
*
*	@return Успшно ли прошло тестирование
*
*/
int Testing ()
{
    int col_OK = 0;

    if (TestPushFront ()) {
        printf ("PushFront (): OK\n");
        col_OK++;
    }
    if (TestPushBack ()) {
        printf ("PushBack (): OK\n");
        col_OK++;
    }
    if (TestDeleteFront ()) {
        printf ("DeleteFront (): OK\n");
        col_OK++;
    }
    if (TestDeleteBefore ()) {
        printf ("DeleteBefore (): OK\n");
        col_OK++;
    }
    if (TestDeleteAfter ()) {
        printf ("DeleteAfter (): OK\n");
        col_OK++;
    }
    if (TestDeleteBack ()) {
        printf ("DeleteBack (): OK\n");
        col_OK++;
    }


    return col_OK == 6;
}

int DeleteFront (list* lst) {

    if (lst == nullptr) {
        printf ("ERROR nullptr in DeleteFront\n");
        return 0;
    }

    lst->sorted = false;

    int rezult = lst->head;
    lst->head = lst->next[lst->head];
    lst->prev[rezult] = Empty;
    lst->next[rezult] = lst->free;
    lst->data[rezult] = Poison;
    lst->free = rezult;
    lst->prev[lst->head] = 0;
    lst->size--;

    return rezult;
}

bool TestDeleteFront () {

    list lst1;
    ListConstructor (&lst1);

    int count = 0;

    lst1.head = 4;
    lst1.free = 1;
    lst1.size = 4;
    lst1.tail = 3;

    ListElementInit (&lst1, 1, -3, 6, -1);
    ListElementInit (&lst1, 2, 98, 5, 1);
    ListElementInit (&lst1, 3, 67, 0, 5);
    ListElementInit (&lst1, 4, 42, 2, 0);
    ListElementInit (&lst1, 5, 87, 3, 2);

    DeleteFront (&lst1);

    TEST (lst1.data[4] != Poison, DeleteFront, 1)
    TEST (lst1.next[4] != 1, DeleteFront, 2)
    TEST (lst1.size != 3, DeleteFront, 3)
    TEST (lst1.head != 2, DeleteFront, 4)
    TEST (lst1.prev[4] != Empty, DeleteFront, 5)
    TEST (lst1.prev[2] != 0, DeleteFront, 6)

    ListDistructor (&lst1);

    return count == 6;
}

int DeleteBack (list* lst) {

    if (lst == nullptr) {
        printf ("ERROR nullptr in DeleteBack\n");
        return 0;
    }

    if (lst->size == 0) {
        printf ("ERROR attempt delete empty element\n");
        return 0;
    }

    if (lst->prev[lst->tail] == 0) lst->head = 0;

    lst->sorted = false;

    lst->next[lst->prev[lst->tail]] = 0;
    lst->next[lst->tail] = lst->free;
    lst->free = lst->tail;
    lst->tail = lst->prev[lst->tail];
    lst->prev[lst->free] = Empty;
    lst->data[lst->free] = Poison;

    lst->size--;

    return lst->free;
}

bool TestDeleteBack () {

    list lst1;
    ListConstructor (&lst1);

    int count = 0;

    lst1.head = 4;
    lst1.free = 6;
    lst1.size = 5;
    lst1.tail = 3;

    ListElementInit (&lst1, 1, 76, 2, 4);
    ListElementInit (&lst1, 2, 98, 5, 1);
    ListElementInit (&lst1, 3, 67, 0, 5);
    ListElementInit (&lst1, 4, 42, 1, 0);
    ListElementInit (&lst1, 5, 87, 3, 2);

    DeleteBack (&lst1);

    TEST (lst1.data[3] != Poison, DeleteBack, 1)
    TEST (lst1.next[3] != 6, DeleteBack, 2)
    TEST (lst1.size != 4, DeleteBack, 3)
    TEST (lst1.tail != 5, DeleteBack, 4)
    TEST (lst1.next[5] != 0, DeleteBack, 5)

    DeleteBack (&lst1);
    DeleteBack (&lst1);
    DeleteBack (&lst1);
    DeleteBack (&lst1);

    TEST (lst1.data[0] != 0, DeleteBack, 6)
    TEST (lst1.next[0] != 0, DeleteBack, 7)
    TEST (lst1.size != 0, DeleteBack, 8)
    TEST (lst1.tail != 0, DeleteBack, 9)
    TEST (lst1.prev[0] != 0, DeleteBack, 10)
    TEST (lst1.free != 4, DeleteBack, 11)
    TEST (lst1.next[1] != 2, DeleteBack, 12)
    TEST (lst1.prev[1] != -1, DeleteBack, 13)



    ListDistructor (&lst1);

    return count == 13;
}

int DeleteBefore (list* lst, int pos) {

    if (lst == nullptr) {
        printf ("ERROR nullptr in DeleteBefore\n");
        return 0;
    }

    if (lst->prev[pos] == Empty) {
        printf ("ERROR attempt to delete empty element\n");
        return 0;
    }

    if (lst->prev[lst->prev[pos]] != 0)
        return DeleteAfter (lst, lst->prev[lst->prev[pos]]);

    return DeleteFront (lst);
}

void ListElementInit (list* lst, int pos, el_t data, int next, int prev) {

    assert (lst);

    lst->data[pos] = data;
    lst->next[pos] = next;
    lst->prev[pos] = prev;
}

bool TestDeleteBefore () {

    list lst1;
    ListConstructor (&lst1);

    int count = 0;

    lst1.head = 4;
    lst1.free = 6;
    lst1.size = 5;
    lst1.tail = 3;

    ListElementInit (&lst1, 1, 76, 2, 4);
    ListElementInit (&lst1, 2, 98, 5, 1);
    ListElementInit (&lst1, 3, 67, 0, 5);
    ListElementInit (&lst1, 4, 42, 1, 0);
    ListElementInit (&lst1, 5, 87, 3, 2);

    DeleteBefore (&lst1, 2);

    TEST (lst1.data[1] != Poison, DeleteBefore, 1)
    TEST (lst1.next[1] != 6, DeleteBefore, 2)
    TEST (lst1.size != 4, DeleteBefore, 3)
    TEST (lst1.prev[1] != Empty, DeleteBefore, 4)
    TEST (lst1.free != 1, DeleteBefore, 5)

    DeleteBefore (&lst1, 2);

    TEST (lst1.data[4] != Poison, DeleteBefore, 6)
    TEST (lst1.next[4] != 1, DeleteBefore, 7)
    TEST (lst1.size != 3, DeleteBefore, 8)
    TEST (lst1.head != 2, DeleteBefore, 9)
    TEST (lst1.prev[4] != Empty, DeleteBefore, 10)
    TEST (lst1.prev[2] != 0, DeleteBefore, 11)

    ListDistructor (&lst1);

    return count == 11;
}

int DeleteAfter (list* lst, int pos) {

    if (lst == nullptr) {
        printf ("ERROR nullptr in DeleteAfter\n");
        return 0;
    }

    if (lst->next[pos] == 0 || lst->prev[pos] == Empty) {
        printf ("ERROR attempt to delete empty element\n");
        return 0;
    }

    lst->sorted = false;

    if (lst->next[lst->next[pos]] != 0) lst->prev[lst->next[lst->next[pos]]] = pos;
    lst->data[lst->next[pos]] = Poison;
    lst->prev[lst->next[pos]] = Empty;
    int buf = lst->next[lst->next[pos]];
    lst->next[lst->next[pos]] = lst->free;
    lst->free = lst->next[pos];
    lst->next[pos] = buf;
    lst->size--;

    if (lst->next[pos] == 0) lst->tail = pos;

    return lst->free;
}

bool TestDeleteAfter () {

    list lst1;
    ListConstructor (&lst1);

    int count = 0;

    lst1.head = 4;
    lst1.free = 6;
    lst1.size = 5;
    lst1.tail = 3;

    ListElementInit (&lst1, 1, 76, 2, 4);
    ListElementInit (&lst1, 2, 98, 5, 1);
    ListElementInit (&lst1, 3, 67, 0, 5);
    ListElementInit (&lst1, 4, 42, 1, 0);
    ListElementInit (&lst1, 5, 87, 3, 2);

    DeleteAfter (&lst1, 5);

    TEST (lst1.data[3] != Poison, DeleteAfter, 1)
    TEST (lst1.next[3] != 6, DeleteAfter, 2)
    TEST (lst1.size != 4, DeleteAfter, 3)
    TEST (lst1.prev[3] != Empty, DeleteAfter, 4)
    TEST (lst1.prev[5] != 2, DeleteAfter, 5)
    TEST (lst1.next[5] != 0, DeleteAfter, 6)
    TEST (lst1.tail != 5, DeleteAfter, 7)
    TEST (lst1.free != 3, DeleteAfter, 8)

    DeleteAfter (&lst1, 1);

    TEST (lst1.free != 2, DeleteAfter, 9)
    TEST (lst1.next[1] != 5, DeleteAfter, 10)
    TEST (lst1.prev[2] != Empty, DeleteAfter, 11)
    TEST (lst1.next[2] != 3, DeleteAfter, 12)
    TEST (lst1.data[2] != Poison, DeleteAfter, 13)


    ListDistructor (&lst1);

    return count == 13;
}


int InsertBefore (list* lst, int pos, el_t value) {

    if (lst == nullptr) {
        printf ("ERROR nullptr in InsertBefore\n");
        return 0;
    }

    if (lst->prev[pos] == Empty) {

        printf ("ERROR attempt to insert before empty element\n");
        return 0;

    }
    if (lst->prev[pos] == 0) return PushFront (lst, value);
    return InsertAfter (lst, lst->prev[pos], value);

}

void ListSort (list* lst) {

    int cur_el = lst->head;

    lst->head = 1;
    for (int pos = 1; pos < lst->size + 1; pos++) {
        if (cur_el != pos && cur_el != 0) {
            Swap (&lst->data[pos], &lst->data[cur_el]);
            int buf = lst->next[pos];

            Swap (&lst->next[pos], &lst->prev[pos]);
            Swap (&lst->next[cur_el], &lst->prev[cur_el]);
            Swap (&lst->prev[pos], &lst->next[cur_el]);

            lst->prev[buf] = cur_el;
            if (pos > 1) lst->next[pos - 1] = pos;
            cur_el = lst->next[pos];
        }
        Dump (lst, 20);
    }

    lst->sorted = true;
    lst->tail = lst->size;
}
void SwapElements (list* lst, int pos, int cur_el) {

}

void Swap (int* a, int* b) {
    int buf = *a;
    *a = *b;
    *b = buf;
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

    assert (lst);

    free (lst->data);
    free (lst->next);
    free (lst->prev);
}

int InsertAfter (list* lst, int pos, el_t value) {

    if (lst == nullptr) {
        printf ("ERROR nullptr in InsertAfter\n");
        return 0;
    }

    if (lst->prev[pos] == Empty) {
        printf ("ERROR attempt to insert after empty element\n");
        return 0;
    }

    lst->sorted = false;
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
    lst1.prev[1] = 0;
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

    if (lst == nullptr) {
        printf ("ERROR nullptr in PushFront\n");
        return 0;
    }
    lst->sorted = false;

    lst->size ++;
    int pos = lst->free;
    lst->data[pos] = value;
    lst->free = lst->next[lst->free];
    lst->next[pos] = lst->head;
    lst->head = pos;
    if (lst->next[pos] != 0) lst->prev[lst->next[pos]] = pos;
    lst->prev[pos] = 0;
    return pos;
}

int PushBack (list* lst, el_t value) {

    if (lst == nullptr) {
        printf ("ERROR nullptr in PushBack\n");
        return 0;
    }

    lst->sorted = false;

    int pos = lst->free;
    lst->free = lst->next[lst->free];
    ListElementInit (lst, pos, value, 0, lst->tail);
    lst->next[lst->tail] = pos;
    lst->tail = pos;
    lst->size++;

    return pos;
}

bool TestPushBack () {

    list lst1;
    ListConstructor (&lst1);

    int count = 0;

    lst1.head = 4;
    lst1.free = 6;
    lst1.size = 5;
    lst1.tail = 3;

    ListElementInit (&lst1, 1, 76, 2, 4);
    ListElementInit (&lst1, 2, 98, 5, 1);
    ListElementInit (&lst1, 3, 67, 0, 5);
    ListElementInit (&lst1, 4, 42, 1, 0);
    ListElementInit (&lst1, 5, 87, 3, 2);

    PushBack (&lst1, 49);

    TEST (lst1.data[6] != 49, PushBack, 1)
    TEST (lst1.next[3] != 6, PushBack, 2)
    TEST (lst1.size != 6, PushBack, 3)
    TEST (lst1.prev[3] != 5, PushBack, 4)
    TEST (lst1.prev[6] != 3, PushBack, 5)
    TEST (lst1.next[6] != 0, PushBack, 6)
    TEST (lst1.tail != 6, PushBack, 7)
    TEST (lst1.free != 7, PushBack, 8)

    ListDistructor (&lst1);

    return count == 8;
}

int Dump (list* lst, int limit, char* str) {

    if (lst == nullptr) {
        printf ("ERROR nullptr in DeleteBefore\n");
        return 1;
    }

    printf ("%s\n", str);

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

    return 0;
}
