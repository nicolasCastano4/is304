#include <iostream>
#include <cassert>

using namespace std;

template<typename T>
class Vector {
private:
    T* storage;
    unsigned int cap;
    unsigned int sz;
public:
    Vector() {
        cap = 5;
        storage = new T[cap];
        sz = 0;
    }
    Vector(unsigned int c) {
        cap = c;
        storage = new T[cap];
        sz = 0;
    }
    ~Vector() {
        delete [] storage;
    }
    unsigned int size() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    unsigned int capacity() const {
        return cap;
    }
    
    void push_back(T elem) {
        resize();
        storage[sz] = elem;
        sz++;
    }
    
    void pop_back() {
      assert(!empty());
      sz--;
    }

    const T& front() const {
        assert(!empty());
        return storage[0];
    }

    T& front() {
        assert(!empty());
        return storage[0];
    }

    const T& back() const {
        assert(!empty());
        return storage[sz-1];
    }
  
    T& back() {
        assert(!empty());
        return storage[sz-1];
    }

    const T& at(unsigned int pos) const {
        assert(pos < sz);
        return storage[pos];
    }

    T& at(unsigned int pos) {
        assert(pos < sz);
        return storage[pos];
    }

    const T& operator[](unsigned int pos) const {
        return storage[pos];
    }

    T& operator[](unsigned int pos) {
        return storage[pos];
    }

    void shrink_to_fit() {
        if (sz == cap) return;
        T* newStorage = new T[sz];
        for(unsigned int i = 0; i < sz; i++) {
            newStorage[i] = storage[i];
        }
        delete [] storage;
        storage = newStorage;
        cap = sz;
    }
    
private:
    void resize() {
        if (sz == cap) {
            unsigned int newCapacity = cap * 1.5;
            T* newStorage = new T[newCapacity];
            for(unsigned int i = 0; i < sz; i++) {
                newStorage[i] = storage[i];
            }
            delete [] storage;
            storage = newStorage;
            cap = newCapacity;
        }
    }
public:
    void print() const {
        cout << "{";
        for(unsigned int i = 0; i < sz; i++) {
            cout << storage[i] << " ";
        }
        cout << "}" << endl;
    }

};


int main() {
    Vector<int> v(4532);
    for(int i = 0; i < 11; i++) {
        v.push_back(i*10);
    }
    v.print();
    cout << v.front() << endl;
    cout << v.back() << endl;
    cout << v.at(5) << endl;
    
    v.back() = 200;
    v.at(5) = 10000;
    v.print();
    
    v[4533] = 10;
    


    return 0;    
}