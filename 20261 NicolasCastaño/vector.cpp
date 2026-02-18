#include <iostream>

using namespace std;

class Vector {
private:
    int* storage;
    unsigned int capacity;
    unsigned int sz;
public:
    Vector() {
        capacity = 5;
        storage = new int[capacity];
        sz = 0;
    }
    unsigned int size() {
        return sz;
    }
    void push_back(int elem) {
        resize();
        storage[sz] = elem;
        sz++;
    }
   
private:
    void resize() {
        if (sz == capacity) {
            // El arreglo esta lleno
            unsigned int newCapacity = capacity * 1.5;
            int* newStorage = new int[newCapacity];
            for(unsigned int i = 0; i < sz; i++) {
                newStorage[i] = storage[i];
            }
            delete [] storage;
            storage = newStorage;
            capacity = newCapacity;
        }
    }
};

int main() {
    Vector v;
    for(int i = 0; i < 11; i++) {
        v.push_back(i*10);
    }
    cout << v.size() << endl;
    return 0;    
}