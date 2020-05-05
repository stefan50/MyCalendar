#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <functional>

template <class T>
class Vector {
private:
    T* elements;
    int size;
    int capacity;
    void erase() {
        delete[] elements;
    }
    void copy(const Vector& other) {
        capacity = other.capacity;
        size = other.size;
        elements = new T[capacity];
        for(int i = 0; i < size; i++) {
            elements[i] = other.elements[i];
        }
    }
    void resize() {
        capacity *= 2;
        T* new_els = new T[capacity];
        for(int i = 0; i < size; i++) {
            new_els[i] = elements[i]; 
        }
        erase();
        elements = new_els;
    }
public:
    Vector() {
        capacity = 16;
        size = 0;
        elements = new T[capacity];
    }
    Vector(const Vector& other) {
        copy(other);
    }
    Vector& operator=(const Vector& other) {
        if(this != &other) {
            erase();
            copy(other);
        }
        return *this;
    }

    T& operator[](int i) {
        return elements[i]; 
    }

    void sort(std::function<bool(T, T)> comparator_function) {
        for(int i = 0; i < size - 1; i++) {
            for(int j = 0; j < size - i - 1; j++) {
                if(comparator_function(elements[j], elements[j + 1]) == false) {
                    T element = elements[j];
                    elements[j] = elements[j + 1];
                    elements[j + 1] = element;
                }
            }
        }
    }

    int add_element(T element, std::function<bool(T, T)> comparator_function) {
        if(size >= capacity) {
            resize();
        }
        /*for(int i = 0; i < size; i++) {
            if(set[i] == el) {
                return -1;
            }
        }*/
        elements[size++] = element;
        sort(comparator_function);
        return 0;
    }

    T remove_element(T element, std::function<bool(T, T)> comparator_function) {
        Vector temp;
        for(int i = 0; i < size; i++) {
            if(elements[i] != element) {
                temp.add_element(elements[i], comparator_function);
            }
        }
        size--;
        erase();
        copy(temp);
        return element;
    }

    int get_size() const {
        return size;
    }

    T find_element(T element) {
        for(int i = 0; i < size; i++) {
            if(elements[i] == element) {
                return elements[i];
            }
        }   
    }
};

#endif