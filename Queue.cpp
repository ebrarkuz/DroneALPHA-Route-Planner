#include "Queue.h"
#include <iostream>

// Constructor to initialize an empty queue
Queue::Queue() {
   front=-1;
    rear=-1;
    // TODO: Your code here
}

// Adds a province to the end of the queue
void Queue::enqueue(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        std::cout << "Queue is full baba, yer kalmadı!\n";
        return;
    } else if (front == -1) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX_QUEUE_SIZE;
    }
    data[rear] = province;


    // Implement circular structure 
    // Add the province  
}

// Removes and returns the front province from the queue
int Queue::dequeue() {
    if (front == -1) {
        std::cout << "Queue is empty baba \n";
        return -1;
    }

    int removedValue = data[front];
    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX_QUEUE_SIZE;
    }

    return removedValue;
}

// Returns the front province without removing it
int Queue::peek() const {
    if (front == -1) {
        std::cout << "Queue is empty baba \n";
        return -1;
    }
    return data[front];
}

// Checks if the queue is empty
bool Queue::isEmpty() const {
    if(front==-1 ) {
        return true;
    }
    return false;
    // TODO: Your code here
}

// Add a priority neighboring province in a way that will be dequeued and explored before other non-priority neighbors
void Queue::enqueuePriority(int province) {
    if ((rear + 1) % MAX_QUEUE_SIZE == front) {
        std::cout << "Queue is full baba, yer kalmadı!\n";
        return;
    }
    if (front == -1) {
        front = rear = 0;
        data[front] = province;
    } else {
        front = (front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
        data[front] = province;
    }
}

