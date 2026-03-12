#pragma once
#include <iostream>
#include <functional>
#include <memory>

template <typename T>
class ListSmartPtr {
private:
    class Node {
    public:
        T data;
        std::shared_ptr<Node> prev;
        std::shared_ptr<Node> next;
        bool isHiddenNode = false;
        
        Node() = default;
    };
    
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    
    void deleteListContents() {
        // With smart pointers, we just need to break the chain
        // Reference counting will handle cleanup
        if (head) {
            head->next = nullptr;
        }
        if (tail) {
            tail->prev = nullptr;
        }
        head = nullptr;
        tail = nullptr;
    }

public:
    // Nested iterator classes
    class const_iterator {
    protected:
        std::shared_ptr<Node> current;
        T & retrieve() const { return current->data; }
        const_iterator(std::shared_ptr<Node> p) : current(p) { }
        friend class ListSmartPtr<T>;
        
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
        iterator(std::shared_ptr<Node> p) : const_iterator(p) { }
        friend class ListSmartPtr<T>;
        
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
    ListSmartPtr() {
        head = std::make_shared<Node>();
        head->isHiddenNode = true;
        tail = std::make_shared<Node>();
        tail->isHiddenNode = true;
        head->prev = nullptr;
        head->next = tail;
        tail->prev = head;
        tail->next = nullptr;
    }
    
    ListSmartPtr(T newData) : ListSmartPtr() {
        push_back(newData);
    }
    
    // Copy constructor
    ListSmartPtr(const ListSmartPtr &rhs) : ListSmartPtr() {
        auto curr = rhs.head->next;
        while (curr != rhs.tail) {
            push_back(curr->data);
            curr = curr->next;
        }
    }
    
    // Move constructor
    ListSmartPtr(ListSmartPtr&& rhs) noexcept 
        : head(std::move(rhs.head)), tail(std::move(rhs.tail)) {
        rhs.head = nullptr;
        rhs.tail = nullptr;
    }
    
    // Destructor
    ~ListSmartPtr() {
        deleteListContents();
    }
    
    // Copy assignment operator
    ListSmartPtr& operator=(const ListSmartPtr &rhs) {
        if (this != &rhs) {
            deleteListContents();
            head = std::make_shared<Node>();
            head->isHiddenNode = true;
            tail = std::make_shared<Node>();
            tail->isHiddenNode = true;
            head->prev = nullptr;
            head->next = tail;
            tail->prev = head;
            tail->next = nullptr;
            
            auto curr = rhs.head->next;
            while (curr != rhs.tail) {
                push_back(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }
    
    // Move assignment operator
    ListSmartPtr& operator=(ListSmartPtr&& rhs) noexcept {
        if (this != &rhs) {
            deleteListContents();
            head = std::move(rhs.head);
            tail = std::move(rhs.tail);
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
        auto newNode = std::make_shared<Node>();
        newNode->data = data;
        newNode->isHiddenNode = false;
        
        auto firstActive = head->next;
        newNode->next = firstActive;
        newNode->prev = head;
        firstActive->prev = newNode;
        head->next = newNode;
    }
    
    // Push to back
    void push_back(T data) {
        auto newNode = std::make_shared<Node>();
        newNode->data = data;
        newNode->isHiddenNode = false;
        
        auto lastActive = tail->prev;
        newNode->prev = lastActive;
        newNode->next = tail;
        lastActive->next = newNode;
        tail->prev = newNode;
    }
    
    // Get front element
    T& front() {
        if (empty()) {
            std::cerr << "ListSmartPtr::front(): List is empty\n";
            exit(1);
        }
        return head->next->data;
    }
    
    // Get back element
    T& back() {
        if (empty()) {
            std::cerr << "ListSmartPtr::back(): List is empty\n";
            exit(1);
        }
        return tail->prev->data;
    }
    
    // Pop from front
    void pop_front() {
        if (!empty()) {
            auto firstNode = head->next;
            head->next = firstNode->next;
            auto newFirstNode = head->next;
            newFirstNode->prev = head;
            // Smart pointer will automatically delete firstNode
        }
        else {
            std::cerr << "pop_front(): Attempt to pop from empty list.\n";
        }
    }
    
    // Pop from back
    void pop_back() {
        if (!empty()) {
            auto lastNode = tail->prev;
            tail->prev = lastNode->prev;
            auto newLastNode = tail->prev;
            newLastNode->next = tail;
            // Smart pointer will automatically delete lastNode
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
        auto current = head->next;
        while (current != tail) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    // Traverse with function
    void traverse(std::function<void(T&)> doIt) {
        auto current = head->next;
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
        auto p = pos.current;
        auto newNode = std::make_shared<Node>();
        newNode->data = x;
        newNode->next = p;
        newNode->prev = p->prev;
        p->prev->next = newNode;
        p->prev = newNode;
        return iterator(newNode);
    }
    
    // Erase at position
    iterator erase(iterator pos) {
        auto p = pos.current;
        iterator retVal(p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        // Smart pointer will auto-delete p
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