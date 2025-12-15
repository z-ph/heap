#include "../include/heap.h"
#include <stdlib.h>
void swap(Element *a, Element *b)
{
    Element temp = *a;
    *a = *b;
    *b = temp;
}
int compare(Element a, Element b, enum SORT_ORDER sort_order)
{
    if (sort_order == ASCENDING)
    {
        return a.key > b.key;
    }
    else
    {
        return a.key < b.key;
    }
}
int parent_index(int index)
{
    return index / 2;
}
int left_child_index(int index)
{
    return 2 * index;
}
int right_child_index(int index)
{
    return 2 * index + 1;
}
void heapify(Heap *heap, int index)
{
    int max_min_index = index;
    int left = left_child_index(index);
    int right = right_child_index(index);

    if (left <= heap->size && compare(heap->data[left], heap->data[max_min_index], heap->sort_order))
    {
        max_min_index = left;
    }
    if (right <= heap->size && compare(heap->data[right], heap->data[max_min_index], heap->sort_order))
    {
        max_min_index = right;
    }
    if (max_min_index != index)
    {
        swap(&heap->data[index], &heap->data[max_min_index]);
        heapify(heap, max_min_index);
    }
}