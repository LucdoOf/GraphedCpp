//
// Created by lucas on 12/05/2021.
//

#include <malloc.h>

#ifndef GRAPHEDCPP_CLIST_H
#define GRAPHEDCPP_CLIST_H

#endif //GRAPHEDCPP_CLIST_H

template<typename T>
class CList {

public:
    CList();
    ~CList();
    inline T get(int index);
    void add(T item);
    void remove(T item);
    void removeAt(int index);
    int indexOf(T item);
    bool contains(T item);
    inline int getSize();
    T shift(int index);
    inline T shift();

private:
    void reallocItems();
    int size;
    T** items;

};


template<typename T>
CList<T>::CList() {
    this->size = 0;
    this->items = malloc(sizeof(T));
}

template<typename T>
CList<T>::~CList() {
    delete this->items;
}

template<typename T>
void CList<T>::add(T item) {
    this->size++;
    this->reallocItems();
    this->items[this->getSize() - 1] = item;
}

template<typename T>
void CList<T>::remove(T item) {
    this->shift(this->indexOf(item));
}

template<typename T>
void CList<T>::removeAt(int index) {
    this->shift(index);
}

template<typename T>
int CList<T>::indexOf(T item) {
    for (int i = 0; i < size; i++) {
        if (this->items[i] == item) return i;
    }
    return -1;
}

template<typename T>
inline int CList<T>::getSize() {
    return this->size;
}

template<typename T>
T CList<T>::shift(int index) {
    T toReturn = this->get(index);
    for (int i = index; i < this->getSize(); i++) {
        this->items[i] = this->items[i+1];
    }
    this->size--;
    this->reallocItems();
    return toReturn;
}

template<typename T>
inline T CList<T>::get(int i) {
    return this->items(i);
}

template<typename T>
inline T CList<T>::shift() {
    return this->shift(0);
}

template<typename T>
void CList<T>::reallocItems() {
    realloc(this->items, this->size * sizeof(T));
}

template<typename T>
bool CList<T>::contains(T item) {
    return this->indexOf(item) >= 0;
}




