// Assignment 2
// Author: Abdelkarim Ait Bourich
// Date: 2026-01-22
// sorry i wasnt able to finish the assignment on time due to some personal issues
#include <iostream>
#include <cassert>
#include <stdexcept>

using namespace std;

// part 1: singly linked list

// node for singly linked list
class SLLNode {
public:
    int data;
    SLLNode* next;

    SLLNode(int value) : data(value), next(nullptr) {}
};

// singly linked list class
class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void insertFront(int value);
    void insertBack(int value);
    void insertAt(int index, int value);

    void removeFront();
    void removeBack();
    void removeAt(int index);

    bool isEmpty() const;
    int size() const;
    void clear();

    void print() const;
    int getAt(int index) const;
    int indexOf(int value) const;

private:
    SLLNode* head;
    int count;
    SLLNode* getNodeAt(int index) const;
};

// constructor
LinkedList::LinkedList() : head(nullptr), count(0) {}

// destructor
LinkedList::~LinkedList() {
    clear();
}

// insert at front
void LinkedList::insertFront(int value) {
    SLLNode* newNode = new SLLNode(value);
    newNode->next = head;
    head = newNode;
    count++;
}

// insert at back
void LinkedList::insertBack(int value) {
    SLLNode* newNode = new SLLNode(value);
    
    if (isEmpty()) {
        head = newNode;
    } else {
        SLLNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

// insert at index
void LinkedList::insertAt(int index, int value) {
    if (index < 0 || index > count) {
        throw out_of_range("Index out of range");
    }

    if (index == 0) {
        insertFront(value);
        return;
    }

    if (index == count) {
        insertBack(value);
        return;
    }

    SLLNode* newNode = new SLLNode(value);
    SLLNode* prev = getNodeAt(index - 1);
    newNode->next = prev->next;
    prev->next = newNode;
    count++;
}

// remove from front
void LinkedList::removeFront() {
    if (isEmpty()) {
        throw underflow_error("Cannot remove from empty list");
    }

    SLLNode* temp = head;
    head = head->next;
    delete temp;
    count--;
}

// remove from back
void LinkedList::removeBack() {
    if (isEmpty()) {
        throw underflow_error("Cannot remove from empty list");
    }

    if (count == 1) {
        delete head;
        head = nullptr;
        count--;
        return;
    }

    SLLNode* prev = getNodeAt(count - 2);
    delete prev->next;
    prev->next = nullptr;
    count--;
}

// remove at index
void LinkedList::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }

    if (index == 0) {
        removeFront();
        return;
    }

    SLLNode* prev = getNodeAt(index - 1);
    SLLNode* toDelete = prev->next;
    prev->next = toDelete->next;
    delete toDelete;
    count--;
}

// check if empty
bool LinkedList::isEmpty() const {
    return count == 0;
}

// return size
int LinkedList::size() const {
    return count;
}

// remove all elements
void LinkedList::clear() {
    while (!isEmpty()) {
        removeFront();
    }
}

// print list
void LinkedList::print() const {
    SLLNode* current = head;
    cout << "[";
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << "]" << endl;
}

// get value at index
int LinkedList::getAt(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }
    return getNodeAt(index)->data;
}

// find index of value, returns -1 if not found
int LinkedList::indexOf(int value) const {
    SLLNode* current = head;
    int index = 0;
    
    while (current != nullptr) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

// get node at index
SLLNode* LinkedList::getNodeAt(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }

    SLLNode* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}


// part 2: doubly linked list

// node for doubly linked list
class DLLNode {
public:
    int data;
    DLLNode* prev;
    DLLNode* next;

