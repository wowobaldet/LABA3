#define BOOST_TEST_MODULE AllTests
#include <chrono>
#include <boost/test/included/unit_test.hpp>
#include "Header.h"
#include "stack.cpp"
#include "queue.cpp"
#include "massive.cpp"
#include "Hash.cpp"
#include "Tree.cpp"
#include "ListS.cpp"
#include "ListD.cpp"

template<typename Func>
void runBenchmark(const string& name, Func func) {
    auto start = chrono::high_resolution_clock::now();
    func();
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Benchmark " << name << " took " << duration << " microseconds.\n";
}
// Тесты для стека
BOOST_AUTO_TEST_CASE(test_push_stack) {
    Stk stack;
    stack.SPUSH("Alice");
    
    BOOST_REQUIRE_EQUAL(!stack.is_empty(),true);  
}
BOOST_AUTO_TEST_CASE(test_pop_stack) {
    Stk stack;
    stack.SPUSH("Alice");
    stack.SPUSH("Bob");
    stack.SPOP();
    BOOST_REQUIRE_EQUAL(!stack.is_empty(),true);
    stack.SPOP();  
    BOOST_REQUIRE_EQUAL(stack.is_empty(),true);
    stack.SPOP();
}
BOOST_AUTO_TEST_CASE(test_print_stack) {
    Stk stack;
    BOOST_REQUIRE_EQUAL(!stack.printStack(),true);
    stack.SPUSH("1");
    BOOST_REQUIRE_EQUAL(stack.printStack(),true);

}
BOOST_AUTO_TEST_CASE(test_empty_stack) {
    Stk stack;
    BOOST_REQUIRE_EQUAL(stack.is_empty(),true);
}
BOOST_AUTO_TEST_CASE(BenchmarkStackPushPop) {
    Stk stack;
    runBenchmark("Stack Push/Pop", [&stack]() {
        for (int i = 0; i < 100; ++i) {
            stack.SPUSH("item");
            stack.SPOP();
        }
    });
}

// Тесты для очереди
BOOST_AUTO_TEST_CASE(test_print_q) {
    Queue qu{nullptr, nullptr};
    BOOST_REQUIRE_EQUAL(!qu.QPrint(),true);
    qu.QPush("Alice");
    BOOST_REQUIRE_EQUAL(qu.QPrint(),true);
}
BOOST_AUTO_TEST_CASE(test_push_queue) {
    Queue queue{nullptr, nullptr};
    queue.QPush("Alice");
    BOOST_REQUIRE_EQUAL(!queue.is_empty(), true);
}

BOOST_AUTO_TEST_CASE(test_pop_queue) {
    Queue queue{nullptr, nullptr};
    queue.QPush("Alice");
    queue.QPush("Bob");
    queue.QPop();
    BOOST_REQUIRE_EQUAL(!queue.is_empty(), true);
    queue.QPop();
    BOOST_REQUIRE_EQUAL(queue.is_empty(), true);
}

BOOST_AUTO_TEST_CASE(test_empty_queue) {
    Queue queue{nullptr, nullptr};
    BOOST_REQUIRE_EQUAL(queue.is_empty(), true);
}
// Бенчмарки для очереди
BOOST_AUTO_TEST_CASE(BenchmarkQueuePushPop) {
    Queue queue{nullptr, nullptr};
    runBenchmark("Queue Push/Pop", [&queue]() {
        for (int i = 0; i < 100; ++i) {
            queue.QPush("item");
            queue.QPop();
        }
    });
}

// Тесты для массива
BOOST_AUTO_TEST_CASE(test_print_mas) {
    Massive mas;
    BOOST_REQUIRE_EQUAL(!mas.MPrint(),true);
    mas.MPushback("Alice");
    BOOST_REQUIRE_EQUAL(mas.MPrint(),true);
}
BOOST_AUTO_TEST_CASE(test_push_end) {
    Massive mas;
    mas.MPushback("Alice");
    mas.MPushback("Bob");
    string znach=mas.MGet(0);
    // Проверка получения значений
    BOOST_CHECK_EQUAL(znach, "Alice");
    znach=mas.MGet(1);
    BOOST_CHECK_EQUAL(znach, "Bob");
    string enter = "1";
    while(mas.realsize < mas.size-1){
        mas.MPushback(enter);
        enter += "a";
    }
    mas.MPushback("13");
    znach = mas[mas.realsize-1];
    BOOST_CHECK_EQUAL(znach, "13");

}

