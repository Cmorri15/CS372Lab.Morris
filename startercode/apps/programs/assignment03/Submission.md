# Assignment 3 Submission

## Overview
This assignment implements a doubly-linked List class with full copy/move semantics, refactors the Bag class to use List instead of Vector, and creates a CircularList class through inheritance.

## Part 1: List Class Implementation

I implemented the List class based on the lecture notes with the following features:
- Doubly-linked list with hidden head and tail nodes
- Full iterator support (iterator and const_iterator)
- Copy constructor and copy assignment operator (deep copy)
- Move constructor and move assignment operator
- Standard operations: push_front, push_back, pop_front, pop_back, insert, erase

The hidden nodes simplify edge cases and make iterator implementation cleaner, particularly for the end() iterator which points to the hidden tail node.

## Part 2: Refactoring Bag to Use List

### Why Bag Can Use List but ReceiptBag Cannot

The regular Bag ADT only needs to store items and doesn't care about order or specific positions. We can use either Vector or List as the backing store because:
- Bags support simple insert and pop operations
- We don't need to access items by position
- We don't need parallel data structures

However, ReceiptBag cannot easily be refactored to use List because:
- ReceiptBag requires parallel data structures (one for items, one for receipts)
- We need random access to find and remove items by receipt number
- Lists don't provide efficient random access like vectors do
- The design specifically relies on keeping two parallel vectors in sync

### Implementation Changes

The refactored Bag class:
- Uses `List<Thing>` instead of `Vector<Thing>` as the backing store
- All operations work identically from the user's perspective
- Added move constructor and move assignment operator (following Rule of Five)
- The pop() operation is simpler now because List has a built-in pop_back() method

## Part 3: CircularList Implementation

### Design Decisions

I implemented CircularList through inheritance from List because:
- CircularList IS-A specialized List with additional behavior
- It doesn't change existing List behavior, only adds new functionality
- Inheritance allows reuse of all the existing List methods

### What Was Overridden

I overrode the `traverse()` method to add a circular version that:
- Takes an iterator as the starting position (instead of always starting at begin())
- Wraps around to the beginning when it reaches the end
- Stops when it returns to the starting position
- Uses a do-while loop to ensure we traverse the entire list exactly once

### What Changed in Base Class

I needed to make the traverse() method virtual in the base List class... actually, I didn't need to make it virtual because I used a different signature (takes an iterator parameter). This allows CircularList to have both:
- The regular traverse() inherited from List (no parameters, starts at beginning)
- The circular traverse() (takes starting iterator)

This design uses method overloading rather than overriding, which is cleaner and allows both behaviors to coexist.

### Testing

The circular traverse correctly:
- Starts at any given position in the list
- Wraps around from end to beginning
- Stops after visiting each element exactly once
- Works with any data type (tested with int and string)

## Code Organization

All files are in the repository:
- Header files: `startercode/include/list.hpp`, `bag.hpp`, `circularlist.hpp`
- Test programs: `startercode/apps/programs/assignment03/`
- All tests pass successfully

I had the help of Claude.ai while completing this assignment.