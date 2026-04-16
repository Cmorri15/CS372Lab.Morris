#pragma once
#include <functional>
#include <cassert>

template <class RecordType>
class HashTable {
public:
    static const std::size_t CAPACITY = 811;

    HashTable() : used(0) {
        for (std::size_t i = 0; i < CAPACITY; i++) {
            data[i].key = NEVERUSED;
        }
    }

    // INSERT with probing function
    void insert(const RecordType& entry,
        std::function<std::size_t(int, std::size_t)> probingFunction = nullptr) {

        assert(entry.key >= 0);

        std::size_t count = 0;
        std::size_t index;

        do {
            if (probingFunction) {
                index = probingFunction(entry.key, count);
            } else {
                index = (hash(entry.key) + count) % CAPACITY; // linear
            }

            if (isVacant(index)) {
                data[index] = entry;
                ++used;
                return;
            }

            ++count;

        } while (count < CAPACITY);

        assert(false); // table full
    }

    void remove(int key) {
        bool found;
        std::size_t index;

        findInternal(key, found, index, nullptr);

        if (found) {
            data[index].key = PREVIOUSLYUSED;
            --used;
        }
    }

    // FIND with probing function
    void find(int key, bool& found, RecordType& result,
        std::function<std::size_t(int, std::size_t)> probingFunction = nullptr) const {

        std::size_t index;
        findInternal(key, found, index, probingFunction);

        if (found) {
            result = data[index];
        }
    }

    std::size_t size() const { return used; }

    // Probing functions (clean version)
    std::size_t quadraticProbe(int key, std::size_t count) const {
        return (hash(key) + count * count) % CAPACITY;
    }

    std::size_t secondHash(int key, std::size_t count) const {
        std::size_t h2 = 7 - (key % 7);
        return (hash(key) + count * h2) % CAPACITY;
    }

    RecordType data[CAPACITY];

private:
    static const int NEVERUSED = -1;
    static const int PREVIOUSLYUSED = -2;

    std::size_t used;

    std::size_t hash(int key) const {
        return key % CAPACITY;
    }

    bool neverUsed(std::size_t index) const {
        return data[index].key == NEVERUSED;
    }

    bool isVacant(std::size_t index) const {
        return data[index].key < 0;
    }

    // Shared probing logic for find/remove
    void findInternal(int key, bool& found, std::size_t& index,
        std::function<std::size_t(int, std::size_t)> probingFunction) const {

        std::size_t count = 0;

        do {
            if (probingFunction) {
                index = probingFunction(key, count);
            } else {
                index = (hash(key) + count) % CAPACITY; // linear
            }

            if (neverUsed(index)) {
                found = false;
                return;
            }

            if (data[index].key == key) {
                found = true;
                return;
            }

            ++count;

        } while (count < CAPACITY);

        found = false;
    }
};