BOOST_AUTO_TEST_CASE(test_push_index) {
    Massive mas;
    mas.MPushback("Alice");
    string znach=mas.MGet(0);
    // Проверка получения значений
    BOOST_CHECK_EQUAL(znach, "Alice");
    mas.MPushind(0, "Bob");
    znach=mas.MGet(0);
    BOOST_CHECK_EQUAL(znach, "Bob");
    znach=mas.MGet(1);
    BOOST_CHECK_EQUAL(znach, "Alice");
    mas.MPushind(7, "Bob");
    znach=mas.MGet(7);
    BOOST_CHECK_EQUAL(znach, "Index is bigger than massive has");
    string enter = "1";
    while(mas.realsize < mas.size){
        mas.MPushback(enter);
        enter += "a";
    }
    mas.MPushind(mas.realsize-1, "13");
    znach = mas[mas.realsize-2];
    BOOST_CHECK_EQUAL(znach, "13");
}

BOOST_AUTO_TEST_CASE(test_pop_index) {
    Massive mas;
    mas.MPushback("Alice");
    mas.MPushback("Bob");
    string znach=mas.MGet(0);
    // Проверка получения значений
    BOOST_CHECK_EQUAL(znach, "Alice");
    znach=mas.MGet(1);
    BOOST_CHECK_EQUAL(znach, "Bob");
    //del
    mas.MPopind(0);
    znach=mas.MGet(0);
    BOOST_CHECK_EQUAL(znach, "Bob");
     mas.MPopind(7);
     znach=mas.MGet(7);
    BOOST_CHECK_EQUAL(znach, "Index is bigger than massive has");

}

BOOST_AUTO_TEST_CASE(test_replace_index) {
    Massive mas;
    mas.MPushback("Alice");
    mas.MPushback("Bob");
    string znach=mas.MGet(0);
    // Проверка получения значений
    BOOST_CHECK_EQUAL(znach, "Alice");
    znach=mas.MGet(1);
    BOOST_CHECK_EQUAL(znach, "Bob");
    //del
    mas.MChange(0,"Rusy");
    znach=mas.MGet(0);
    BOOST_CHECK_EQUAL(znach, "Rusy");
}
BOOST_AUTO_TEST_CASE(test_size) {
    Massive mas;
    int size=mas.Size();
    //Пуст ли
    BOOST_CHECK_EQUAL(size,0);
}

BOOST_AUTO_TEST_CASE(test_empty_get) {
    Massive mas;
    mas.MPushind(1, "123");
    string znach = mas.MGet(1);
    BOOST_CHECK_EQUAL(znach, "Massive is empty");
}

// Бенчмарки для массива
BOOST_AUTO_TEST_CASE(BenchmarkMassivePushBack) {
    Massive mas;
    runBenchmark("Massive PushBack", [&mas]() {
        for (int i = 0; i < 10; i++) {
            mas.MPushback("item");
        }
    });
}

BOOST_AUTO_TEST_CASE(BenchmarkMassivePopIndex) {
    Massive mas;
    for (int i = 0; i < 10; i++) {
        mas.MPushback("item");
    }
    runBenchmark("Massive PopIndex", [&mas]() {
        for (int i = 0; i < 10; ++i) {
            mas.MPopind(0);
        }
    });
}


// Тесты для хэш-таблицы

BOOST_AUTO_TEST_CASE(test_insert_and_get) {
    Hash hash;
    hash.HPush("key1", "value1");
    hash.HPush("key2", "value2");
    hash.HPush("key3", "value3");
    string val=hash.HGet("key1");
    // Проверка получения значений
    BOOST_CHECK_EQUAL(val, "value1");
    
}