    DLLNode(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// doubly linked list class
class DoublyLinkedList {
public:
    DoublyLinkedList();
    virtual ~DoublyLinkedList();

    void insertFront(int value);
    void insertBack(int value);
    void insertAt(int index, int value);

    void removeFront();
    void removeBack();
    void removeAt(int index);

    bool isEmpty() const;
    int size() const;
    void clear();

    void printForward() const;
    void printBackward() const;

    int getAt(int index) const;
    int indexOf(int value) const;

protected:
    DLLNode* head;
    DLLNode* tail;
    int count;

    DLLNode* getNodeAt(int index) const;
};

// constructor
DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

// destructor
DoublyLinkedList::~DoublyLinkedList() {
    clear();
}

// insert at front
void DoublyLinkedList::insertFront(int value) {
    DLLNode* newNode = new DLLNode(value);

    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
}

// insert at back
void DoublyLinkedList::insertBack(int value) {
    DLLNode* newNode = new DLLNode(value);

    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

// insert at index
void DoublyLinkedList::insertAt(int index, int value) {
    if (index < 0 || index > count) {
        throw out_of_range("Index out of range");
    }

    if (index == 0) {
        insertFront(value);
        return;
    }

    if (index == count) {
        insertBack(value);
        return;
    }

    DLLNode* newNode = new DLLNode(value);
    DLLNode* current = getNodeAt(index);
    
    newNode->prev = current->prev;
    newNode->next = current;
    current->prev->next = newNode;
    current->prev = newNode;
    count++;
}

// remove from front
void DoublyLinkedList::removeFront() {
    if (isEmpty()) {
        throw underflow_error("Cannot remove from empty list");
    }

    DLLNode* temp = head;

    if (count == 1) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }

    delete temp;
    count--;
}

// remove from back
void DoublyLinkedList::removeBack() {
    if (isEmpty()) {
        throw underflow_error("Cannot remove from empty list");
    }

    DLLNode* temp = tail;

    if (count == 1) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    count--;
}

// remove at index
void DoublyLinkedList::removeAt(int index) {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }

    if (index == 0) {
        removeFront();
        return;
    }

    if (index == count - 1) {
        removeBack();
        return;
    }

    DLLNode* toDelete = getNodeAt(index);
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;
    delete toDelete;
    count--;
}

// check if empty
bool DoublyLinkedList::isEmpty() const {
    return count == 0;
}

// return size
int DoublyLinkedList::size() const {
    return count;
}

// remove all elements
void DoublyLinkedList::clear() {
    while (!isEmpty()) {
        removeFront();
    }
}

// print head to tail
void DoublyLinkedList::printForward() const {
    DLLNode* current = head;
    cout << "[";
    while (current != nullptr) {
        cout << current->data;
        if (current->next != nullptr) {
            cout << " <-> ";
        }
        current = current->next;
    }
    cout << "]" << endl;
}

// print tail to head
void DoublyLinkedList::printBackward() const {
    DLLNode* current = tail;
    cout << "[";
    while (current != nullptr) {
        cout << current->data;
        if (current->prev != nullptr) {
            cout << " <-> ";
        }
        current = current->prev;
    }
    cout << "]" << endl;
}

// get value at index
int DoublyLinkedList::getAt(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }
    return getNodeAt(index)->data;
}

