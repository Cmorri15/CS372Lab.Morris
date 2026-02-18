#pragma once
#include <iostream>
#include <functional>

template <typename T>
class List {
private:
    class Node {
    public:
        T data;
        Node *prev = nullptr;
        Node *next = nullptr;
        bool isHiddenNode = false;
    };
    
    Node *head = nullptr;
    Node *tail = nullptr;
    
    void deleteListContents() {
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current->next;
            delete current;
            current = temp;
        }
        head = nullptr;
        tail = nullptr;
    }
    
    void setupList() {
        Node* newNode = new Node();
        newNode->next = nullptr;
        newNode->prev = nullptr;
        newNode->isHiddenNode = false;
        head->next = newNode;
        newNode->prev = head;
        newNode->next = tail;
        tail->prev = newNode;
    }

public:
    // Nested iterator classes
    class const_iterator {
    protected:
        Node *current;
        T & retrieve() const { return current->data; }
        const_iterator(Node* p) : current(p) { }
        friend class List<T>;
        
    public:
        const_iterator() : current(nullptr) { }
        
        T & operator*() const {
            return retrieve();
        }
        
        const_iterator & operator++() {
            current = current->next;
            return *this;
        }
        
        const_iterator operator++(int) {
            const_iterator old = *this;
            ++(*this);
            return old;
        }
        
        bool operator==(const const_iterator & rhs) const {
            return current == rhs.current;
        }
        
        bool operator!=(const const_iterator & rhs) const {
            return !(*this == rhs);
        }
    };
    
    class iterator : public const_iterator {
    protected:
        iterator(Node *p) : const_iterator(p) { }
        friend class List<T>;
        
    public:
        iterator() { }
        
        T & operator*() {
            return const_iterator::retrieve();
        }
        
        const T & operator*() const {
            return const_iterator::operator*();
        }
        
        iterator & operator++() {
            this->current = this->current->next;
            return *this;
        }
        
        iterator operator++(int) {
            iterator old = *this;
            ++(*this);
            return old;
        }
    };
    
    // Constructors
    List() {
        head = new Node();
        head->isHiddenNode = true;
        tail = new Node();
        tail->isHiddenNode = true;
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
    }
    
    List(T newData) : List() {
        push_back(newData);
    }
    
    // Copy constructor
    List(const List &rhs) : List() {
        for (Node *curr = rhs.head->next; curr != rhs.tail; curr = curr->next) {
            push_back(curr->data);
        }
    }
    
    // Move constructor
    List(List&& rhs) noexcept : head(rhs.head), tail(rhs.tail) {
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    
    // Destructor
    ~List() {
        deleteListContents();
    }
    
    // Copy assignment operator
    List& operator=(const List &rhs) {
        if (this != &rhs) {
            deleteListContents();
            head = new Node();
            head->isHiddenNode = true;
            tail = new Node();
            tail->isHiddenNode = true;
            head->prev = nullptr;
            head->next = tail;
            tail->prev = head;
            tail->next = nullptr;
            
            for (Node *curr = rhs.head->next; curr != rhs.tail; curr = curr->next) {
                push_back(curr->data);
            }
        }
        return *this;
    }
    
    // Move assignment operator
    List& operator=(List&& rhs) noexcept {
        if (this != &rhs) {
            deleteListContents();
            head = rhs.head;
            tail = rhs.tail;
            rhs.head = nullptr;
            rhs.tail = nullptr;
        }
        return *this;
    }
    
    // Check if list is empty
bool empty() const {
    if (head == nullptr || tail == nullptr) {
        return true;
    }
    return (head->next == tail);
}
    
    // Push to front
    void push_front(T data) {
        if (this->empty()) {
            setupList();
            Node *actualHead = head->next;
            actualHead->data = data;
        }
        else {
            Node *actualHead = head->next;
            Node *newNode = new Node();
            newNode->data = data;
            newNode->next = actualHead;
            actualHead->prev = newNode;
            newNode->prev = head;
            head->next = newNode;
        }
    }
    
    // Push to back
    void push_back(T data) {
        if (this->empty()) {
            setupList();
            Node *actualTail = tail->prev;
            actualTail->data = data;
        }
        else {
            Node *actualTail = tail->prev;
            Node *newNode = new Node();
            newNode->data = data;
            newNode->prev = actualTail;
            actualTail->next = newNode;
            newNode->next = tail;
            tail->prev = newNode;
        }
    }
    
    // Get front element
    T& front() {
        if (empty()) {
            std::cerr << "List::front(): List is empty\n";
            exit(1);
        }
        Node *actualHead = head->next;
        return actualHead->data;
    }
    
    // Get back element
    T& back() {
        if (empty()) {
            std::cerr << "List::back(): List is empty\n";
            exit(1);
        }
        Node *actualTail = tail->prev;
        return actualTail->data;
    }
    
    // Pop from front
    void pop_front() {
        if (!empty()) {
            Node *firstNode = head->next;
            head->next = firstNode->next;
            Node *newFirstNode = head->next;
            newFirstNode->prev = head;
            delete firstNode;
        }
        else {
            std::cerr << "pop_front(): Attempt to pop from empty list.\n";
        }
    }
    
    // Pop from back
    void pop_back() {
        if (!empty()) {
            Node *lastNode = tail->prev;
            tail->prev = lastNode->prev;
            Node *newLastNode = tail->prev;
            newLastNode->next = tail;
            delete lastNode;
        }
        else {
            std::cerr << "pop_back(): Attempt to pop from empty list.\n";
        }
    }
    
    // Get size
int size() const {
    if (head == nullptr || tail == nullptr) {
        return 0;
    }
    int count = 0;
    Node *current = head->next;
    while (current != tail) {
        count++;
        current = current->next;
    }
    return count;
}
    
    // Traverse with function
    void traverse(std::function<void(T&)> doIt) {
        Node *current = head->next;
        while (current != tail) {
            doIt(current->data);
            current = current->next;
        }
    }
    
    // Iterator methods
    iterator begin() { return iterator(head->next); }
    iterator end() { return iterator(tail); }
    const_iterator cbegin() const { return const_iterator(head->next); }
    const_iterator cend() const { return const_iterator(tail); }
    
    // Insert at position
    iterator insert(iterator pos, const T &x) {
        Node *p = pos.current;
        Node *newNode = new Node();
        newNode->data = x;
        newNode->next = p;
        newNode->prev = p->prev;
        p->prev->next = newNode;
        p->prev = newNode;
        return iterator(newNode);
    }
    
    // Erase at position
    iterator erase(iterator pos) {
        Node *p = pos.current;
        iterator retVal(p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        return retVal;
    }
    
    // Erase range
    iterator erase(iterator start, iterator end) {
        for (iterator itr = start; itr != end; ) {
            itr = erase(itr);
        }
        return end;
    }
};