BOOST_AUTO_TEST_CASE(test_update_value) {
    Hash hash;
    hash.HPush("key1", "value1");
    hash.HPush("key2", "value2");
    hash.HPush("key3", "value3");
    string val=hash.HGet("key1");
    // Проверка получения значений
    BOOST_CHECK_EQUAL(val, "value1");

     hash.HPush("key1", "3");
     val=hash.HGet("key1");
    // Проверка получения значений
    BOOST_CHECK_EQUAL(val, "3");
    hash.HPush("G", "value4");
    val=hash.HGet("G");
    // Проверка получения значений
    BOOST_CHECK_EQUAL(val, "value4");
    hash.HPush("G", "420");
    val=hash.HGet("G");
    BOOST_CHECK_EQUAL(val, "420");
    hash.HPush("aaaaaaa", "value1");
    hash.HPush("xxxxxxx", "value2");
    hash.HPush("aaaaaaa", "123");
    val=hash.HGet("aaaaaaa");
    BOOST_CHECK_EQUAL(val, "123");
}

BOOST_AUTO_TEST_CASE(test_remove) {
    Hash hash;
    hash.HPush("key1", "value1");
    hash.HPush("key2", "value2");
    //Добавилось ли
    string val=hash.HGet("key1");
    // Проверка получения значений
    BOOST_CHECK_EQUAL(val, "value1");
    //Уд
    hash.HPop("key1");
    //Удалился ли?
    string value=hash.HGet("key1");
    // Проверка получения значений
    BOOST_CHECK_EQUAL(value, "");
    //Все хорошо с другим значением?
    val=hash.HGet("key2");
    // Проверка получения значений
    BOOST_CHECK_EQUAL(val, "value2");
    hash.HPush("G", "value3");
    hash.HPop("G");
    val=hash.HGet("G");
    BOOST_CHECK_EQUAL(val, "");
    hash.HPush("aaaaaaa", "value1");
    hash.HPush("xxxxxxx", "value2");
    hash.HPop("aaaaaaa");
    val = hash.HGet("aaaaaaa");
    BOOST_CHECK_EQUAL(val, "");
    hash.HPop("aaaaaaa");
    val = hash.HGet("aaaaaaa");
    BOOST_CHECK_EQUAL(val, "");

}

BOOST_AUTO_TEST_CASE(test_print_hash){
    Hash hash;
    bool check = hash.HPrint();
    BOOST_CHECK_EQUAL(check, 0);
    hash.HPush("key1", "value1");
    hash.HPush("key2", "value2");
    check = hash.HPrint();
    BOOST_CHECK_EQUAL(check, 1);
}

BOOST_AUTO_TEST_CASE(test_collision_handling) {
    Hash hash;
    hash.HPush("ab", "value1");
    hash.HPush("ba", "value2");
    string value=hash.HGet("ab");
    BOOST_CHECK_EQUAL(value, "value1");
    value=hash.HGet("ba");
    BOOST_CHECK_EQUAL(value, "value2");
}

// Бенчмарки для хэш-таблицы
BOOST_AUTO_TEST_CASE(BenchmarkHashInsertGet) {
    Hash hash;
    runBenchmark("Hash Insert/Get", [&hash]() {
        for (int i = 0; i < 100; ++i) {
            hash.HPush("key" + to_string(i), "value" + to_string(i));
            hash.HGet("key" + to_string(i));
        }
    });
}

// Тесты для дерева
BOOST_AUTO_TEST_CASE(test_push) {
    Tree tree{nullptr};
    tree.TPush(tree.root, "5");
    bool kol = tree.TFind(tree.root, "5");
    tree.TPush(tree.root, "53");
    tree.TPush(tree.root, "4");
    tree.TPush(tree.root, "51");
    kol = tree.TFind(tree.root, "53");
    BOOST_CHECK_EQUAL(kol, 1);
    kol = tree.TFind(tree.root, "4");
    BOOST_CHECK_EQUAL(kol, 1);
}
BOOST_AUTO_TEST_CASE(test_find) {
    Tree tree{nullptr};
    tree.TPush(tree.root, "5");
    tree.TPush(tree.root, "3");
    tree.print_Tree(tree.root, 0);
    BOOST_CHECK_EQUAL(tree.TFind(tree.root, "5"), true);
    BOOST_CHECK_EQUAL(tree.TFind(tree.root, "3"), true);
    BOOST_CHECK_EQUAL(!tree.TFind(tree.root, "69"), true);
}

