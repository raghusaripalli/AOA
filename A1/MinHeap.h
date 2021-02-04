#include <stdlib.h>

struct MinHeapNode
{
    int v;
    int dist;
};

struct MinHeap
{

    // Number of heap nodes present currently
    int size;

    // Capacity of min heap
    int capacity;

    // This is needed for decreaseKey()
    int *pos;
    struct MinHeapNode **array;
};

class MinPriorityQueue
{
public:
    //Constructor
    MinPriorityQueue();

    // Destructor
    ~MinPriorityQueue();

    // create a new Min Heap Node
    struct MinHeapNode *newMinHeapNode(int v, int dist);

    // create a Min Heap
    struct MinHeap *createMinHeap(int capacity);

    // swap two nodes of min heap. Needed for min heapify
    void swapMinHeapNode(struct MinHeapNode **a, struct MinHeapNode **b);

    // to heapify at given idx. This function also updates position of nodes when they are swapped. Position is needed for decreaseKey()
    void minHeapify(struct MinHeap *minHeap, int idx);

    // check if the given minHeap is ampty or not
    int isEmpty(struct MinHeap *minHeap);

    // Standard function to extract minimum node from heap
    struct MinHeapNode *extractMin(struct MinHeap *minHeap);

    // decrease dist value of a given vertex v.
    // This function uses pos[] of min heap to get the current index of node in min heap
    void decreaseKey(struct MinHeap *minHeap, int v, int dist);

    // check if a given vertex 'v' is in min heap or not
    bool isInMinHeap(struct MinHeap *minHeap, int v);
};