#include "./tests.c"
#include <stdlib.h>
// 传入函数指针
int divide(int(*func)(void)){
    printf("==================\n");
    int res = func();
    printf("==================\n");
    return res;
}
int main() {
    divide(test_swap);
    divide(test_compare);
    divide(test_index_functions);
    divide(test_heapify);
    divide(test_build_heap);
    divide(test_heap_sort);
    return 0;
}