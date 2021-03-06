#ifndef NODE_CPP
#define NODE_CPP
#pragma once

#include <iostream>
enum n
{
    rightCH,
    leftCH,
    both
};

template <typename T>
class BSTNode
{
private:
    BSTNode<T> *children[2];
    T value;

public:
    BSTNode(const BSTNode<T> &obj);
    BSTNode(BSTNode<T> &&obj);
    BSTNode(T value);
    ~BSTNode();
    void put(T value);
    BSTNode<T> **getChildren();
    T getValue();
    T *getDataPointer(); //todo
    bool bothChildren();
    bool oneChildren();
    bool noChildren();
    int whichChildren();
    bool operator==(const BSTNode<T> &node) const;
};

template <typename T>
BSTNode<T>::BSTNode(T data) : value(data)
{
    children[rightCH] = nullptr;
    children[leftCH] = nullptr;
}

template <typename T>
BSTNode<T>::~BSTNode()
{
    delete children[rightCH];
    delete children[leftCH];
}
template <typename T>
BSTNode<T>::BSTNode(const BSTNode<T> &obj) : value(obj.value)
{
    // value = obj.value;
    children[rightCH] = nullptr;
    children[leftCH] = nullptr;
    if (obj.children[rightCH] != nullptr)
        this->children[rightCH] = new BSTNode<T>(*obj.children[rightCH]);
    if (obj.children[leftCH] != nullptr)
        this->children[leftCH] = new BSTNode<T>(*obj.children[leftCH]);
}
template <typename T>
BSTNode<T>::BSTNode(BSTNode<T> &&obj)
{
    this->data = obj.value;
    this->children = obj.children;
    obj.children[rightCH] = nullptr;
    obj.children[leftCH] = nullptr;
}
template <typename T>
void BSTNode<T>::put(T __data)
{
    children[__data < this->value] = new BSTNode<T>(__data);
}
template <typename T>
BSTNode<T> **BSTNode<T>::getChildren()
{
    return children;
}
template <typename T>
T BSTNode<T>::getValue()
{
    return value;
}
template <typename T>
T* BSTNode<T>::getDataPointer()
{
    return &value;
}
template <typename T>
bool BSTNode<T>::bothChildren()
{
    return (children[rightCH] != nullptr && children[leftCH] != nullptr);
}
template <typename T>
bool BSTNode<T>::oneChildren()
{
    return ((children[rightCH] != nullptr) ^ (children[leftCH] != nullptr));
}
template <typename T>
bool BSTNode<T>::noChildren()
{
    return (children[rightCH] == nullptr && children[leftCH] == nullptr);
}
template <typename T>
int BSTNode<T>::whichChildren()
{
    if (bothChildren())
        return both;
    if (noChildren())
        return -1;
    if (children[rightCH] != nullptr)
        return rightCH;
    if (children[leftCH] != nullptr)
        return leftCH;
    return -1;
}
template <typename T>
bool BSTNode<T>::operator==(const BSTNode<T> &node) const
{
    if ((children[rightCH] != nullptr && node.children[rightCH] == nullptr) || (children[rightCH] == nullptr && node.children[rightCH] != nullptr))
        return false;

    if ((children[leftCH] != nullptr && node.children[leftCH] == nullptr) || (children[leftCH] == nullptr && node.children[leftCH] != nullptr))
        return false;

    else if (children[rightCH] == nullptr && node.children[rightCH] == nullptr && children[1] == nullptr && node.children[1] == nullptr)
        return true;

    else if (children[rightCH] == nullptr && node.children[rightCH] == nullptr)
        return *children[leftCH] == *(node.children[leftCH]);
    
    else if (children[leftCH] == nullptr && node.children[leftCH] == nullptr)
        return *children[rightCH] == *(node.children[rightCH]);
    
    else if (value == node.value)
        return (*children[rightCH] == *(node.children[rightCH]) && *children[leftCH] == *(node.children[leftCH]));
    else
        return false;
}

#endif // !NODE_CPP
