#pragma once
#include <iostream>

template <class T> class Stack;

template <class T>
class Stack {
protected:
    T* _data;
    int _size;
    int _top; //Штука которая показывает на верхний элемент стека

public:
    //Stack();
    Stack(const Stack& other);
    Stack(const T* arr, int n);
    Stack(int size);
    Stack(std::initializer_list<T> data);
    
    ~Stack();

    inline T*data() const noexcept;
    inline int size() const noexcept;
    inline int get_top() const noexcept;
    inline T top() const;

    //int size() const noexcept;

    Stack& operator=(const Stack& other) noexcept;
    //inline T& operator[](int pos) noexcept;

    //bool operator==(const Stack& other) const;
    //bool operator!=(const Stack& other) const;


    //Functional
    void pop();
    void push(const T& value);

    inline bool is_empty() noexcept;
    inline bool is_full() noexcept;

    void clear() noexcept;
    //friend std::ostream& operator <<<T>(std::ostream& out, const Stack<T>& dmass);
};

template <typename T>
Stack<T>::Stack(const Stack& other)
{
    _size = other._size;
    _data = new T[_size];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = other._data[i];
    }
    _top = other.get_top();
}

template <typename T>
Stack<T>::Stack(const T* arr, int n) : _size(n), _top(n - 1), _data(new T[n]) {
    for (int i = 0; i < n; ++i){
        _data[i] = arr[i];
    }
}

template <typename T>
Stack<T>::Stack(int size) {
    _size = size;
    _data = new T[_size];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = T();
    }
    _top = - 1;
}

template <typename T>
Stack<T>::Stack(std::initializer_list<T> data)
{
    _size = data.size();
    _data = new T[_size];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = *(data.begin() + i);
    }
    _top = _size - 1;
}

template <typename T>
Stack<T>::~Stack()
{
        delete[] _data;
}

template <typename T>
inline T*Stack<T>::data() const noexcept
{
    return _data;
}

template <typename T>
inline int Stack<T>::size() const noexcept
{
    return _size;
}

template <typename T>
inline int Stack<T>::get_top() const noexcept
{
    return _top;
}

template <typename T>
inline T Stack<T>::top() const
{
    return _data[_top];
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other) noexcept
{
    if (this != other){
        delete[] _data;
        _size = other._size;
        _data = new T[_size];
        for (int i = 0; i < _size; ++i){
            _data[i] = other._data[i];
        }
        _top = other._top;
    }
    return *this;
}

// template <typename T>
// bool Stack<T>::operator==(const Stack& other) const
// {
//     for (int i = 0; i < _top; ++i) 
//     {
//         if (_data[i] != other._data[i]) return false;
//     }
//     for (int i = _top; i < other.get_top(); ++i) 
//     {
//         if (_data[i] != other._data[i]) return false;
//     }
//     return true;
// }

// template<typename T>
// bool Stack<T>::operator!=(const Stack& other) const {
//     return !(*this == other);
// }

template <typename T>
void Stack<T>::pop()
{
    if (is_empty())
    {
        throw std::logic_error("Stack is empty");
    }

    --_top;
}

template <typename T>
void Stack<T>::push(const T& value)
{
    if (is_full())
    {
        throw std::logic_error("Stack is full");
    }

    _data[_top + 1] = value;
    ++_top;
}

template <typename T>
inline bool Stack<T>::is_empty() noexcept
{
    return _top == -1;
}

template <typename T>
inline bool Stack<T>::is_full() noexcept
{
    return _top == _size - 1;
}

template <typename T>
void Stack<T>::clear() noexcept
{
    _top = -1;
}
