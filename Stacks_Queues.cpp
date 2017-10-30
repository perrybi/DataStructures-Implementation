#include <iostream>
#include <string>
using namespace std;

// Stack and queue implementation and their functionalities (with C++):

class StackClass{
    int* stackArray;
    int top;
    int stackCap;

public:
    StackClass(int stackCap){
        if(stackCap<=0)
            throw string("Stack capacity must be positive!\n”);
        
        top = -1;
        this->stackCap = stackCap;
        stackArray = new int[stackCap];
    }
    
    void push(int data){
        if (isFull()){
            throw string("Stack is full!\n");
        }
        stackArray[++top] = data;
    }
    
    int pop(){
        if (isEmpty()){
            throw string("Stack if empty!\n");
        }        
        top--;
        return stackArray[top+1];
    }
    
    int Top(){
        if (isEmpty()){
            throw string("Stack is empty!\n");
        }
        return stackArray[top];
    }
    
    bool isEmpty(){
        if (top == -1){
            return true;
        }
        return false;
    }
    
    bool isFull(){
        //cout << stackCap << " " << top ;
        if (top == stackCap-1){
            return true;
        }
        return false;
    }
    
    void printStack(){
        if (isEmpty()){
            throw string("Stack is empty!\n");
        }
        for (int i=0; i<=top; i++){
            cout << stackArray[i] << " ";
        }
        cout << endl;
    }
};    

// Sort stack: sort a stack such that the smallest items are on the top:

void sortStack (StackClass* myStack){
    StackClass* temporaryStack = new StackClass;
    while(!myStack->isEmpty()){
        int temp = myStack->pop();
        while(!temporaryStack->isEmpty() && temp < temporaryStack->Top()){
            myStack->push(temporaryStack->pop());
        }
        temporaryStack->push(temp);
    }
    
    // copy over all the sorted elements from the temporary stack:
    while(!temporaryStack->isEmpty())
        myStack->push(temporaryStack->pop());
}

// Three in one (multi-stack): use a single array to implement multiple stacks:

class multiStackClass{
    int numberStack = 3; // e.g. three stacks by one array
    int multiStackCap;
    int* sizeArray;
    int* multiStackArray;
    
public:
    multiStackClass(int numberStack, int stackCap){
        multiStackCap = stackCap;
        multiStackArray = new int[stackCap*numberStack];
        sizeArray = new int[numberStack];
    }

    int Index(int stacknum, int val){
        return (stacknum-1)*multiStackCap + val - 1;
    }
    
    void push(int stacknum, int data){
        if (isFull(stacknum))
            throw string ("Stack is Full!");
        
        sizeArray[stacknum-1]++;    
        multiStackArray[Index(stacknum, sizeArray[stacknum-1])] = data;    
    }
    
    int pop(int stacknum){
        if (isEmpty(stacknum))
            throw string ("Stack is Empty!");
        
        int topind = Index(stacknum, sizeArray[stacknum-1]);
        sizeArray[stacknum-1]--;
        return multiStackArray[topind];
    }   
    
    int Top(int stacknum){
        if (isEmpty(stacknum))
            throw string ("Stack is Empty!");
        
        return multiStackArray[Index(stacknum, sizeArray[stacknum-1])];
    }
    
    bool isEmpty(int stacknum){
        if (sizeArray[stacknum-1] == 0)
            return true;
            
        return false;    
    }
    
    bool isFull(int stacknum){
        if (sizeArray[stacknum-1] == multiStackCap-1)
            return true;
            
        return false;    
    }
    
    void printMultiStack(int stacknum){
        if (isEmpty(stacknum)){
            throw string("Stack is empty!\n");
        }
        for (int i=1; i<=sizeArray[stacknum-1]; i++){
            cout << multiStackArray[Index(stacknum, i)] << " ";
        }
        cout << endl;
    }
};

// Stack min: design a stack in which in addition to push and pop, “min” function returns the minimum element with o(1) time complexity:
class stackArraywMin: public StackClass{
   
    StackClass* stackMin = new StackClass; // a stack to record the min w each element
    
public:
    void push(int data);
    void efficPush(int data);
    int pop();
    int efficPop();
    int getMin();
};

void stackArraywMin :: push(int data){
        if(isEmpty() == true){
            StackClass :: push(data);
            stackMin->push(data);
        }
        else {
            StackClass :: push(data);
            int oldMin = stackMin->Top();
            if (data < oldMin)
                stackMin->push(data);
                
            else
                stackMin->push(oldMin);
        }
}
    
int stackArraywMin :: pop(){
    int val = StackClass::pop();
    stackMin->pop();
    return val;
}
 
int stackArraywMin :: getMin(){
    return (stackMin->Top());
}   
    
void stackArraywMin :: efficPush(int data){
        if(isEmpty() == true){
            StackClass :: push(data);
            stackMin->push(data);
        }
        else {
            StackClass :: push(data);
            int oldMin = stackMin->Top();
            if (data <= oldMin)
                stackMin->push(data);
        }
}
    
int stackArraywMin :: efficPop(){
    int val = StackClass :: pop();
    int mins = stackMin->pop();
    if (mins != val)
        stackMin->push(mins);
    
    return val;
}

// Queue via stacks (FIFO): using two stacks (LIFO):

struct myQueue{
    StackClass* oldStack;
    StackClass* newStack;
    myQueue (){
    oldStack = new StackClass;
    newStack = new StackClass;        
    }
    void addQ(int data){
        if (newStack->isFull())
            throw string ("Queue is full!");
            
        newStack->push(data);
    }
    void shiftStacks(){
        if (oldStack->isEmpty()){
            while(!newStack->isEmpty())
            oldStack->push(newStack->pop());
            
        }
    }
    int TopQ(){
        shiftStacks(); // check old stack is not empty, and if it is update it.
        return oldStack->Top();
    }
    int removeQ(){
        shiftStacks();
        return oldStack->pop();
    }
    
};