// find index of value, returns -1 if not found
int DoublyLinkedList::indexOf(int value) const {
    DLLNode* current = head;
    int index = 0;

    while (current != nullptr) {
        if (current->data == value) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

// get node at index
DLLNode* DoublyLinkedList::getNodeAt(int index) const {
    if (index < 0 || index >= count) {
        throw out_of_range("Index out of range");
    }

    DLLNode* current;
    
    if (index < count / 2) {
        current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
    } else {
        current = tail;
        for (int i = count - 1; i > index; i--) {
            current = current->prev;
        }
    }
    
    return current;
}


// part 3: stack (derived from doubly linked list)

// stack class - lifo behavior using back of list
class Stack : public DoublyLinkedList {
public:
    Stack();
    ~Stack();

    void push(int value);
    void pop();
    int top() const;
    bool isEmpty() const;
    int size() const;
    void clear();
};

// constructor
Stack::Stack() : DoublyLinkedList() {}

// destructor
Stack::~Stack() {}

// push onto stack
void Stack::push(int value) {
    insertBack(value);
}

// pop from stack
void Stack::pop() {
    if (isEmpty()) {
        throw underflow_error("Cannot pop from empty stack");
    }
    removeBack();
}

// peek at top
int Stack::top() const {
    if (isEmpty()) {
        throw underflow_error("Cannot peek empty stack");
    }
    return tail->data;
}

// check if empty
bool Stack::isEmpty() const {
    return DoublyLinkedList::isEmpty();
}

// return size
int Stack::size() const {
    return DoublyLinkedList::size();
}

// clear stack
void Stack::clear() {
    DoublyLinkedList::clear();
}


// part 4: queue (derived from doubly linked list)

// queue class - fifo behavior
class Queue : public DoublyLinkedList {
public:
    Queue();
    ~Queue();

    void enqueue(int value);
    void dequeue();
    int front() const;
    bool isEmpty() const;
    int size() const;
    void clear();
};

// constructor
Queue::Queue() : DoublyLinkedList() {}

// destructor
Queue::~Queue() {}

// add to back
void Queue::enqueue(int value) {
    insertBack(value);
}

// remove from front
void Queue::dequeue() {
    if (isEmpty()) {
        throw underflow_error("Cannot dequeue from empty queue");
    }
    removeFront();
}

// peek at front
int Queue::front() const {
    if (isEmpty()) {
        throw underflow_error("Cannot peek empty queue");
    }
    return head->data;
}

// check if empty
bool Queue::isEmpty() const {
    return DoublyLinkedList::isEmpty();
}

// return size
int Queue::size() const {
    return DoublyLinkedList::size();
}

// clear queue
void Queue::clear() {
    DoublyLinkedList::clear();
}


// validation function

bool validate() {
    cout << "running validation tests..." << endl << endl;

    // stack test
    cout << "testing stack..." << endl;
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);
    s.push(40);
    s.push(50);
    s.push(60);

    assert(s.top() == 60);
    cout << "  [pass] s.top() == 60" << endl;

    s.pop();
    assert(s.top() == 50);
    cout << "  [pass] after pop(), s.top() == 50" << endl;

    s.clear();
    assert(s.isEmpty() == true);
    cout << "  [pass] after clear(), s.isEmpty() == true" << endl;

    cout << "stack tests passed!" << endl << endl;

    // queue test
    cout << "testing queue..." << endl;
    Queue q;
    q.enqueue(100);
    q.enqueue(200);
    q.enqueue(300);
    q.enqueue(400);
    q.enqueue(500);
    q.enqueue(600);

    assert(q.front() == 100);
    cout << "  [pass] q.front() == 100" << endl;

    q.dequeue();
    assert(q.front() == 200);
    cout << "  [pass] after dequeue(), q.front() == 200" << endl;

    q.clear();
    assert(q.isEmpty() == true);
    cout << "  [pass] after clear(), q.isEmpty() == true" << endl;

    cout << "queue tests passed!" << endl << endl;

    cout << "==================================" << endl;
    cout << "all validation tests passed!" << endl;
    cout << "==================================" << endl;

    return true;
}


// main function

int main() {
    cout << "==================================" << endl;
    cout << "  data structures assignment" << endl;
    cout << "==================================" << endl << endl;

    validate();

    cout << endl;

    // demo
    cout << "--- additional demos ---" << endl << endl;

    // linkedlist demo
    cout << "linkedlist demo:" << endl;
    LinkedList ll;
    ll.insertBack(1);
    ll.insertBack(2);
    ll.insertBack(3);
    ll.insertFront(0);
    ll.print();
    cout << "  size: " << ll.size() << endl;
    cout << "  element at index 2: " << ll.getAt(2) << endl;
    cout << "  index of value 2: " << ll.indexOf(2) << endl;
    cout << endl;

    // doublylinkedlist demo
    cout << "doublylinkedlist demo:" << endl;
    DoublyLinkedList dll;
    dll.insertBack(10);
    dll.insertBack(20);
    dll.insertBack(30);
    dll.insertFront(5);
    cout << "  forward:  ";
    dll.printForward();
    cout << "  backward: ";
    dll.printBackward();
    cout << endl;

    cout << "all demos complete!" << endl;

    return 0;
}
