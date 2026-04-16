#include <iostream>
#include "hashtable.hpp"

using namespace std;

struct Record {
    int key;
    string value;
};

void printResult(bool found, Record& result) {
    if (found) {
        cout << "Found - Key: " << result.key << " Value: " << result.value << "\n";
    } else {
        cout << "Not found\n";
    }
}

int main() {
    cout << "Hash Table Test\n";
    cout << "===============\n\n";

    Record r1 = {1,    "Alice"};
    Record r2 = {2,    "Bob"};
    Record r3 = {812,  "Charlie"};
    Record r4 = {1623, "Diana"};
    Record r5 = {5,    "Eve"};
    Record r6 = {10,   "Frank"};

    bool found;
    Record result;

    // -------------------------
    // Test 1: Linear (default)
    // -------------------------
    HashTable<Record> table1;

    table1.insert(r1);
    table1.insert(r2);
    table1.insert(r3);
    table1.insert(r4);
    table1.insert(r5);
    table1.insert(r6);

    cout << "Inserted 6 records. Table size: " << table1.size() << "\n\n";

    cout << "Test 1: Default findIndex\n";
    cout << "-------------------------\n";

    table1.find(1, found, result);
    cout << "Search for key 1: "; printResult(found, result);

    table1.find(812, found, result);
    cout << "Search for key 812: "; printResult(found, result);

    table1.find(1623, found, result);
    cout << "Search for key 1623: "; printResult(found, result);

    table1.find(999, found, result);
    cout << "Search for key 999: "; printResult(found, result);

    cout << "\n";

    // -------------------------
    // Test 2: Quadratic
    // -------------------------
    HashTable<Record> table2;

    auto quad = [&table2](int k, size_t c) {
        return table2.quadraticProbe(k, c);
    };

    table2.insert(r1, quad);
    table2.insert(r2, quad);
    table2.insert(r3, quad);
    table2.insert(r4, quad);
    table2.insert(r5, quad);
    table2.insert(r6, quad);

    cout << "Test 2: Quadratic Probe\n";
    cout << "-----------------------\n";

    table2.find(1, found, result, quad);
    cout << "Search for key 1: "; printResult(found, result);

    table2.find(812, found, result, quad);
    cout << "Search for key 812: "; printResult(found, result);

    table2.find(1623, found, result, quad);
    cout << "Search for key 1623: "; printResult(found, result);

    table2.find(999, found, result, quad);
    cout << "Search for key 999: "; printResult(found, result);

    cout << "\n";

    // -------------------------
    // Test 3: Double Hashing
    // -------------------------
    HashTable<Record> table3;

    auto dbl = [&table3](int k, size_t c) {
        return table3.secondHash(k, c);
    };

    table3.insert(r1, dbl);
    table3.insert(r2, dbl);
    table3.insert(r3, dbl);
    table3.insert(r4, dbl);
    table3.insert(r5, dbl);
    table3.insert(r6, dbl);

    cout << "Test 3: Second Hash h2(x) = 7 - (x mod 7)\n";
    cout << "-------------------------------------------\n";

    table3.find(1, found, result, dbl);
    cout << "Search for key 1: "; printResult(found, result);

    table3.find(812, found, result, dbl);
    cout << "Search for key 812: "; printResult(found, result);

    table3.find(1623, found, result, dbl);
    cout << "Search for key 1623: "; printResult(found, result);

    table3.find(999, found, result, dbl);
    cout << "Search for key 999: "; printResult(found, result);

    cout << "\n";

    // -------------------------
    // Test 4: Remove
    // -------------------------
    cout << "Test 4: Remove behavior\n";
    cout << "-----------------------\n";

    cout << "Removing key 2...\n";
    table1.remove(2);

    cout << "Table size after remove: " << table1.size() << "\n";

    table1.find(2, found, result);
    cout << "Search for key 2 after remove: "; printResult(found, result);

    cout << "\n";

    cout << "Hash table test complete!\n";

    return 0;
}