BOOST_AUTO_TEST_CASE(test_bin) {
    Tree tree{nullptr};
    tree.TPush(tree.root, "b");
    tree.TPush(tree.root, "c");
    BOOST_CHECK_EQUAL(!tree.is_full(tree.root), true);
    tree.TPush(tree.root, "a");
    BOOST_CHECK_EQUAL(tree.is_full(tree.root), true);
}

BOOST_AUTO_TEST_CASE(test_emty) {
    Tree tree{nullptr};
    BOOST_CHECK_EQUAL(tree.is_empty(), true);
}
// Бенчмарки для дерева
BOOST_AUTO_TEST_CASE(BenchmarkTreeInsertFind) {
    Tree tree{nullptr};
    runBenchmark("Tree Insert/Find", [&tree]() {
        for (int i = 0; i < 100; ++i) {
            tree.TPush(tree.root, to_string(i));
            tree.TFind(tree.root, to_string(i));
        }
    });
}
// Тесты для списка
BOOST_AUTO_TEST_CASE(test_print_ls){
    LIST_S list{nullptr};
    BOOST_REQUIRE_EQUAL(!list.LsPRINT(),true);
    list.LsPUSH_end("AE");
    BOOST_REQUIRE_EQUAL(list.LsPRINT(),true);
}
BOOST_AUTO_TEST_CASE(test_push_end_ls) {
    LIST_S list{nullptr};
    list.LsPUSH_end("B");
    list.LsPUSH_end("C");
    list.LsPUSH_end("D");
    
    BOOST_REQUIRE_EQUAL(list.LsGET("B"),true);
    BOOST_REQUIRE_EQUAL(list.LsGET("C"),true);
    BOOST_REQUIRE_EQUAL(list.LsGET("D"),true);
    BOOST_REQUIRE_EQUAL(!list.LsGET("A"),true);
   
}

BOOST_AUTO_TEST_CASE(test_push_head) {
     LIST_S list{nullptr};
     list.LsPUSH_front("A");
     list.LsPUSH_front("B");
    BOOST_REQUIRE_EQUAL(list.LsGET("B"),true);
    BOOST_REQUIRE_EQUAL(!list.LsGET("C"),true);
    BOOST_REQUIRE_EQUAL(list.LsGET("A"),true);
}

BOOST_AUTO_TEST_CASE(test_pop_front) {
     LIST_S list{nullptr};
    list.LsPUSH_end("B");
    list.LsPUSH_end("C");
    
    list.LsPOP_head();
    BOOST_REQUIRE_EQUAL(!list.LsGET("B"),true);
    BOOST_REQUIRE_EQUAL(list.LsGET("C"),true);
}

BOOST_AUTO_TEST_CASE(test_pop_end) {
     LIST_S list{nullptr};
     list.LsPUSH_end("A");
    list.LsPUSH_end("B");
    list.LsPUSH_end("C");
    
    list.LsPOP_end();
    BOOST_REQUIRE_EQUAL(list.LsGET("B"),true);
    BOOST_REQUIRE_EQUAL(!list.LsGET("C"),true);
    list.LsPOP_end();
    list.LsPOP_end();
    BOOST_REQUIRE_EQUAL(!list.LsGET("B"),true);
}

BOOST_AUTO_TEST_CASE(test_pop_znach) {
    LIST_S list{nullptr};
    list.LsPOP_data("123");
    BOOST_REQUIRE_EQUAL(list.LsGET("123"),false);
    list.LsPUSH_end("B");
    list.LsPUSH_end("C");
    list.LsPUSH_front("A");
    list.LsPOP_data("B");
    BOOST_REQUIRE_EQUAL(!list.LsGET("B"),true);
    BOOST_REQUIRE_EQUAL(list.LsGET("C"),true);
    BOOST_REQUIRE_EQUAL(list.LsGET("A"),true);
    list.LsPOP_data("A");
     BOOST_REQUIRE_EQUAL(!list.LsGET("B"),true);
    BOOST_REQUIRE_EQUAL(list.LsGET("C"),true);
    BOOST_REQUIRE_EQUAL(!list.LsGET("A"),true);
     list.LsPOP_data("R");
    list.LsPUSH_end("B");
    list.LsPUSH_end("C");
    list.LsPUSH_end("A");
    list.LsPOP_data("A");
    BOOST_REQUIRE_EQUAL(!list.LsGET("A"),true);
}

