#include <iostream>
#include <stack>
#include <stdlib.h> 
#include <bits/stdc++.h>

using namespace std;

// Linked list implementation and its functionalities with C++:

struct Node{
    int data;
    Node* next;
};

bool deleteNode (Node* node){
    if (node == NULL || node->next == NULL){
        return false; // deletion did not work!    
    }
    Node* nxt_node = node->next;
    node->data = nxt_node->data;
    node->next = nxt_node->next;
    delete(nxt_node);
    return true;
}

Node* addNode(int data){
    Node* node = new Node;
    node->data = data;
    node->next = NULL;
    return node;
}

void printNode(Node* node){
    cout << node->data << endl;
}

void printList(Node* node){
    while(node != NULL){
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

Node* reverseList(Node* node){
    Node* dummyHead = NULL;
    while(node != NULL){
        Node* n = new Node;
        n->data = node->data;
        n->next = dummyHead;
        dummyHead = n;
        node = node->next;
    }
    return dummyHead;    
}

bool equalLists(Node* list1, Node* list2){
    while(list1 != NULL){
        if (list1->data != list2->data)
            return false;
       
        list1 = list1->next;
        list2 = list2->next;
    }
    return list1 == NULL && list2 == NULL;
}

// Detect if the linked list has a loop?

bool hasCircle(Node* node){
    Node* fastRunner = node;
    Node* slowRunner = node->next;
    
    while(fastRunner!= NULL && fastRunner->next != NULL){
        slowRunner = slowRunner->next;
        fastRunner = fastRunner->next->next;
        
        if (slowRunner == fastRunner){
            return true;
        }
        
    }
    return false;
}

// Remove Dups: removing duplicates from an unsorted linked list using hashing:

void removeDups(Node* node){
    //declare an unordered set:
    unordered_set<int> hashTable;
    Node* previous = NULL;
    Node* current = node;
    while(current != NULL){
        if (hashTable.find(current->data) != hashTable.end()){
            previous->next = current->next;
            delete(current); // free the memory block
        }
        else{
            hashTable.insert(current->data); 
            previous = current;
        }
        current = previous->next;
    }
}

// Remove Dups: removing duplicates from an unsorted linked list when temporary buffer is not allowed:

Node* removeDups(Node* node){
    Node* current = node;
    while(current != NULL){
        // remove duplicates:
        Node* second = current;
        while(second->next != NULL){
            if (second->next -> data == current->data){
                Node* duplicate = new Node;
                duplicate = second->next; // Don't forget to delete the pointer
                second->next = second->next->next;
                delete(duplicate);
            }
            else
                second = second->next;
        }
        current = current->next;
    }
    return node;
}

// Kth to Last: Kth to last element of a singly linked list:

Node* KthToLast(Node* node , int k, int& ind){
    if (node==NULL) // when the recursion stops
        return NULL;
    Node* temp = KthToLast(node->next, k, ind);
    ind = ind + 1;
    if (ind == k){
        return node;
    }
    return temp;
}
// pass by reference:
Node* KthToLast(Node* node , int k){
    int i = 0;
    return KthToLast(node , k, i);
}

// Kth to Last: Kth to last element of a singly linked list using two pointers:

Node* KthToLast(Node* node, int k){
    Node* ptr1 = node;
    Node* ptr2 = node;
    for (int i=0; i<k; i++){
        if (ptr1 == NULL)
            return NULL;
            
        ptr1 = ptr1->next;
    }
    while(ptr2 != NULL){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;    
    }
    return ptr2;
}

// Sum lists: add the two numbers represented by two linked lists (less significant < … < most significant) using recursion: 

Node* addLists(Node* list1, Node* list2, int residu){
        Node* listResult = new Node;
        if(list1 == NULL && list2 == NULL){
            if (residu > 0){
                listResult->data = residu;
                return listResult;
            }            
            return NULL;
        }
            
        if (list1 != NULL)
            residu += list1->data;
        
        if (list2 != NULL)
            residu += list2->data;
        
        listResult->data = residu % 10; 
        // conditions on list1/list2 needed for unequal-length lists
        listResult->next = addLists(list1 == NULL ? NULL : list1->next, list2 == NULL ? NULL : list2->next, residu >= 10 ? 1 : 0);
    
        return listResult;
}

// Sum lists: (less significant < … < most significant) using iteration: 


Node* addLists(Node* list1, Node* list2){
    if (list1 == NULL && list2 == NULL)
        return NULL;
    
    int residu = 0;
    Node* dummyHead = new Node;
    Node* tmp = dummyHead;
    while(list1 != NULL || list2 != NULL){
        
        if(list1 != NULL)
            residu += list1->data;
            
        if(list2 != NULL)
            residu += list2->data;
        
        tmp->next = addNode(residu%10);
        tmp = tmp->next;
        residu = residu/10;

        if (list1 != NULL)
            list1 = list1->next;
        
        if (list2 != NULL)
            list2 = list2->next;
    }
        
    if (residu > 0)
        tmp->next = addNode(residu);
        
    return dummyHead->next;
}

// // Sum lists: add the two numbers represented by two linked lists (most significant < … < less significant) using iteration: 
 

struct AddHelper{
    Node* partAdd = NULL;
    int residu = 0;
};
Node* putBefore(int intg, Node* head){
    Node* dummy = new Node;
    dummy->data = intg;
    if (head != NULL)
        dummy->next = head;
    
    head = dummy;
    return head;
}
Node* padZero(Node* head, int mLength, int MLength){
    Node* res = head;
    while(mLength != MLength){
        res = putBefore(0, head);
        mLength++;
    }  
    return res;
}
AddHelper* addRecurs(Node* list1, Node* list2){
    if(list1 == NULL && list2 == NULL){
        AddHelper* sum = new AddHelper;
        return sum;
    }
    AddHelper* sum = addRecurs(list1->next, list2->next);
    sum->residu += list1->data;
    sum->residu += list2->data;
    sum->partAdd = putBefore(sum->residu%10, sum->partAdd);
    sum->residu = sum->residu/10;
    return sum;
}

Node* addLists(Node* list1, Node* list2){
        if(list1 == NULL && list2 == NULL)          
            return NULL;
        
        int len1 = 0;
        while(list1 != NULL){
            len1 ++;
            list1 = list1->next;
        }
        
        int len2 = 0;
        while(list2 != NULL){
            len2 ++;
            list2 = list2->next;
        }
        
        if (len1 != len2){
            if(len1 < len2)
                padZero(list1, len1, len2);
                
            else
                padZero(list2, len2, len1);
        }
        
        AddHelper* partialAdd = addRecurs(list1, list2);
        
        if (partialAdd->residu > 0){
            Node* listResult = putBefore(partialAdd->residu, partialAdd->partAdd); 
            return listResult;
        }
        else
            return partialAdd->partAdd;
            
}

// Partition: partition a linked list around a value x: (< x) (= || > x)
(order is preserved)

Node* orderedPart(Node* node, int x){
    if (node == NULL || node-> next == NULL){
        return NULL;
    }
    Node* preList = NULL; # head and tail of 3 linked lists
    Node* preListEnd = NULL;
    Node* postList = NULL;
    Node* postListEnd = NULL;
    Node* equList = NULL;
    Node* equListEnd = NULL;
    
    while(node != NULL){
        Node* next = node->next; // keep track of next before any changes to the list
        node->next = NULL;
        if (node->data < x){
            if (preList == NULL){ //first element in the "< x" partition
                preList = node;
                preListEnd = preList;
            }
            else{ // already have data -> insert in the tail
                preListEnd->next = node;
                preListEnd = preListEnd->next; //iterator
            }
        }
        else if (node->data > x){
            if (postList == NULL){
                postList = node;
                postListEnd = postList;
            }
            else{
                postListEnd->next = node;
                postListEnd = postListEnd->next;
            }
        }
        else{
            if (equList == NULL){
                equList = node;
                equListEnd = equList;
            }
            else{
                equListEnd->next = node;
                equListEnd = equListEnd->next;
            }
        } 
        node = next; // iterates through the linked list
    }
    
    if (preList == NULL && equList == NULL){
        return postList;     
    }
    
    if (preList == NULL){
        equListEnd->next = postList;
        return equList;
    }
    
    if (equList == NULL){
        preListEnd->next = postList;
        return preList;
    }
    
    // merges preList, equList and postList:
    preListEnd->next = equList;
    equListEnd->next = postList;
    return preList;
}

// Partition: partition a linked list around a value x: (< x) (= || > x)
(order is not preserved)

Node* unorderedPart(Node* node, int x){
    Node* head = node; // head and tail of the result
    Node* tail = node;
    while(node != NULL){
        Node* next = node->next;
        if (node->data < x){
            node->next = head;
            head = node;
        }
        else {
            tail->next = node;
            tail = tail->next; // iterates
            tail->next = NULL;
        }
    node = next;    
    }
    tail->next = NULL;
    return head;
}

// Palindrome: is the linked list palindrome?

struct AddHelper{
    Node* partAdd = NULL;
    int residu = 0;
};

Node* putBefore(int integ, Node* head){
    Node* dummy = new Node;
    dummy->data = integ;
    dummy->next = head;
    head = dummy;
    return head;
}

Node* padZero(Node* head, int mLength, int MLength){
    while(mLength != MLength){
        putBefore(0, head);
        mLength++;
    }  
    return(head);
}

AddHelper* addRecurs(Node* list1, Node* list2){
    if(list1 == NULL && list2 == NULL){
        AddHelper* sum = new AddHelper;
        return sum;
    }
    AddHelper* sum = addRecurs(list1->next, list2->next);
    
    sum->residu += list1->data;
    sum->residu += list2->data;
    
    sum->partAdd = putBefore(sum->residu%10, sum->partAdd);
    sum->residu = sum->residu/10;
    return sum;
}

Node* addLists(Node* list1, Node* list2){
        if(list1 == NULL && list2 == NULL)          
            return NULL;
        
        int len1 = 0;
        while(list1 != NULL)
            len1 ++;
        
        int len2 = 0;
        while(list2 != NULL)
            len2 ++;
        
        if (len1 != len2){
            if(len1 < len2)
                padZero(list1, len1, len2);
                
            else
                padZero(list2, len2, len1);
        }
        
        AddHelper* partialAdd = addRecurs(list1, list2);
        
        if (partialAdd->residu > 0){
            Node* listResult = putBefore(partialAdd->residu, partialAdd->partAdd); 
            return listResult;
        }
        else
            return partialAdd->partAdd;
            
}

bool listIsPali(Node* node){
    Node* revNode = reverseList(node);
    return equalLists(node, revNode);
}

// Palindrome: is the linked list palindrome? fastRunner-slowRunner technique:

bool listIsPali2(Node* node){
    stack<int> helperStack;
    Node* slowRunner = node;
    Node* fastRunner = node;
    // even #s: itself is NULL, odd #s: next is NULL
    while(fastRunner != NULL && fastRunner->next != NULL){
        helperStack.push(slowRunner->data);
        slowRunner = slowRunner->next;
        fastRunner = fastRunner->next->next;
    }
    if(fastRunner != NULL)
        slowRunner = slowRunner->next; // odd #s: skip the middle node
        int Top;
    while(slowRunner != NULL && !helperStack.empty()){
        Top = helperStack.top();
        helperStack.pop();
        if(slowRunner->data != Top){
            return false;
        }
        slowRunner = slowRunner->next;    
    }    
    return true;
}

// Intersection: check if two linked list intersects:

struct Intersection{
    int len;
    Node* tail;
    Intersection(int len, Node* tail){
        this->len = len;
        this->tail = tail;
    }
};

Intersection* size_Tail(Node* head){
    if (head == NULL)
        return NULL;
        
    int len = 0;
    Node* node = head;
    while(node->next != NULL){
        len++;
        node = node->next;
    }
    Intersection* intersResult = new Intersection(len, node);
    return intersResult; // contains length and the tail node
}

Node* KthNode(Node* node, int k){
    Node* counter = node;
    while(node != NULL, k != 0){
        counter = counter->next;
        k--;
    }
    return counter;
}

Node* intersectedLists(Node* list1, Node* list2){
    
    Intersection* info1 = size_Tail(list1);
    Intersection* info2 = size_Tail(list2);

    // by definition, if two LSs intersect, they will share nodes until their tails:
    if (info1->tail != info2->tail)
        return NULL;
        
    Node* shorterList = info1->len > info2->len ? list2 : list1;
    Node* longerList = info1->len > info2->len ? list1 : list2;
    // removing the offset based on the length difference
    longerList = KthNode(longerList, abs(info2->len - info1->len));
    
    while(shorterList != longerList){
        shorterList = shorterList->next;
        longerList = longerList->next;
    }
    return shorterList;
}

// Given a circular linked list, find the node at the beginning of the loop:

Node* circleStart(Node* node){
    if (!hasCircle(node)){
        return NULL;
    }   
    delete(fastRunner);
    // one SR is already at the collision point.
    Node* slowRunner2 = node;
    
    while(slowRunner != slowRunner2){
        slowRunner = slowRunner->next;
        slowRunner2 = slowRunner2->next;
    }
    return (slowRunner1); // start of the loop
}

