#include "../include/heap.h"
#include <stdlib.h>
void swap(Element *a, Element *b){
    Element temp = *a;
    *a = *b;
    *b = temp;
}
int compare(Element a, Element b, enum SORT_ORDER sort_order){
    if(sort_order == ASCENDING){
        return a.key > b.key;
    } else {
        return a.key < b.key;
    }
}
int parent_index(int index){
    return index / 2;
}
int left_child_index(int index){
    return 2 * index;
}
int right_child_index(int index){
    return 2 * index + 1;
}
void heapify(Heap *heap, int index){
    int max_min_index = index;
    int left = left_child_index(index);
    int right = right_child_index(index);

    if(left <= heap->size && compare(heap->data[left], heap->data[max_min_index], heap->sort_order)){
        max_min_index = left;
    }
    if(right <= heap->size && compare(heap->data[right], heap->data[max_min_index], heap->sort_order)){
        max_min_index = right;
    }
    if(max_min_index != index){
        swap(&heap->data[index], &heap->data[max_min_index]);
        heapify(heap, max_min_index);
    }
}
void build_heap(Heap *heap){
    for(int i = parent_index(heap->size); i >= 1; i--){
        heapify(heap, i);
    }
}

void heap_init(Heap *heap, Element *data, int capacity, int size, enum SORT_ORDER sort_order) {
    heap->data = data;
    heap->capacity = capacity;
    heap->size = size;
    heap->sort_order = sort_order;
}

void heap_insert(Heap *heap, Element element) {
    if(heap->size >= heap->capacity - 1) {
        expand_heap(heap);
    }

    heap->size++;
    heap->data[heap->size] = element;

    int current = heap->size;
    while(current > 1 && compare(heap->data[current], heap->data[parent_index(current)], heap->sort_order)) {
        swap(&heap->data[current], &heap->data[parent_index(current)]);
        current = parent_index(current);
    }
}

Element heap_delete_top(Heap *heap) {
    if(heap->size < 1) {
        Element empty = {0};
        return empty;
    }

    Element top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;

    heapify(heap, 1);

    if(heap->size < heap->capacity / 4 && heap->capacity > 4) {
        shrink_heap(heap);
    }

    return top;
}

void heap_destroy(Heap *heap) {
    if(heap->data != NULL) {
        free(heap->data);
        heap->data = NULL;
    }
    heap->capacity = 0;
    heap->size = 0;
}

void heap_print(Heap *heap) {
    printf("Heap [");
    for(int i = 1; i <= heap->size; i++) {
        printf("%d", heap->data[i].key);
        if(i < heap->size) printf(", ");
    }
    printf("] (size: %d, capacity: %d)\n", heap->size, heap->capacity);
}

void heap_sort(Element *array, int length, enum SORT_ORDER sort_order) {
    if(length <= 1) return;

    Element *data = malloc((length + 1) * sizeof(Element));
    data[0].key = 0;
    for(int i = 0; i < length; i++) {
        data[i + 1] = array[i];
    }

    Heap heap = {data, length + 1, length, sort_order};
    build_heap(&heap);

    for(int i = length - 1; i >= 0; i--) {
        Element max = heap_delete_top(&heap);
        array[i] = max;
    }
    heap_destroy(&heap);
}

void expand_heap(Heap *heap) {
    int new_capacity = heap->capacity * 2;
    Element *new_data = realloc(heap->data, new_capacity * sizeof(Element));
    if(new_data != NULL) {
        heap->data = new_data;
        heap->capacity = new_capacity;
    }
}

void shrink_heap(Heap *heap) {
    int new_capacity = heap->capacity / 2;
    Element *new_data = realloc(heap->data, new_capacity * sizeof(Element));
    if(new_data != NULL) {
        heap->data = new_data;
        heap->capacity = new_capacity;
    }
}