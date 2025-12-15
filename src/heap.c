#include "./utils.c"
void build_heap(Heap *heap)
{
    for (int i = parent_index(heap->size); i >= 1; i--)
    {
        heapify(heap, i);
    }
}

void heap_init(Heap *heap, Element *data, int capacity, int size, enum SORT_ORDER sort_order)
{
    heap->data = data;
    heap->capacity = capacity;
    heap->size = size;
    heap->sort_order = sort_order;
}


Element heap_delete_top(Heap *heap)
{
    if (heap->size < 1)
    {
        Element empty = {0};
        return empty;
    }

    Element top = heap->data[1];
    heap->data[1] = heap->data[heap->size];
    heap->size--;

    heapify(heap, 1);

    return top;
}

void heap_destroy(Heap *heap)
{
    if (heap->data != NULL)
    {
        free(heap->data);
        heap->data = NULL;
    }
    heap->capacity = 0;
    heap->size = 0;
}

void heap_print(Heap *heap)
{
    printf("Heap [");
    for (int i = 1; i <= heap->size; i++)
    {
        printf("%d", heap->data[i].key);
        if (i < heap->size)
            printf(", ");
    }
    printf("] (size: %d, capacity: %d)\n", heap->size, heap->capacity);
}

void heap_sort(Element *array, int length, enum SORT_ORDER sort_order)
{
    if (length <= 1)
        return;

    Element *data = malloc((length + 1) * sizeof(Element));
    data[0].key = 0;
    for (int i = 0; i < length; i++)
    {
        data[i + 1] = array[i];
    }

    Heap *heap = malloc(sizeof(Heap));
    heap_init(heap, data, length + 1, length, sort_order);
    build_heap(heap);

    for (int i = length - 1; i >= 0; i--)
    {
        Element max = heap_delete_top(heap);
        array[i] = max;
    }
    heap_destroy(heap);
}


