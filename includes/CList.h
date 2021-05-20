//
// Created by lucas on 12/05/2021.
//

#include <malloc.h>

#ifndef GRAPHEDCPP_CLIST_H
#define GRAPHEDCPP_CLIST_H

#endif //GRAPHEDCPP_CLIST_H

/**
 * CList class
 *
 * Very basic list c++ implementation.
 * CList objects works with pointers, if an object from the list is deleted by an external stack,
 * behaviors may be undefined in some case.
 *
 * @warning This class is experimental, so it is not completely memory-leak-free / memory-access-error-free.
 * We know this class is not stable and have a lot of breaches, it's just for educational purposes, we didn't had
 * enough time to develop it more.
 * @tparam T Type of objects in the list
 */
template<typename T>
class CList {

public:
    /**
     * CList constructor
     */
    CList();
    /**
     * CList copy constructor
     *
     * Copy all of the list items into the new one, calling their copy constructors
     */
    CList(CList<T>&);
    /**
     * CList destructor
     */
    ~CList();
    /**
     * Retrieves an item from the list at the given index
     *
     * @param index Item index
     * @return An item from the list at the given index
     */
    T* get(int index);
    /**
     * Add an item to the list, its memory should now be completely handled by the list.
     * The item will be appended at the end of the list
     *
     * @param item Item to append to the list
     */
    void add(T* item);
    /**
     * Remove the given from the list. Don't remove everything if not contained.
     *
     * @param item Item to remove from the list
     */
    void remove(T* item);
    /**
     * Remove the item at the given index
     *
     * @param index Index where the item will be removed
     */
    void removeAt(int index);
    /**
     * Retrieves the index of the given item in the list
     *
     * @param item Item to find the index in the list
     * @return The index of the given item in the list
     */
    int indexOf(T* item);
    /**
     * Determines whether the given item is in the list whether it is not in the list
     *
     * @param item The item to check if it is in the list
     * @return Whether the given item is in the list whether it is not in the list
     */
    bool contains(T* item);
    /**
     * Retrieves the list size
     *
     * @return The list size
     */
    inline int getSize();
    /**
     * Shift the list from the given index and returns the the shifted item
     *
     * @param index Shift index
     * @return The shifted item at the given index
     */
    T* shift(int index);
    /**
     * Shift the list from the first index
     *
     * @return The first list shifted item
     */
    T* shift();

private:
    /**
     * Realloc the items array to the actual list size
     */
    void reallocItems();
    // int previousSize = 0;
    /**
     * Actual array size
     */
    int size = 0;
    /**
     * Items array, handled with realloc in the reallocItems method
     */
    T** items;

};

/**
 * CList constructor
 */
template<typename T>
CList<T>::CList() {
    this->items = (T**) malloc(sizeof(T));
}

/**
 * CList copy constructor
 *
 * Copy all of the list items into the new one, calling their copy constructors
 */
template<typename T>
CList<T>::CList(CList<T> &list) {
    this->items = (T**) malloc(sizeof(T));
    for (int i = 0; i < list.getSize(); i++) {
        // Recopie necessaire, on fait appel au constructeur de recopie
        T* newInstance = new T(*list.get(i));
        this->add(newInstance);
    }
}

/**
 * CList destructor
 */
template<typename T>
CList<T>::~CList() {
    for (int i = 0; i < this->getSize(); i++) {
        delete this->get(i);
    }
    free(this->items);
}

/**
 * Retrieves an item from the list at the given index
 *
 * @param index Item index
 * @return An item from the list at the given index
 */
template<typename T>
T* CList<T>::get(int i) {
    return this->items[i];
}

/**
 * Add an item to the list, its memory should now be completely handled by the list.
 * The item will be appended at the end of the list
 *
 * @param item Item to append to the list
 */
template<typename T>
void CList<T>::add(T* item) {
    this->size++;
    this->reallocItems();
    this->items[this->getSize() - 1] = item;
}

/**
 * Remove the given from the list. Don't remove everything if not contained.
 *
 * @param item Item to remove from the list
 */
template<typename T>
void CList<T>::remove(T* item) {
    int index = this->indexOf(item);
    if (index >= 0) {
        this->shift(index);
    }
}

/**
 * Remove the item at the given index
 *
 * @param index Index where the item will be removed
 */
template<typename T>
void CList<T>::removeAt(int index) {
    this->shift(index);
}

/**
 * Retrieves the index of the given item in the list
 *
 * @param item Item to find the index in the list
 * @return The index of the given item in the list
 */
template<typename T>
int CList<T>::indexOf(T* item) {
    for (int i = 0; i < size; i++) {
        if (this->get(i) == item) return i;
    }
    return -1;
}

/**
 * Determines whether the given item is in the list whether it is not in the list
 *
 * @param item The item to check if it is in the list
 * @return Whether the given item is in the list whether it is not in the list
 */
template<typename T>
bool CList<T>::contains(T* item) {
    return this->indexOf(item) >= 0;
}

/**
 * Retrieves the list size
 *
 * @return The list size
 */
template<typename T>
inline int CList<T>::getSize() {
    return this->size;
}

/**
 * Shift the list from the given index and returns the the shifted item
 *
 * @param index Shift index
 * @return The shifted item at the given index
 */
template<typename T>
T* CList<T>::shift(int index) {
    T* toReturn = this->get(index);
    if (this->getSize() >= 1) {
        for (int i = index; i < this->getSize() - 1; i++) {
            this->items[i] = this->get(i + 1);
        }
        this->size--;
    }
    this->reallocItems();
    return toReturn;
}

/**
 * Shift the list from the first index
 *
 * @return The first list shifted item
 */
template<typename T>
T* CList<T>::shift() {
    return this->shift(0);
}

/**
 * Realloc the items array to the actual list size
 */
template<typename T>
void CList<T>::reallocItems() {
    // This code don't work without valgrind, don't know why,
    // it should normally fix a lot of memory issues in this class
    /*
    if (previousSize > size) {
        for (int i = size; i < previousSize; i++) {
            delete this->get(i);
        }
    }
    previousSize = size;
     */
    this->items = (T**) realloc(this->items, this->size * sizeof(T*));
}





