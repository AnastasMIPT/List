#include <stdio.h>
#include <cstdlib>
#include <assert.h>
#include <algorithm>

#define TEST(cond, FuncName, Num)                        \
    if (cond)                                            \
        printf ("%s() test failed %d\n", #FuncName, Num);\
    else                                                 \
        count++;                                         \


const int Empty = -1;
const int Poison = -3;

typedef int el_t;



template<typename Type>
class list {
    Type* data;
    int* next;
    int* prev;

    int head;
    int free;
    int tail;

    size_t size;
    size_t max_size;
    bool sorted;
    const static int DefaultSize = 50;

    void ListElementInit (int pos, Type data, int next, int prev);

public:

    list ();

    ~list ();

    int PushFront (Type value);

    int PushBack (Type value);

    int InsertAfter (int pos, Type value);

    int InsertBefore (int pos, Type value);

    int DeleteAfter (int pos);

    int DeleteBefore (int pos);

    int DeleteFront ();

    int DeleteBack ();

    int Delete (int pos);

    void SwapElements (int pos, int cur_el);

    int SearchElementByLogicNum (int num);

    void ListSort ();

    int Dump (int limit = DefaultSize, const char* str = "Information lst");

    void DrawDump (int limit = DefaultSize, FILE* f_out = fopen ("F:\\Graphs\\output.dot", "w"));

    friend struct list_testing;
};

struct list_testing {
    static bool TestDeleteFront ();

    static bool TestDeleteBack ();

    static bool TestPushFront ();

    static bool TestPushBack ();

    static bool TestDeleteBefore ();

    static bool TestSwapElements ();

    static bool TestDeleteAfter ();

    static bool Testing ();

    list_testing () = delete;

};

int main () {

    list<int> lst1;

    if (list_testing::Testing ()) printf ("ALL IS OK\n");

    lst1.InsertAfter (lst1.InsertAfter (lst1.InsertAfter (0, 76), 98), 67);

    lst1.PushFront (42);
    lst1.PushFront (88);
    lst1.Dump (20);
    //DeleteAfter(1);
    lst1.Delete (3);

    //Dump (20);
    //ListSort ();
    //int g = SearchElementByLogicNum (4);
    //SwapElements (2, 4);
    //Dump (20);
    //SwapElements (1, 5);
    lst1.Dump (20);

    //ListDistructor ();
    return 0;
}

/*! Функция, запускающая тестирующие функции
*
*	@return Успшно ли прошло тестирование
*
*/
bool list_testing::Testing () {
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
//    if (TestSwapElements ()) {
//        printf ("SwapElements (): OK\n");
//        col_OK++;
//    }

    return col_OK == 6;
}

template<typename Type>
int list<Type>::SearchElementByLogicNum (int num) {
    if (sorted) {
        return data[num];
    } else {
        int pos = head;
        for (int i = 1; i != num && i < size + 1; i++) {
            pos = next[pos];
        }
        return data[pos];
    }
}

template<typename Type>
int list<Type>::DeleteFront () {

    if (this == nullptr) {
        printf ("ERROR nullptr in DeleteFront\n");
        return 0;
    }

    sorted = false;

    int rezult = head;
    head = next[head];
    prev[rezult] = Empty;
    next[rezult] = free;
    data[rezult] = Poison;
    free = rezult;
    prev[head] = 0;
    size--;

    return rezult;
}

bool list_testing::TestDeleteFront () {

    list<int> lst1;

    int count = 0;

    lst1.head = 4;
    lst1.free = 1;
    lst1.size = 4;
    lst1.tail = 3;

    lst1.ListElementInit (1, -3, 6, -1);
    lst1.ListElementInit (2, 98, 5, 1);
    lst1.ListElementInit (3, 67, 0, 5);
    lst1.ListElementInit (4, 42, 2, 0);
    lst1.ListElementInit (5, 87, 3, 2);

    lst1.DeleteFront ();

    TEST (lst1.data[4] != Poison, DeleteFront, 1)
    TEST (lst1.next[4] != 1, DeleteFront, 2)
    TEST (lst1.size != 3, DeleteFront, 3)
    TEST (lst1.head != 2, DeleteFront, 4)
    TEST (lst1.prev[4] != Empty, DeleteFront, 5)
    TEST (lst1.prev[2] != 0, DeleteFront, 6)

    //ListDistructor ();

    return count == 6;
}

template<typename Type>
int list<Type>::DeleteBack () {

    if (this == nullptr) {
        printf ("ERROR nullptr in DeleteBack\n");
        return 0;
    }

    if (size == 0) {
        printf ("ERROR attempt delete empty element\n");
        return 0;
    }

    if (prev[tail] == 0) head = 0;

    sorted = false;

    next[prev[tail]] = 0;
    next[tail] = free;
    free = tail;
    tail = prev[tail];
    prev[free] = Empty;
    data[free] = Poison;

    size--;

    return free;
}

bool list_testing::TestDeleteBack () {

    list<int> lst1;

    int count = 0;

    lst1.head = 4;
    lst1.free = 6;
    lst1.size = 5;
    lst1.tail = 3;

    lst1.ListElementInit (1, 76, 2, 4);
    lst1.ListElementInit (2, 98, 5, 1);
    lst1.ListElementInit (3, 67, 0, 5);
    lst1.ListElementInit (4, 42, 1, 0);
    lst1.ListElementInit (5, 87, 3, 2);

    lst1.DeleteBack ();

    TEST (lst1.data[3] != Poison, DeleteBack, 1)
    TEST (lst1.next[3] != 6, DeleteBack, 2)
    TEST (lst1.size != 4, DeleteBack, 3)
    TEST (lst1.tail != 5, DeleteBack, 4)
    TEST (lst1.next[5] != 0, DeleteBack, 5)

    lst1.DeleteBack ();
    lst1.DeleteBack ();
    lst1.DeleteBack ();
    lst1.DeleteBack ();

    TEST (lst1.data[0] != 0, DeleteBack, 6)
    TEST (lst1.next[0] != 0, DeleteBack, 7)
    TEST (lst1.size != 0, DeleteBack, 8)
    TEST (lst1.tail != 0, DeleteBack, 9)
    TEST (lst1.prev[0] != 0, DeleteBack, 10)
    TEST (lst1.free != 4, DeleteBack, 11)
    TEST (lst1.next[1] != 2, DeleteBack, 12)
    TEST (lst1.prev[1] != -1, DeleteBack, 13)



    //ListDistructor ();

    return count == 13;
}

template<typename Type>
int list<Type>::DeleteBefore (int pos) {

    if (this == nullptr) {
        printf ("ERROR nullptr in DeleteBefore\n");
        return 0;
    }

    if (prev[pos] == Empty) {
        printf ("ERROR attempt to delete empty element\n");
        return 0;
    }

    if (prev[prev[pos]] != 0)
        return DeleteAfter (prev[prev[pos]]);

    return DeleteFront ();
}

template<typename Type>
void list<Type>::ListElementInit (int pos, Type data, int next, int prev) {

    this->data[pos] = data;
    this->next[pos] = next;
    this->prev[pos] = prev;
}

bool list_testing::TestDeleteBefore () {

    list<int> lst1;

    int count = 0;

    lst1.head = 4;
    lst1.free = 6;
    lst1.size = 5;
    lst1.tail = 3;

    lst1.ListElementInit (1, 76, 2, 4);
    lst1.ListElementInit (2, 98, 5, 1);
    lst1.ListElementInit (3, 67, 0, 5);
    lst1.ListElementInit (4, 42, 1, 0);
    lst1.ListElementInit (5, 87, 3, 2);

    lst1.DeleteBefore (2);

    TEST (lst1.data[1] != Poison, DeleteBefore, 1)
    TEST (lst1.next[1] != 6, DeleteBefore, 2)
    TEST (lst1.size != 4, DeleteBefore, 3)
    TEST (lst1.prev[1] != Empty, DeleteBefore, 4)
    TEST (lst1.free != 1, DeleteBefore, 5)

    lst1.DeleteBefore (2);

    TEST (lst1.data[4] != Poison, DeleteBefore, 6)
    TEST (lst1.next[4] != 1, DeleteBefore, 7)
    TEST (lst1.size != 3, DeleteBefore, 8)
    TEST (lst1.head != 2, DeleteBefore, 9)
    TEST (lst1.prev[4] != Empty, DeleteBefore, 10)
    TEST (lst1.prev[2] != 0, DeleteBefore, 11)

    //ListDistructor ();

    return count == 11;
}

template<typename Type>
int list<Type>::Delete (int pos) {

    if (this == nullptr) {
        printf ("ERROR nullptr in DeleteAfter\n");
        return 0;
    }
    if (prev[pos] == Empty) {
        printf ("ERROR attempt to delete empty element\n");
        return 0;
    }

    if (pos != tail) sorted = false;

    if (prev[pos] != 0)
        next[prev[pos]] = next[pos];
    else {
        head = next[head];
        prev[head] = 0;
    }

    if (next[pos] != 0)
        prev[next[pos]] = prev[pos];
    else {
        tail = prev[tail];
        next[tail] = 0;
    }
    data[pos] = Poison;
    next[pos] = free;
    prev[pos] = Empty;
    free = pos;

    size--;

    return pos;
}

template<typename Type>
int list<Type>::DeleteAfter (int pos) {

    if (this == nullptr) {
        printf ("ERROR nullptr in DeleteAfter\n");
        return 0;
    }

    if (next[pos] == 0 || prev[pos] == Empty) {
        printf ("ERROR attempt to delete empty element\n");
        return 0;
    }

    sorted = false;

    if (next[next[pos]] != 0) prev[next[next[pos]]] = pos;
    data[next[pos]] = Poison;
    prev[next[pos]] = Empty;
    int buf = next[next[pos]];
    next[next[pos]] = free;
    free = next[pos];
    next[pos] = buf;
    size--;

    if (next[pos] == 0) tail = pos;

    return free;
}

bool list_testing::TestDeleteAfter () {

    list<int> lst1;

    int count = 0;

    lst1.head = 4;
    lst1.free = 6;
    lst1.size = 5;
    lst1.tail = 3;

    lst1.ListElementInit (1, 76, 2, 4);
    lst1.ListElementInit (2, 98, 5, 1);
    lst1.ListElementInit (3, 67, 0, 5);
    lst1.ListElementInit (4, 42, 1, 0);
    lst1.ListElementInit (5, 87, 3, 2);

    lst1.DeleteAfter (5);

    TEST (lst1.data[3] != Poison, DeleteAfter, 1)
    TEST (lst1.next[3] != 6, DeleteAfter, 2)
    TEST (lst1.size != 4, DeleteAfter, 3)
    TEST (lst1.prev[3] != Empty, DeleteAfter, 4)
    TEST (lst1.prev[5] != 2, DeleteAfter, 5)
    TEST (lst1.next[5] != 0, DeleteAfter, 6)
    TEST (lst1.tail != 5, DeleteAfter, 7)
    TEST (lst1.free != 3, DeleteAfter, 8)

    lst1.DeleteAfter (1);

    TEST (lst1.free != 2, DeleteAfter, 9)
    TEST (lst1.next[1] != 5, DeleteAfter, 10)
    TEST (lst1.prev[2] != Empty, DeleteAfter, 11)
    TEST (lst1.next[2] != 3, DeleteAfter, 12)
    TEST (lst1.data[2] != Poison, DeleteAfter, 13)


    //ListDistructor ();

    return count == 13;
}

template<typename Type>
int list<Type>::InsertBefore (int pos, Type value) {

    if (this == nullptr) {
        printf ("ERROR nullptr in InsertBefore\n");
        return 0;
    }

    if (prev[pos] == Empty) {

        printf ("ERROR attempt to insert before empty element\n");
        return 0;

    }
    if (prev[pos] == 0) return PushFront (value);
    return InsertAfter (prev[pos], value);

}

template<typename Type>
void list<Type>::ListSort () {

    int cur_el = head;

    for (int pos = 1; pos < size + 1; pos++) {
        printf ("pos = %d , cur_el = %d\n", pos, cur_el);
        if (cur_el != pos && cur_el != 0) {
            SwapElements (pos, cur_el);
        }
        cur_el = next[pos];
        Dump (20);
    }

    sorted = true;
    tail = size;
}

template<typename Type>
void list<Type>::SwapElements (int pos, int cur_el) {

    int n_pos = pos;
    int n_cur_el = cur_el;
    //Swap (&data[pos], &data[cur_el]);
    std::swap (data[pos], data[cur_el]);


    if (next[pos] == cur_el || next[cur_el] == pos) {

        if (next[cur_el] == pos) {
            n_pos = cur_el;
            n_cur_el = pos;
        }

        next[prev[n_pos]] = n_cur_el;
        prev[n_cur_el] = prev[n_pos];

        next[n_pos] = next[n_cur_el];
        prev[next[n_cur_el]] = n_pos;

        prev[n_pos] = n_cur_el;
        next[n_cur_el] = n_pos;
    } else {
        next[prev[pos]] = cur_el;
        prev[next[pos]] = cur_el;

        next[prev[cur_el]] = pos;
        prev[next[cur_el]] = pos;

        //printf ("/n ^ data[pos] = %d, data[cur_el] = %d\n", next[pos], next[cur_el]);
        //Swap(&next[pos], &next[cur_el]);
        std::swap (next[pos], next[cur_el]);
        //printf ("/n ^ data[pos] = %d, data[cur_el] = %d\n", next[pos], next[cur_el]);
        std::swap (prev[pos], prev[cur_el]);

        //Swap(&prev[pos], &prev[cur_el]);
    }

    if (pos == head) {
        head = cur_el;
        next[0] = 0;
    } else if (cur_el == head) {
        next[0] = 0;
        head = pos;
    }
    if (pos == tail) {
        tail = cur_el;
        prev[0] = 0;
    } else if (cur_el == tail) {
        tail = pos;
        prev[0] = 0;
    }
    if (pos == free) {
        free = cur_el;
        prev[next[cur_el]] = -1;
    } else if (cur_el == free) {
        free = pos;
        prev[next[pos]] = -1;
    }
}

bool list_testing::TestSwapElements () {

    list<int> lst1;

    int count = 0;

    lst1.head = 5;
    lst1.free = 2;
    lst1.size = 4;
    lst1.tail = 3;

    lst1.ListElementInit (1, 76, 3, 4);
    lst1.ListElementInit (2, Poison, 6, Empty);
    lst1.ListElementInit (3, 67, 0, 1);
    lst1.ListElementInit (4, 42, 1, 5);
    lst1.ListElementInit (5, 88, 4, 0);

    lst1.SwapElements (2, 4);                          ///Swap with free
    lst1.Dump (20);

    TEST (lst1.prev[6] != Empty, SwapElements, 0)
    TEST (lst1.data[4] != Poison, SwapElements, 1)
    TEST (lst1.next[4] != 6, SwapElements, 2)
    TEST (lst1.data[2] != 42, SwapElements, 3)
    TEST (lst1.prev[4] != Empty, SwapElements, 4)
    TEST (lst1.free != 4, SwapElements, 5)
    TEST (lst1.prev[2] != 5, SwapElements, 6)
    TEST (lst1.next[2] != 1, SwapElements, 7)
    TEST (lst1.next[5] != 2, SwapElements, 8)
    TEST (lst1.prev[1] != 2, SwapElements, 9)

    lst1.ListElementInit (4, Poison, 6, Empty);
    lst1.ListElementInit (2, 42, 1, 5);
    lst1.free = 4;
    lst1.next[5] = 2;
    lst1.prev[1] = 2;

    lst1.SwapElements (1, 5);                  ///Swap with head
    TEST (lst1.data[1] != 88, SwapElements, 10)
    TEST (lst1.next[1] != 2, SwapElements, 11)
    TEST (lst1.prev[1] != 0, SwapElements, 12)
    TEST (lst1.data[5] != 76, SwapElements, 13)
    TEST (lst1.next[5] != 3, SwapElements, 14)
    TEST (lst1.prev[5] != 2, SwapElements, 15)
    TEST (lst1.head != 1, SwapElements, 16)
    TEST (lst1.prev[2] != 1, SwapElements, 17)
    TEST (lst1.next[2] != 5, SwapElements, 18)
    TEST (lst1.prev[3] != 5, SwapElements, 19)
    TEST (lst1.next[0] != 0, SwapElements, 20)

    printf ("count = %d \n", count);

    return count == 21;
}

template<typename Type>
list<Type>::list () : max_size (DefaultSize), free (1), head (0), size (0), sorted (true), tail (1) {

    data = new Type[DefaultSize];
    next = new int[DefaultSize];
    prev = new int[DefaultSize];

    for (int i = 1; i < DefaultSize; i++) {
        next[i] = i + 1;
    }

    for (int i = 1; i < DefaultSize; i++) {
        prev[i] = -1;
    }


    for (int i = 1; i < DefaultSize; i++) {
        data[i] = Poison;
    }
    next[0] = 0;
    prev[0] = 0;
    data[0] = 0;
}

template<typename Type>
list<Type>::~list () {

    delete[] (data);
    delete[] (next);
    delete[] (prev);
}

template<typename Type>
int list<Type>::InsertAfter (int pos, Type value) {

    if (this == nullptr) {
        printf ("ERROR nullptr in InsertAfter\n");
        return 0;
    }

    if (prev[pos] == Empty) {
        printf ("ERROR attempt to insert after empty element\n");
        return 0;
    }

    if (pos != tail) sorted = false;


    if (size == 0) return PushFront (value);

    size += 1;

    data[free] = value;
    int buf = free;
    free = next[free];

    next[buf] = next[pos];
    prev[buf] = pos;
    if (next[buf] != 0) prev[next[buf]] = buf;
    if (next[buf] == 0) tail = buf;
    next[pos] = buf;


    return buf;
}

bool list_testing::TestPushFront () {
    list<int> lst1;


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
    lst1.PushFront (12);

    TEST (lst1.data[2] != 12, PushFront, 1)
    TEST (lst1.next[2] != 1, PushFront, 2)
    TEST (lst1.size != 3, PushFront, 3)
    TEST (lst1.head != 2, PushFront, 4)

    lst1.PushFront (11);

    TEST (lst1.data[4] != 11, PushFront, 5)
    TEST (lst1.next[4] != 2, PushFront, 6)
    TEST (lst1.size != 4, PushFront, 7)
    TEST (lst1.head != 4, PushFront, 8)

    //ListDistructor ();

    list<int> lst2;
    //ListConstructor (&lst2);

    lst2.PushFront (25);

    TEST (lst2.data[1] != 25, PushFront, 9)
    TEST (lst2.next[1] != 0, PushFront, 10)
    TEST (lst2.size != 1, PushFront, 11)
    TEST (lst2.head != 1, PushFront, 12)

    //ListDistructor (&lst2);

    return count == 12;
}

template<typename Type>
int list<Type>::PushFront (Type value) {

    if (this == nullptr) {
        printf ("ERROR nullptr in PushFront\n");
        return 0;
    }
    sorted = false;

    size++;
    int pos = free;
    data[pos] = value;
    free = next[free];
    next[pos] = head;
    head = pos;
    if (next[pos] != 0) prev[next[pos]] = pos;
    prev[pos] = 0;
    return pos;
}

template<typename Type>
int list<Type>::PushBack (Type value) {

    if (this == nullptr) {
        printf ("ERROR nullptr in PushBack\n");
        return 0;
    }

    sorted = false;

    int pos = free;
    free = next[free];
    ListElementInit (pos, value, 0, tail);
    next[tail] = pos;
    tail = pos;
    size++;

    return pos;
}

bool list_testing::TestPushBack () {

    list<int> lst1;


    int count = 0;

    lst1.head = 4;
    lst1.free = 6;
    lst1.size = 5;
    lst1.tail = 3;

    lst1.ListElementInit (1, 76, 2, 4);
    lst1.ListElementInit (2, 98, 5, 1);
    lst1.ListElementInit (3, 67, 0, 5);
    lst1.ListElementInit (4, 42, 1, 0);
    lst1.ListElementInit (5, 87, 3, 2);

    lst1.PushBack (49);

    TEST (lst1.data[6] != 49, PushBack, 1)
    TEST (lst1.next[3] != 6, PushBack, 2)
    TEST (lst1.size != 6, PushBack, 3)
    TEST (lst1.prev[3] != 5, PushBack, 4)
    TEST (lst1.prev[6] != 3, PushBack, 5)
    TEST (lst1.next[6] != 0, PushBack, 6)
    TEST (lst1.tail != 6, PushBack, 7)
    TEST (lst1.free != 7, PushBack, 8)

    //ListDistructor ();

    return count == 8;
}

template<typename Type>
int list<Type>::Dump (int limit, const char* str) {

    if (this == nullptr) {
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
        printf ("[%2d]", data[i]);
    }
    printf ("\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", next[i]);
    }
    printf ("\n");
    for (int i = 0; i < limit; i++) {
        printf ("[%2d]", prev[i]);
    }
    printf ("\n");

    printf ("head = %d\n", head);
    printf ("free = %d\n", free);
    printf ("size = %ld\n", size);
    printf ("tail = %d\n", tail);
    printf ("sorted = %d\n", sorted);
    printf ("}\n");


    return 0;
}

