#include "MinPQ.h"

MinPriorityQueue::MinPriorityQueue() {}
MinPriorityQueue::~MinPriorityQueue() {}

struct Node *MinPriorityQueue::newNode(int v, int dist)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->vertex = v;
    node->distance = dist;
    return node;
}

struct MinPQ *MinPriorityQueue::newMinPQ(int capacity)
{
    struct MinPQ *minPQ = (struct MinPQ *)malloc(sizeof(struct MinPQ));
    minPQ->positionsForDecreaseKey = (int *)malloc(capacity * sizeof(int));
    minPQ->size = 0;
    minPQ->capacity = capacity;
    minPQ->array = (struct Node **)malloc(capacity * sizeof(struct Node *));
    return minPQ;
}

void MinPriorityQueue::swapNodes(struct Node **a, struct Node **b)
{
    struct Node *t = *a;
    *a = *b;
    *b = t;
}

void MinPriorityQueue::heapify(struct MinPQ *minPQ, int idx)
{
    int least, left, right;
    least = idx;
    left = (idx * 2) + 1;
    right = (idx * 2) + 2;

    if (left < minPQ->size && minPQ->array[left]->distance < minPQ->array[least]->distance)
        least = left;

    if (right < minPQ->size && minPQ->array[right]->distance < minPQ->array[least]->distance)
        least = right;

    if (least != idx)
    {
        Node *leastNode = minPQ->array[least];
        Node *idxNode = minPQ->array[idx];

        minPQ->positionsForDecreaseKey[leastNode->vertex] = idx;
        minPQ->positionsForDecreaseKey[idxNode->vertex] = least;

        swapNodes(&minPQ->array[least], &minPQ->array[idx]);

        heapify(minPQ, least);
    }
}

int MinPriorityQueue::isEmpty(struct MinPQ *minPQ)
{
    return minPQ->size == 0;
}

struct Node *MinPriorityQueue::extractMin(struct MinPQ *minPQ)
{
    if (isEmpty(minPQ))
        return NULL;

    struct Node *root = minPQ->array[0];

    struct Node *lastNode = minPQ->array[minPQ->size - 1];
    minPQ->array[0] = lastNode;

    minPQ->positionsForDecreaseKey[root->vertex] = minPQ->size - 1;
    minPQ->positionsForDecreaseKey[lastNode->vertex] = 0;

    --minPQ->size;
    heapify(minPQ, 0);

    return root;
}

void MinPriorityQueue::decreaseKey(struct MinPQ *minPQ, int v, int dist)
{
    int i = minPQ->positionsForDecreaseKey[v];
    minPQ->array[i]->distance = dist;

    while (i && minPQ->array[i]->distance < minPQ->array[(i - 1) / 2]->distance)
    {

        minPQ->positionsForDecreaseKey[minPQ->array[i]->vertex] = (i - 1) / 2;
        minPQ->positionsForDecreaseKey[minPQ->array[(i - 1) / 2]->vertex] = i;
        swapNodes(&minPQ->array[i], &minPQ->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

bool MinPriorityQueue::isInMinPQ(struct MinPQ *minPQ, int v)
{
    return minPQ->positionsForDecreaseKey[v] < minPQ->size;
}
