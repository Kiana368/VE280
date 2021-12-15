//
// Created by junsi on 2021/7/20.
//

#ifndef P5_DLISTIMPL_H
#define P5_DLISTIMPL_H

#include <iostream>
#include "Dlist.h"
using namespace std;

template<class T>
bool Dlist<T>::isEmpty() const {
    return first == nullptr;
}

template<class T>
void Dlist<T>::insertFront(T *op) {
    node *new_node = new node;
    new_node->op = op;
    new_node->next = first;
    new_node->prev = nullptr;
    if (isEmpty()) {
        first = new_node;
        last = new_node;
    } else {
        first->prev=new_node;
        first=new_node;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    node *new_node = new node;
    new_node->op = op;
    new_node->prev = last;
    new_node->next = nullptr;
    if (isEmpty()) {
        first = new_node;
        last = new_node;
    } else {
        last->next=new_node;
        last=new_node;
    }
}

template<class T>
T *Dlist<T>::removeFront() {
    if (isEmpty()){
        throw EmptyList{};
    }else{
        node *victim=first;
        T *vic_val=victim->op;
        first=first->next;
        if (first== nullptr){
            last= nullptr;
        }else{
            first->prev= nullptr;
        }
        delete victim;
        return vic_val;
    }
}

template<class T>
T *Dlist<T>::removeBack() {
    if (isEmpty()){
        throw EmptyList{};
    }else{
        node *victim=last;
        T *vic_val;
        vic_val=victim->op;
        last=last->prev;
        if (last== nullptr){
            first= nullptr;
        }else{
            last->next= nullptr;
        }
        delete victim;
        return vic_val;
    }
}

template<class T>
Dlist<T>::Dlist() {
    first= nullptr;
    last= nullptr;
}

template<class T>
Dlist<T>::Dlist(const Dlist &l) {
    first= nullptr;
    last= nullptr;
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l) {
    if (this!=&l) {
        removeAll();
        copyAll(l);
    }
    return *this;
}

template<class T>
Dlist<T>::~Dlist() {
    removeAll();
}

template<class T>
void Dlist<T>::removeAll() {
    if (isEmpty()) return;
    node *temp;
    while (first!= nullptr){
        temp=first;
        first=first->next;
        delete temp->op;
        delete temp;
    }
    last= nullptr;
}

template<class T>
void Dlist<T>::copyAll(const Dlist &l) {
    removeAll();
    node *temp=l.first;
    while (temp!= nullptr){
        insertBack(new T(*temp->op));
        temp=temp->next;
    }
}

#endif //P5_DLISTIMPL_H
