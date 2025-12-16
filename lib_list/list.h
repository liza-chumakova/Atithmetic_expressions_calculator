#pragma once
#include <iostream>

template <typename T>
struct Node {
    T _value;
    Node<T>* _next;
    Node(T value, Node<T>* next = nullptr): _value(value), _next(next) {}
};

template <typename T> class List;

template <class T>
class List {
    Node<T>* _head;
    Node<T>* _tail;
    int _count;

public:
    List();
    List(const List<T>& other);
    List(std::initializer_list<T> data);

    ~List();

    Node<T>* head() const;
    Node<T>* tail() const;
    int count() const;

    List<T>& operator=(const List<T>& other);

    bool operator==(const List& other) const;

    void push_front(const T& val) noexcept;
    void push_back(const T& val) noexcept;
    void insert(int pos, const T& val);
    void insert(Node<T>* node, const T& val);

    void pop_front();
    void pop_back();
    void pop(int pos);
    void pop(Node<T>* node);

    void erase();

    bool is_empty() const;

    Node<T>* find(const T& val);

    class Iterator {
        Node<T>* _current;
    public:
        Iterator() : _current(nullptr) {}
        Iterator(Node<T>* pos) : _current(pos) {}
        Iterator(const Iterator& other) : _current(other._current) {}

        Iterator& operator=(const Iterator& other);
        T& operator*();

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

        Iterator operator++(int); //x++
        Iterator& operator++();   //++x
    };

    class ConstIterator {
        const Node<T>* _current;
    public:
        ConstIterator() : _current(nullptr) {}
        ConstIterator(const Node<T>* pos) : _current(pos) {}
        ConstIterator(const ConstIterator& other) : _current(other._current) {}

        ConstIterator& operator=(const ConstIterator& other);
        const T& operator*() const;

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

        ConstIterator operator++(int); //x++
        ConstIterator& operator++();   //++x
    };

    Iterator begin() { return Iterator(_head); }
    Iterator end() {return Iterator(nullptr); }

    ConstIterator cbegin() const { return ConstIterator(_head); }
    ConstIterator cend() const {return ConstIterator(nullptr); }
};

template <class T>
List<T>::List() : _head(nullptr), _tail(nullptr), _count(0) {}

template <typename T>
List<T>::List(const List<T>& other) : _head(nullptr), _tail(nullptr), _count(0) {
    // Если другой список пуст, просто создаем пустой список
    if (other._head == nullptr) {
        return;
    }
    
    // Копируем первый элемент
    _head = new Node<T>(other._head->_value);
    Node<T>* current = _head;
    Node<T>* otherCurrent = other._head->_next;
    _count = 1;
    
    // Копируем остальные элементы
    while (otherCurrent != nullptr) {
        current->_next = new Node<T>(otherCurrent->_value);
        current = current->_next;
        otherCurrent = otherCurrent->_next;
        _count++;
    }
    
    // Устанавливаем хвост
    _tail = current;
}

template <typename T>
List<T>::List(std::initializer_list<T> data) 
    : _head(nullptr), _tail(nullptr), _count(0)
{
    for (auto it = data.begin(); it != data.end(); ++it) {
        this->push_back(*it);
    }
}

template <typename T>
List<T>::~List() {
    erase();
}

template <typename T>
Node<T>* List<T>::head() const {
    return _head;
}

template <typename T>
Node<T>* List<T>::tail() const {
    return _tail;
}

template <typename T>
int List<T>::count() const {
    return _count;
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other) {
    Node<T>* cur = other._head;
    int cur_pos = 0;
    while (cur != nullptr) {
        this->push_back(cur->_value);
        ++cur_pos;
        cur = cur->_next;
    }
    return *this;
}

template <typename T>
bool List<T>::operator==(const List& other) const {
    if(_count != other._count) { return false; }

    Node<T>* cur = _head;
    Node<T>* cur_other = other._head;
    int cur_pos = 0;
    while (cur != nullptr) {
        if (cur->value != cur_other->value) { return false; }
        //допроверка
        ++cur_pos;
        cur = cur->next;
        cur_other = cur_other->next;
    }

    return true;
}

template <typename T>
void List<T>::push_front(const T& val) noexcept {
    Node<T>* node = new Node<T>(val, _head);

    if(is_empty()) {
        _tail = node;
    }

    _head = node;
    ++_count;
}

template <typename T>
void List<T>::push_back(const T& val) noexcept {
    Node<T>* const node = new Node<T>(val);

    if(is_empty()) {
        _head = node;
        _tail = node;
        _count = 1;
        return;
    }

    _tail->_next = node;
    _tail = node;
    ++_count;
}

