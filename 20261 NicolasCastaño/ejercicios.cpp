#include <iostream>
#include <cassert>
#include <string>
#include <type_traits> // Necesario para declval en map()

using namespace std;

template<typename T>
class Vector {
private:
    T* storage;
    unsigned int cap;
    unsigned int sz;

    // Método auxiliar para QuickSort (Ejercicio 2.16)
    int partition(int low, int high) {
        T pivot = storage[high];
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (storage[j] < pivot) {
                i++;
                swap(i, j);
            }
        }
        swap(i + 1, high);
        return (i + 1);
    }

    void quickSort(int low, int high) {
        if (low < high) {
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }

public:
    Vector() {
        cap = 5;
        storage = new T[cap];
        sz = 0;
    }
    
    Vector(unsigned int c) {
        cap = c > 0 ? c : 5;
        storage = new T[cap];
        sz = 0;
    }
    
    ~Vector() {
        delete[] storage;
    }

    // --- EJERCICIO 2.19: Operador de asignación ---
    Vector<T>& operator=(const Vector<T>& other) {
        if (this != &other) { // Evitar autoasignación
            delete[] storage;
            cap = other.cap;
            sz = other.sz;
            storage = new T[cap];
            for (unsigned int i = 0; i < sz; i++) {
                storage[i] = other.storage[i];
            }
        }
        return *this;
    }

    unsigned int size() const { return sz; }
    bool empty() const { return sz == 0; }
    unsigned int capacity() const { return cap; }

    void push_back(const T& elem) {
        resize();
        storage[sz] = elem;
        sz++;
    }

    void pop_back() {
        assert(!empty());
        sz--;
    }

    // Faltantes de la API Básica (Parte 1)
    void push_front(const T& elem) { insert(0, elem); }
    
    void pop_front() {
        assert(!empty());
        erase(0);
    }

    void insert(unsigned int pos, const T& elem) {
        assert(pos <= sz);
        resize();
        for (unsigned int i = sz; i > pos; i--) {
            storage[i] = storage[i - 1];
        }
        storage[pos] = elem;
        sz++;
    }

    const T& front() const { assert(!empty()); return storage[0]; }
    T& front() { assert(!empty()); return storage[0]; }
    const T& back() const { assert(!empty()); return storage[sz - 1]; }
    T& back() { assert(!empty()); return storage[sz - 1]; }

    const T& at(unsigned int pos) const {
        assert(pos < sz);
        return storage[pos];
    }
    
    T& at(unsigned int pos) {
        assert(pos < sz);
        return storage[pos];
    }

    const T& operator[](unsigned int pos) const { return storage[pos]; }
    T& operator[](unsigned int pos) { return storage[pos]; }

    // --- PARTE 2: Extendiendo la clase ---

    // Ejercicio 2.1
    void erase(unsigned int pos) {
        assert(pos < sz);
        for (unsigned int i = pos; i < sz - 1; i++) {
            storage[i] = storage[i + 1];
        }
        sz--;
    }

    // Ejercicio 2.2
    void erase(unsigned int from, unsigned int to) {
        assert(from <= to && to <= sz);
        unsigned int elementsToRemove = to - from;
        for (unsigned int i = to; i < sz; i++) {
            storage[i - elementsToRemove] = storage[i];
        }
        sz -= elementsToRemove;
    }

    // Ejercicio 2.3
    void clear() { sz = 0; }

    // Ejercicio 2.5
    int find(const T& elem) const {
        for (unsigned int i = 0; i < sz; i++) {
            if (storage[i] == elem) return i;
        }
        return -1;
    }

    // Ejercicio 2.4 (Reescrito usando find)
    bool contains(const T& elem) const {
        return find(elem) != -1;
    }

    // Ejercicio 2.6
    void remove(const T& elem) {
        int pos = find(elem);
        if (pos != -1) erase(pos);
    }

    // Ejercicio 2.7
    void replace(const T& oldVal, const T& newVal) {
        int pos = find(oldVal);
        if (pos != -1) storage[pos] = newVal;
    }

    // Ejercicio 2.8
    void remove_all(const T& elem) {
        unsigned int w = 0;
        for (unsigned int i = 0; i < sz; i++) {
            if (storage[i] != elem) {
                storage[w] = storage[i];
                w++;
            }
        }
        sz = w;
    }

    // Ejercicio 2.9
    void replace_all(const T& oldVal, const T& newVal) {
        for (unsigned int i = 0; i < sz; i++) {
            if (storage[i] == oldVal) storage[i] = newVal;
        }
    }

    // Ejercicio 2.11
    Vector<int> indices_of(const T& elem) const {
        Vector<int> result;
        for (unsigned int i = 0; i < sz; i++) {
            if (storage[i] == elem) result.push_back(i);
        }
        return result;
    }

    // Ejercicio 2.10
    unsigned int count(const T& elem) const {
        return indices_of(elem).size();
    }

    // Ejercicio 2.12
    void swap(unsigned int i, unsigned int j) {
        assert(i < sz && j < sz);
        if (i == j) return;
        T tmp = storage[i];
        storage[i] = storage[j];
        storage[j] = tmp;
    }

    // Ejercicio 2.13
    void reverse() {
        for (unsigned int i = 0; i < sz / 2; i++) {
            swap(i, sz - 1 - i);
        }
    }

    // Ejercicio 2.14
    void rotate_left(unsigned int k) {
        if (sz == 0) return;
        k = k % sz;
        if (k == 0) return;
        
        // Invertir las 3 partes para lograr la rotación In-Place
        auto reverse_range = [&](unsigned int start, unsigned int end) {
            while (start < end) { swap(start++, end--); }
        };
        reverse_range(0, k - 1);
        reverse_range(k, sz - 1);
        reverse_range(0, sz - 1);
    }

    // Ejercicio 2.15
    void rotate_right(unsigned int k) {
        if (sz == 0) return;
        k = k % sz;
        if (k == 0) return;
        rotate_left(sz - k);
    }

    // Ejercicio 2.16
    void sort() {
        if (sz > 1) quickSort(0, sz - 1);
    }

    // Ejercicio 2.17
    void append(const Vector<T>& other) {
        if (this == &other) { // Manejo de edge case: self-append
            Vector<T> copy = other;
            for (unsigned int i = 0; i < copy.size(); i++) push_back(copy[i]);
        } else {
            for (unsigned int i = 0; i < other.size(); i++) push_back(other[i]);
        }
    }

    // Ejercicio 2.18
    Vector<T> slice(unsigned int from, unsigned int to) const {
        assert(from <= to && to <= sz);
        Vector<T> result;
        for (unsigned int i = from; i < to; i++) {
            result.push_back(storage[i]);
        }
        return result;
    }

    // --- PARTE 3: Predicados y Programación Funcional ---

    // Ejercicio 3.1
    template <typename Predicate>
    bool any(Predicate p) const {
        for (unsigned int i = 0; i < sz; i++) {
            if (p(storage[i])) return true;
        }
        return false;
    }

    // Ejercicio 3.2
    template <typename Predicate>
    bool all(Predicate p) const {
        for (unsigned int i = 0; i < sz; i++) {
            if (!p(storage[i])) return false;
        }
        return true;
    }

    // Ejercicio 3.3
    template <typename Predicate>
    bool none(Predicate p) const {
        return !any(p);
    }

    // Ejercicio 3.4
    template <typename Predicate>
    Vector<T> filter(Predicate p) const {
        Vector<T> result;
        for (unsigned int i = 0; i < sz; i++) {
            if (p(storage[i])) result.push_back(storage[i]);
        }
        return result;
    }

    // Ejercicio 3.5 (Parte B - Salida genérica)
    template <typename Function>
    auto map(Function f) const -> Vector<decltype(f(declval<T>()))> {
        using R = decltype(f(declval<T>()));
        Vector<R> result;
        for (unsigned int i = 0; i < sz; i++) {
            result.push_back(f(storage[i]));
        }
        return result;
    }

    // Ejercicio 3.6
    template <typename Function>
    void for_each(Function f) {
        for (unsigned int i = 0; i < sz; i++) {
            f(storage[i]);
        }
    }

    void shrink_to_fit() {
        if (sz == cap) return;
        cap = (sz > 0) ? sz : 1; // Manejo del caso donde sz = 0 (Ej. 4.3)
        T* newStorage = new T[cap];
        for(unsigned int i = 0; i < sz; i++) {
            newStorage[i] = storage[i];
        }
        delete[] storage;
        storage = newStorage;
    }
    
private:
    void resize() {
        if (sz == cap) {
            // Crecimiento corregido según la fórmula del lab (Ej. 4.2)
            unsigned int newCapacity = (cap * 3) / 2 + 1;
            T* newStorage = new T[newCapacity];
            for(unsigned int i = 0; i < sz; i++) {
                newStorage[i] = storage[i];
            }
            delete[] storage;
            storage = newStorage;
            cap = newCapacity;
        }
    }

public:
    void print() const {
        cout << "{ ";
        // Revertido al bucle clásico sin usar iteradores
        for (unsigned int i = 0; i < sz; i++) {
            cout << storage[i] << " ";
        }
        cout << "}" << endl;
    }
};

