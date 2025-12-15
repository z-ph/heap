#include <stdio.h>
enum boolean { FALSE=0, TRUE=1 };
enum SORT_ORDER { DESCENDING=0, ASCENDING=1 };
typedef struct {
    int key;
    // 其他字段可以根据需要添加
} Element;

typedef struct {
    Element *data;// 0号为留空，堆元素从1号开始存储
    int capacity;
    int size;
    enum SORT_ORDER sort_order; // 1表示升序堆，0表示降序堆
} Heap;
/* 对外暴露的堆操作接口 */
// 初始化堆
void heap_init(Heap *heap, Element *data, int capacity, int size, enum SORT_ORDER sort_order);

// 插入元素到堆
void heap_insert(Heap *heap, Element element);

// 删除堆顶元素, 并返回该元素
Element heap_delete_top(Heap *heap);

// 销毁堆, 释放内存
void heap_destroy(Heap *heap);

// 打印堆中的元素 
void heap_print(Heap *heap);

// 堆排序函数, 对给定数组进行排序, ascending 为真时升序排序, 否则降序排序
void heap_sort(Element *array, int length, int ascending);

/* 底层api*/
// 对某一节点进行堆化
void heapify(Heap *heap, int index);
// 构建堆
void build_heap(Heap *heap);
// 交换堆中两个元素的位置
void swap(Element *a, Element *b);
// 比较两个元素的大小, 返回1表示a大于b, 返回0表示a小于等于b
int compare(Element a, Element b, enum SORT_ORDER sort_order);
// 扩展堆的容量
void expand_heap(Heap *heap);
// 收缩堆的容量
void shrink_heap(Heap *heap);
// 获取父节点索引
int parent_index(int index);
// 获取左子节点索引
int left_child_index(int index);
// 获取右子节点索引
int right_child_index(int index);