template<typename Type>
void list<Type>::DrawDump (int limit, FILE* f_out) {
    assert (f_out);
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
             head);

//    for (int i = free; i < limit; i = next[i]) {
    //      fprintf (f_out, "EMPTY->A:i%d\n", i);
    // }
    fprintf (f_out, "EMPTY->A:%d1\n", free);
    fprintf (f_out, "A:%d2", free);

    for (int i = next[free]; i != 0 && i < limit; i = next[i]) {
        fprintf (f_out, "->A:%d1\n", i);\
        if (next[i] != 0) fprintf (f_out, "A:%d2", i);
    }

    fprintf (f_out, "\tlabel = \"\";\n"
                    "}\n"
                    "\n"
                    "subgraph List {\n"
                    "\tA [shape = \"record\", label = \"{{<01> | <02> } |<i0> %d |<val0> %d | {<03> | <04> }}",
             0, data[0]);

    for (int i = 1; i < limit; i++) {
        fprintf (f_out, "| {{<%d1> | <%d2> } |<i%d> %d |<val%d> %d | {<%d3> | <%d4> }}", i, i, i, i, i, data[i], i,
                 i);
    }
    fprintf (f_out, "\"]\n");
    fprintf (f_out, "    lebel = \"\";\n"
                    "}\n"
                    "\n"
                    "{rank = same; HEAD; EMPTY;}\n"
                    "{rank = same; A;}\n"
                    "subgraph Next {\n"
                    "\tedge[color=\"#ffcbdb\"]\n");
    fprintf (f_out, "A:%d2", head);

    for (int i = next[head]; i != 0; i = next[i]) {
        fprintf (f_out, "->A:%d1\n", i);\
        if (next[i] != 0) fprintf (f_out, "A:%d2", i);
    }

    fprintf (f_out, "\n\tlebel = \"\";\n"
                    "}\n"
                    "subgraph Prev {\n"
                    "\tedge[color=\"#98ff98\"]\n");

    //Prev
    fprintf (f_out, "A:%d3", tail);
    for (int i = prev[tail]; i != 0; i = prev[i]) {
        fprintf (f_out, "->A:%d4\n", i);
        if (prev[i] != 0) fprintf (f_out, "A:%d3", i);
    }


    fprintf (f_out, "\tlabel = \"\";\n"
                    "}\n"
                    "}\n");

    fclose (f_out);
}