#include "Stack.h"
#include <iostream>

// Constructor to initialize an empty stack
Stack::Stack() {
     top= -1;
    // TODO: Your code here
}

// Adds a province to the top of the stack
void Stack::push(int province) {
    if(top>=MAX_SIZE-1) {
        std::cout<<"Stack is full baba"<<std::endl;
    }
    else {
        top++;
        data[top]=province;
    }
    // TODO: Your code here
}

// Removes and returns the top province from the stack
int Stack::pop() {
    if(top==-1) {
        std::cout<<"Stack is empty baba "<<std::endl;
        return -1;
    }
        int val = data[top];
        top--;
        return val;

    // TODO: Your code here
}

// Returns the top province without removing it
int Stack::peek() const {
    if(top==-1) {
        std::cout<<"Stack is empty baba "<<std::endl;
        return -1;
    }

        return data[top];


    // TODO: Your code here

}

// Checks if the stack is empty
bool Stack::isEmpty() const {
    if(top==-1) {
         return true;
    } return false;
    // TODO: Your code here

}

// Function to get the current size of the stack
int Stack::getSize() const {

    return top+1;
}
