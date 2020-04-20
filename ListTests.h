//
// Created by anastas on 20.04.2020.
//

#include <cstdio>

#ifndef LIST_LISTTESTS_H
#define LIST_LISTTESTS_H

#endif //LIST_LISTTESTS_H

#define TEST(cond, FuncName, Num)                        \
    if (cond)                                            \
        printf ("%s() test failed %d\n", #FuncName, Num);\
    else                                                 \
        count++;                                         \



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