int main() {
    cout << "--- EJERCICIO 1.1: Operaciones basicas ---" << endl;
    Vector<int> v;
    for(int i = 1; i <= 10; i++) v.push_back(i); // 1. Push 1-10
    
    // 2. Imprimir
    v.print(); 
    cout << "Size: " << v.size() << ", Capacity: " << v.capacity() << endl;
    
    // 3. Remover primero y ultimo
    v.pop_front(); 
    v.pop_back();
    v.print();
    
    // 4. Insertar 99 en index 2
    v.insert(2, 99);
    v.print();

    cout << "\n--- EJERCICIO 1.2: Metodos de acceso ---" << endl;
    Vector<int> v2;
    v2.push_back(5); v2.push_back(10); v2.push_back(15); v2.push_back(20); v2.push_back(25);
    cout << "Front: " << v2.front() << ", Back: " << v2.back() << endl; // 1
    cout << "Middle (at 2): " << v2.at(2) << endl; // 2
    v2[1] = 100; // 3
    v2.print();

    cout << "\n--- EJERCICIO 1.3: Strings ---" << endl;
    Vector<string> vs;
    vs.push_back("the"); vs.push_back("quick"); vs.push_back("brown"); 
    vs.push_back("fox"); vs.push_back("jumps");
    vs.print();
    
    return 0;
}