template <typename T>
void List<T>::insert(int pos, const T& val) {
    if(pos < 0 || pos >= _count) {
        throw std::logic_error("Index out of range");
    }
    if(pos == 0) {
        push_front(val);
    }
    else if(pos == _count - 1) {
        push_back(val);
    }
    else {
        Node<T>* cur = _head;
        int cur_pos = 0;
        while (cur != nullptr) {
            if (cur_pos == pos - 1) {
                break;
            }
            ++cur_pos;

            cur = cur->_next;
        }
        insert(cur, val);
    }
}

template <typename T>
void List<T>::insert(Node<T>* node, const T& val) {
    
    if (node == nullptr) {
        throw std::logic_error("Node error");
    }
    Node<T>* new_node = new Node<T>(val, node->_next);
    //if(_tail == node) {
        new_node->_next = node->_next;
        node->_next = new_node;
    //}

    if(node == _tail) {
        _tail = new_node;
    }
    ++_count;
}

template <typename T>
void List<T>::pop_front() {
    if(is_empty()) {
        throw std::logic_error("List is empty");
    }

    Node<T>* pr_node = _head;
    _head = _head->_next;
    delete pr_node;
    --_count;
}

template <typename T>
void List<T>::pop_back() {
    if(is_empty()) {
        throw std::logic_error("List is empty");
    }
    if(_count == 1) {
        Node<T>* pr_node = _head;
        _head = nullptr;
        _tail = nullptr;
        delete pr_node;
        --_count;
        return;
    }
    Node<T>* cur = _head;
    int cur_pos = 0;
    while (cur_pos < _count - 2) {
        if (cur_pos == _count - 1) {
            break;
        }
        ++cur_pos;
        cur = cur->_next;
    }
    Node<T>* pr_node = _tail;
    cur->_next = nullptr;
    _tail = cur;
    delete pr_node;
    --_count;
}

template <typename T>
void List<T>::pop(int pos) {
    if(pos < 0 || pos >= _count) {
        throw std::logic_error("Index out of range");
    }
    if(pos == 0) {
        pop_front();
    }
    else if(pos == _count - 1) {
        pop_back();
    }
    else {
        Node<T>* cur = _head;
        int cur_pos = 0;
        while (cur != nullptr) {
            if (cur_pos == pos - 1) {
                break;
            }
            ++cur_pos;
            cur = cur->_next;
        }

        if (cur == nullptr) {
            throw std::logic_error("Internal error");
        }

        Node<T>* pr_node = cur->_next;
        cur->_next = (cur->_next)->_next;
        delete pr_node;
        --_count;
    }
}

template <typename T>
void List<T>::pop(Node<T>* node) {
    Node<T>* cur = _head;
    int cur_pos = 0;
    while (cur != nullptr) {
        if (cur_pos == _count - 1) {
            break;
        }
        ++cur_pos;

        cur->_next = node->_next;
    }
    delete node;  
}

template <typename T>
void List<T>::erase() {
    while (!is_empty()) {
        pop_front();
    }

    _head = nullptr;
    _tail = nullptr;
    _count = 0;
}

template <typename T>
bool List<T>::is_empty() const {
    return _head == nullptr;
}

template <typename T>
Node<T>* List<T>::find(const T& val) {
    Node<T>* cur = _head;
    int cur_pos = 0;
    while (cur != nullptr) {
        if (cur->value == val) {
            return cur;
        }
        ++cur_pos;
    }
    return nullptr;
}

//CLASS ITERATOR
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator=(const Iterator& other) {
    this->_current = other._current;
    return *this;
}

template <typename T>
T& List<T>::Iterator::operator*() {
    return _current->_value;
}

template <typename T>
bool List<T>::Iterator::operator==(const Iterator& other) const {
    return _current == other._current;
}

template <typename T>
bool List<T>::Iterator::operator!=(const Iterator& other) const {
    return _current != other._current;
}

template <typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    if(_current != nullptr) {
        _current = _current->_next;
    }
    return *this;
}

//CLASS CONST ITERATOR

template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator=(const ConstIterator& other) {
    this->_current = other._current;
    return *this;
}
template <typename T>
const T& List<T>::ConstIterator::operator*() const {
    return _current->_value;
}

template <typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return _current == other._current;
}

template <typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return _current != other._current;
}

template <typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int) {
    ConstIterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++() {
    if(_current != nullptr) {
        _current = _current->_next;
    }
    return *this;
}