#include <stdlib.h>

struct Node
{
    int vertex;
    int distance;
};

struct MinPQ
{
    int size;
    int capacity;
    int *positionsForDecreaseKey;
    struct Node **array;
};

class MinPriorityQueue
{
public:
    //Constructor
    MinPriorityQueue();

    // Destructor
    ~MinPriorityQueue();

    // creates new Node
    struct Node *newNode(int v, int dist);

    // creates new MinPQ
    struct MinPQ *newMinPQ(int capacity);

    // swap nodes of MinPQ during heapify
    void swapNodes(struct Node **a, struct Node **b);

    // heapifies at the given index
    void heapify(struct MinPQ *minPQ, int idx);

    // checks minPQ size with zero
    int isEmpty(struct MinPQ *minPQ);

    // extracts top node from the heap
    struct Node *extractMin(struct MinPQ *minPQ);

    // decreases distance of the vertex v
    void decreaseKey(struct MinPQ *minPQ, int v, int dist);

    // checks the given vertex is present in heap or not
    bool isInMinPQ(struct MinPQ *minPQ, int v);
};