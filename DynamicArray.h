//
// Created by bozhidar on 5/14/20.
//

#ifndef TABLEREADING_DYNAMICARRAY_H
#define TABLEREADING_DYNAMICARRAY_H

template <typename T>
struct DynamicArray {
private:
    T* array;
    unsigned size{};
public:
    DynamicArray() = default;
    explicit DynamicArray(unsigned n) : array{new T[n]}, size{n} {}
    ~DynamicArray() { delete[] array; }

    unsigned getSize() { return this->size; }
    T& operator[](unsigned i) { return array[i]; }
    void push(const T& newElement){
        T* extended = new T[size + 1];
        for (int i = 0; i < size; ++i){
            extended[i] = array[i];
        }
        extended[size] = newElement;
        delete[] array;
        size++;
        array = extended;
    }
    void deleteAt(unsigned n){
        T* shrunken = new T[size - 1];
        for (int i = 0; i < size; ++i) {
            if (i < n) shrunken[i] = array[i];
            if (i > n) shrunken[i - 1] = array[i];
        }
        delete[] array;
        size--;
        array = shrunken;
    }
};

#endif //TABLEREADING_DYNAMICARRAY_H
