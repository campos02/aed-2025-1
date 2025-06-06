typedef struct Number {
    int number;
    struct Number *next;
} Number;

typedef struct Queue {
    Number *first;
    Number *last;
} Queue;

Queue* queueCreate() {
    Queue *queue = malloc(sizeof(Queue));
    queue->first = NULL;
    queue->last = NULL;

    return queue;
}

void queuePush(Queue* queue, int x) {
    Number *number = malloc(sizeof(Number));
    number->number = x;
    number->next = NULL;

    if (queue->last == NULL)
        queue->last = number;
    else {
        queue->last->next = number;
        queue->last = number;
    }

    if (queue->first == NULL)
        queue->first = queue->last;
}

int queuePop(Queue* queue) {
    if (queue->first == NULL)
        return -1;

    int number = queue->first->number;

    if (queue->first->next != NULL)
        queue->first = queue->first->next;
    else {
        queue->first = NULL;
        queue->last = NULL;
    }

    return number;
}

int queuePeek(Queue* queue) {
    if (queue->first == NULL)
        return -1;

    return queue->first->number;
}

void queueClear(Queue* queue) {
    queue->first = NULL;
    queue->last = NULL;
}

int queueSize(Queue* queue) {
    int size = 0;

    Number *number = queue->first;
    while (number != NULL) {
        size++;
        number = number->next;
    }

    return size;
}

typedef struct MyStack {
    Queue *queue;
    Queue *reverseQueue;
} MyStack;


MyStack* myStackCreate() {
    MyStack *stack = malloc(sizeof(MyStack));
    stack->queue = queueCreate();
    stack->reverseQueue = queueCreate();

    return stack;
}

void myStackPush(MyStack* obj, int x) {
    queuePush(obj->queue, x);
    queueClear(obj->reverseQueue);

    Queue *queueCopy = malloc(sizeof(Queue));
    queueCopy->first = obj->queue->first;
    queueCopy->last = obj->queue->last;

    int size = queueSize(queueCopy);
    int *contents = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        contents[i] = queuePop(queueCopy);
    }

    for (int i = size - 1; i >= 0; i--) {
        queuePush(queueCopy, contents[i]);
    }
    
    free(contents);
    obj->reverseQueue = queueCopy;
}

int myStackPop(MyStack* obj) {
    int number = queuePop(obj->reverseQueue);
    queueClear(obj->queue);

    Queue *queueCopy = malloc(sizeof(Queue));
    queueCopy->first = obj->reverseQueue->first;
    queueCopy->last = obj->reverseQueue->last;

    int size = queueSize(queueCopy);
    int *contents = malloc(size * sizeof(int));

    for (int i = 0; i < size; i++) {
        contents[i] = queuePop(queueCopy);
    }

    for (int i = size - 1; i >= 0; i--) {
        queuePush(queueCopy, contents[i]);
    }
    
    free(contents);
    obj->queue = queueCopy;
    
    return number;
}

int myStackTop(MyStack* obj) {
    return queuePeek(obj->reverseQueue);
}

bool myStackEmpty(MyStack* obj) {
    return obj->reverseQueue->last == NULL;
}

void myStackFree(MyStack* obj) {
    queueClear(obj->queue);
    queueClear(obj->reverseQueue);

    free(obj->queue);
    free(obj->reverseQueue);

    obj->queue = NULL;
    obj->reverseQueue = NULL;

    free(obj);
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/