BOOST_AUTO_TEST_CASE(test_empty_list) {
   LIST_S list{nullptr};
    BOOST_REQUIRE_EQUAL(!list.LsGET("A"),true); 
}

// Бенчмарки для односвязного списка
BOOST_AUTO_TEST_CASE(BenchmarkListPushPop) {
    LIST_S list{nullptr};
    runBenchmark("List Push/Pop", [&list]() {
        for (int i = 0; i < 100; ++i) {
            list.LsPUSH_end("item");
            list.LsPOP_end();
        }
    });
}
//Doublelimk
BOOST_AUTO_TEST_CASE(test_print_ld){
    LIST_d list{nullptr,nullptr};
    BOOST_REQUIRE_EQUAL(!list.LdPRINT(),true);
    list.LdPUSH_end("AE");
    BOOST_REQUIRE_EQUAL(list.LdPRINT(),true);
}
BOOST_AUTO_TEST_CASE(test_push_end_ld) {
    LIST_d list{nullptr, nullptr};
    list.LdPUSH_end("B");
    list.LdPUSH_end("C");
    
    BOOST_REQUIRE_EQUAL(list.LdGET("B"),true);
    BOOST_REQUIRE_EQUAL(list.LdGET("C"),true);
    BOOST_REQUIRE_EQUAL(!list.LdGET("A"),true);
   
}

BOOST_AUTO_TEST_CASE(test_push_head_ld) {
     LIST_d list{nullptr, nullptr};
     list.LdPUSH_front("A");
     list.LdPUSH_front("B");
    BOOST_REQUIRE_EQUAL(list.LdGET("B"),true);
    BOOST_REQUIRE_EQUAL(!list.LdGET("C"),true);
    BOOST_REQUIRE_EQUAL(list.LdGET("A"),true);
}

BOOST_AUTO_TEST_CASE(test_pop_front_ld) {
    LIST_d list{nullptr, nullptr};
    list.LdPUSH_end("B");
    list.LdPUSH_end("C");
    
    list.LdPOP_head();
    BOOST_REQUIRE_EQUAL(!list.LdGET("B"),true);
    BOOST_REQUIRE_EQUAL(list.LdGET("C"),true);
}

BOOST_AUTO_TEST_CASE(test_pop_end_ld) {
    LIST_d list{nullptr, nullptr};
    list.LdPUSH_end("B");
    list.LdPUSH_end("C");
    
    list.LdPOP_end();
    BOOST_REQUIRE_EQUAL(list.LdGET("B"),true);
    BOOST_REQUIRE_EQUAL(!list.LdGET("C"),true);
}

BOOST_AUTO_TEST_CASE(test_pop_znach_ld) {
    LIST_d list{nullptr, nullptr};
    list.LdPUSH_end("B");
    list.LdPUSH_end("C");
    list.LdPUSH_front("A");
    list.LdPOP_data("B");
    BOOST_REQUIRE_EQUAL(!list.LdGET("B"),true);
    BOOST_REQUIRE_EQUAL(list.LdGET("C"),true);
    BOOST_REQUIRE_EQUAL(list.LdGET("A"),true);
    list.LdPOP_data("B");
    list.LdPUSH_front("A");
    list.LdPUSH_front("A");
    list.LdPUSH_front("A");
    list.LdPUSH_end("C");
    list.LdPOP_data("A");
}
BOOST_AUTO_TEST_CASE(test_empty_list_ld) {
    LIST_d list{nullptr, nullptr};
    BOOST_REQUIRE_EQUAL(!list.LdGET("A"),true); 
}
// Бенчмарки для двусвязного списка
BOOST_AUTO_TEST_CASE(BenchmarkDoubleListPushPop) {
    LIST_d list{nullptr, nullptr};
    runBenchmark("DoubleList Push/Pop", [&list]() {
        for (int i = 0; i < 100; ++i) {
            list.LdPUSH_end("item");
            list.LdPOP_end();
        }
    });
}