#pragma once
#include <iostream>
#include <functional>

template <typename T>
class LazyList {
private:
    class Node {
    public:
        T data;
        Node *prev = nullptr;
        Node *next = nullptr;
        bool isHiddenNode = false;
        bool isDeleted = false;  // NEW: Track lazy deletion status
    };
    
    Node *head = nullptr;
    Node *tail = nullptr;
    int activeCount = 0;    // NEW: Count of non-deleted items
    int deletedCount = 0;   // NEW: Count of deleted items
    
    // Helper: Physically remove all deleted nodes
    void purgeDeletedNodes() {
        Node *current = head->next;
        while (current != tail) {
            Node *nextNode = current->next;
            if (current->isDeleted) {
                // Remove this node from the list
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            current = nextNode;
        }
        deletedCount = 0;  // Reset deleted count
    }
    
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
        activeCount = 0;
        deletedCount = 0;
    }
    
    void setupList() {
        Node* newNode = new Node();
        newNode->next = nullptr;
        newNode->prev = nullptr;
        newNode->isHiddenNode = false;
        newNode->isDeleted = false;
        head->next = newNode;
        newNode->prev = head;
        newNode->next = tail;
        tail->prev = newNode;
    }

public:
    // Constructors
    LazyList() {
        head = new Node();
        head->isHiddenNode = true;
        tail = new Node();
        tail->isHiddenNode = true;
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
        activeCount = 0;
        deletedCount = 0;
    }
    
    LazyList(T newData) : LazyList() {
        push_back(newData);
    }
    
    // Copy constructor
    LazyList(const LazyList &rhs) : LazyList() {
        for (Node *curr = rhs.head->next; curr != rhs.tail; curr = curr->next) {
            if (!curr->isDeleted) {  // Only copy non-deleted items
                push_back(curr->data);
            }
        }
    }
    
    // Destructor
    ~LazyList() {
        deleteListContents();
    }
    
    // Copy assignment operator
    LazyList& operator=(const LazyList &rhs) {
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
            activeCount = 0;
            deletedCount = 0;
            
            for (Node *curr = rhs.head->next; curr != rhs.tail; curr = curr->next) {
                if (!curr->isDeleted) {  // Only copy non-deleted items
                    push_back(curr->data);
                }
            }
        }
        return *this;
    }
    
    // Check if list is empty (ignoring deleted items)
    bool empty() const {
        return activeCount == 0;
    }
    
    // Push to front
    void push_front(T data) {
        Node *newNode = new Node();
        newNode->data = data;
        newNode->isDeleted = false;
        
        Node *firstActive = head->next;
        newNode->next = firstActive;
        newNode->prev = head;
        firstActive->prev = newNode;
        head->next = newNode;
        
        activeCount++;
    }
    
    // Push to back
    void push_back(T data) {
        Node *newNode = new Node();
        newNode->data = data;
        newNode->isDeleted = false;
        
        Node *lastActive = tail->prev;
        newNode->prev = lastActive;
        newNode->next = tail;
        lastActive->next = newNode;
        tail->prev = newNode;
        
        activeCount++;
    }
    
    // Get front element (skip deleted)
    T& front() {
        if (empty()) {
            std::cerr << "LazyList::front(): List is empty\n";
            exit(1);
        }
        Node *current = head->next;
        while (current != tail && current->isDeleted) {
            current = current->next;
        }
        if (current == tail) {
            std::cerr << "LazyList::front(): No active elements\n";
            exit(1);
        }
        return current->data;
    }
    
    // Get back element (skip deleted)
    T& back() {
        if (empty()) {
            std::cerr << "LazyList::back(): List is empty\n";
            exit(1);
        }
        Node *current = tail->prev;
        while (current != head && current->isDeleted) {
            current = current->prev;
        }
        if (current == head) {
            std::cerr << "LazyList::back(): No active elements\n";
            exit(1);
        }
        return current->data;
    }
    
    // LAZY DELETION: Mark item as deleted
    void pop_front() {
        if (empty()) {
            std::cerr << "pop_front(): Attempt to pop from empty list.\n";
            return;
        }
        
        // Find first non-deleted node
        Node *current = head->next;
        while (current != tail && current->isDeleted) {
            current = current->next;
        }
        
        if (current != tail) {
            current->isDeleted = true;
            activeCount--;
            deletedCount++;
            
            // Check if we need to purge
            if (deletedCount >= activeCount && activeCount > 0) {
                purgeDeletedNodes();
            }
        }
    }
    
    // LAZY DELETION: Mark item as deleted
    void pop_back() {
        if (empty()) {
            std::cerr << "pop_back(): Attempt to pop from empty list.\n";
            return;
        }
        
        // Find last non-deleted node
        Node *current = tail->prev;
        while (current != head && current->isDeleted) {
            current = current->prev;
        }
        
        if (current != head) {
            current->isDeleted = true;
            activeCount--;
            deletedCount++;
            
            // Check if we need to purge
            if (deletedCount >= activeCount && activeCount > 0) {
                purgeDeletedNodes();
            }
        }
    }
    
    // Get size (only non-deleted items)
    int size() const {
        return activeCount;
    }
    
    // Get count of deleted items
    int getDeletedCount() const {
        return deletedCount;
    }
    
    // Traverse (skip deleted items)
    void traverse(std::function<void(T&)> doIt) {
        Node *current = head->next;
        while (current != tail) {
            if (!current->isDeleted) {
                doIt(current->data);
            }
            current = current->next;
        }
    }
    
    // Force purge of deleted nodes (for testing)
    void forcePurge() {
        purgeDeletedNodes();
    }
};