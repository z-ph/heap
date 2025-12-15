#include "./utils.c"

int test_swap()
{
    printf("Heap module test: swap\n");
    print_info("Before swap: a.key = 5, b.key = 10");
    Element a = {.key = 5};
    Element b = {.key = 10};
    swap(&a, &b);
    expect(a.key, 10, "Swap a.key should be 10");
    expect(b.key, 5, "Swap b.key should be 5");
    return 0;
}

int test_index_functions()
{
    printf("Heap module test: index functions\n");
    print_info("Testing parent_index, left_child_index, right_child_index");

    expect(parent_index(1), 0, "Parent of index 1 should be 0");
    expect(parent_index(2), 1, "Parent of index 2 should be 1");
    expect(parent_index(3), 1, "Parent of index 3 should be 1");
    expect(parent_index(4), 2, "Parent of index 4 should be 2");
    expect(parent_index(5), 2, "Parent of index 5 should be 2");
    expect(parent_index(6), 3, "Parent of index 6 should be 3");

    expect(left_child_index(1), 2, "Left child of index 1 should be 2");
    expect(left_child_index(2), 4, "Left child of index 2 should be 4");
    expect(left_child_index(3), 6, "Left child of index 3 should be 6");

    expect(right_child_index(1), 3, "Right child of index 1 should be 3");
    expect(right_child_index(2), 5, "Right child of index 2 should be 5");
    expect(right_child_index(3), 7, "Right child of index 3 should be 7");

    return 0;
}

int test_compare()
{
    printf("Heap module test: compare\n");
    Element a = {.key = 5};
    Element b = {.key = 10};
    print_info("Before compare: a.key = 5, b.key = 10");
    int res1 = compare(a, b, ASCENDING);
    int res2 = compare(a, b, DESCENDING);
    expect(res1, 0, "Compare ascending a < b should be FALSE");
    expect(res2, 1, "Compare descending a > b should be TRUE");
    return 0;
}

int test_heapify()
{
    printf("Heap module test: heapify\n");
    print_info("Testing heapify with small heap");

    Element data[] = {{0}, {12}, {4}, {5}, {6}, {1}, {3}};
    Heap heap = {data, sizeof(data) / sizeof(data[0]), 6, ASCENDING};

    print_heap_array(heap.data, heap.size, "Original array:");
    print_info("Heapifying from index 1");

    heapify(&heap, 1);

    Element expected[] = {{0}, {12}, {4}, {5}, {6}, {1}, {3}};
    print_heap_array(heap.data, heap.size, "After heapify:");
    expect_heap_array_equal(heap.data, heap.size, expected, 6, "Heapify at index 1 should not change the heap");

    print_info("Continue Heapifying from index 2");
    heapify(&heap, 2);
    Element expected2[] = {{0}, {12}, {6}, {5}, {4}, {1}, {3}};
    print_heap_array(heap.data, heap.size, "After heapify index 2:");
    expect_heap_array_equal(heap.data, heap.size, expected2, 6, "Heapify at index 2 should adjust subtree correctly");

    print_info("Continue Heapifying from index 3");
    heapify(&heap, 3);
    Element expected3[] = {{0}, {12}, {6}, {5}, {4}, {1}, {3}};
    print_heap_array(heap.data, heap.size, "After heapify index 3:");
    expect_heap_array_equal(heap.data, heap.size, expected3, 6, "Heapify at index 3 should not change the heap");

    return 0;
}

int test_build_heap()
{
    printf("Heap module test: build_heap\n");
    print_info("Testing build_heap with unsorted array");

    Element data[] = {{0}, {3}, {1}, {6}, {5}, {2}, {4}};
    Heap heap = {data, sizeof(data) / sizeof(data[0]), 6, ASCENDING};

    print_heap_array(heap.data, heap.size, "Original array:");
    print_info("Building max heap");

    build_heap(&heap);

    Element expected[] = {{0}, {6}, {5}, {4}, {1}, {2}, {3}};
    print_heap_array(heap.data, heap.size, "After build_heap:");
    expect_heap_array_equal(heap.data, heap.size, expected, sizeof(expected) / sizeof(expected[0]) - 1, "Build_heap should create valid max heap");

    return 0;
}

int test_heap_sort()
{
    printf("Heap module test: heap_sort\n");
    print_info("Testing heap_sort ascending");

    Element array_asc[] = {3, 1, 6, 5, 2, 4};
    print_normal_array(array_asc, sizeof(array_asc) / sizeof(array_asc[0]), "Original array:");

    heap_sort(array_asc, sizeof(array_asc) / sizeof(array_asc[0]), ASCENDING);

    Element expected_asc[] = {1, 2, 3, 4, 5, 6};
    print_normal_array(array_asc, sizeof(array_asc) / sizeof(array_asc[0]), "After ascending sort:");
    expect_normal_array_equal(array_asc, sizeof(array_asc) / sizeof(array_asc[0]), expected_asc, sizeof(expected_asc) / sizeof(expected_asc[0]), "Heap sort ascending should work correctly");

    print_info("Testing heap_sort descending");

    Element array_desc[] = {3, 1, 6, 5, 2, 4};
    heap_sort(array_desc, sizeof(array_desc) / sizeof(array_desc[0]), DESCENDING);

    Element expected_desc[] = {6, 5, 4, 3, 2, 1};
    print_normal_array(array_desc, sizeof(array_desc) / sizeof(array_desc[0]), "After descending sort:");
    expect_normal_array_equal(array_desc, sizeof(array_desc) / sizeof(array_desc[0]), expected_desc, sizeof(expected_desc) / sizeof(expected_desc[0]), "Heap sort descending should work correctly");

    return 0;
}
