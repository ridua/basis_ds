#include <stdio.h>

#define MAX_HEAP_INDEX  100
#define LEFT(i) (2*i + 1)
#define RIGHT(i) (2*i + 2)
#define PARENT(i) (i==0 ? -1 : (i - 1)/2)

typedef struct heap_node_t {
    int arr[MAX_HEAP_INDEX];
    int last_index;
} heap_node;

void swap (int *a, int *b) {
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void check_and_swap(int *arr, int me, int i, int n) {

    if (i >= 0 && i < n && arr[me] > arr[i] && i != me) {
        swap(&arr[me], &arr[i]);
    }
}


void heapify_internal(int *arr, int i, int n) {
    if (i >= n || i < 0 ) {
        return;
    }

    check_and_swap(arr, i, LEFT(i), n);
    check_and_swap(arr, i, RIGHT(i), n);
    heapify_internal(arr, PARENT(i), n);
    return;
}


void heapify(int *arr, int n) {
    heapify_internal(arr, n - 1, n);
}

void heap_push (heap_node *heap, int val) {
    if (!heap) {
        return;
    }

    if (heap->last_index == MAX_HEAP_INDEX) {
        return;
    }

    if (heap->last_index == -1) {
        heap->arr[0] = val;
        heap->last_index = 0;
        return;
    }

    heap->last_index++;
    heap->arr[heap->last_index] = val;

    heapify(heap->arr, heap->last_index + 1);
}

void display(int *arr, int n) {
    int i = 0;

    printf("\nElements in heap:");
    for (i = 0; i < n; i++) {
        printf("\narr[%d]: %d", i, arr[i]);
    }
    printf("\n");

}


int heap_pop(heap_node *heap) {
    int rv = -1;

    if (!heap) {
        return rv;
    }

    if (heap->last_index == -1) {
        return rv;
    }

    rv = heap->arr[0];

    swap(&heap->arr[0], &heap->arr[heap->last_index]);
    heap->last_index--;

    heapify(heap->arr, heap->last_index + 1);
    return rv;
}

int main() {
    heap_node heap = {0};
    heap.last_index = -1;

    heap_push(&heap, 5);
    //display(heap.arr, heap.last_index + 1);
    heap_push(&heap, 2);
    //display(heap.arr, heap.last_index + 1);
    heap_push(&heap, 3);
    //display(heap.arr, heap.last_index + 1);
    heap_push(&heap, 6);
    heap_push(&heap, 7);
    heap_push(&heap, 1);
    display(heap.arr, heap.last_index + 1);

    //display(heap.arr, heap.last_index + 1);

    printf("\nPop: %d", heap_pop(&heap));
    printf("\nPop: %d", heap_pop(&heap));
    printf("\nPop: %d", heap_pop(&heap));
    printf("\nPop: %d", heap_pop(&heap));
    printf("\nPop: %d", heap_pop(&heap));
    printf("\nPop: %d", heap_pop(&heap));
    display(heap.arr, heap.last_index + 1);

    return 0;
}