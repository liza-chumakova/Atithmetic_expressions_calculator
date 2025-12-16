#pragma once
#include <iostream>

#define STEP_CAPACITY 15

template <class T> class TVector;

template <class T>
class TVector {
protected:
    T* _data;
    int _capacity;
    int _size;

public:
    TVector();
    TVector(const TVector& other);
    TVector(const T* arr, int n);
    TVector(int size);
    TVector(std::initializer_list<T> data);
    
    ~TVector();

    inline T&front();
    inline T&back();
    inline T&front() const;
    inline T&back() const;

    inline T*data() const noexcept;
    inline int size() const noexcept;
    inline int capacity() const noexcept;

    //int size() const noexcept;

    TVector& operator=(const TVector& other) noexcept;

    bool operator==(const TVector& other) const;

    inline T& operator[](int pos);
    inline const T& operator[](int pos) const;

    //Functional
    void erase(int pos, int count = 1);
    void pop_front();
    void pop_back();
    void push_front(T value);
    void push_back(T value);
    void insert(int pos, T value);

    void reset_memory(int new_size);

    class Iterator {
    private:
        T* _current;
    public:
        Iterator();
        Iterator(T* pos);
        Iterator(const Iterator& other);

        Iterator& operator=(const Iterator& other);
        T& operator*() const;

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

        Iterator& operator++();
        Iterator operator++(int);

        Iterator& operator--();
        Iterator operator--(int);
    };

    Iterator begin() noexcept { return Iterator(_data); }
    Iterator end() noexcept { return Iterator(_data + _size); }
};

template <typename T>
TVector<T>::TVector(): _data(nullptr), _size(0), _capacity(0)
{
}

template <typename T>
TVector<T>::TVector(const TVector& other)
{
    _size = other._size;
    _capacity = (_size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;
    _data = new T[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = other._data[i];
    }
}

template <typename T>
TVector<T>::TVector(const T* arr, int n){
    _size = n;
    _capacity = (_size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;
    _data = new T[n];
    for (int i = 0; i < n; ++i){
        _data[i] = arr[i];
    }
}

template <typename T>
TVector<T>::TVector(int size){
    _capacity = (size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;
    _size = size;
    _data = new T[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = T();
    }
}

template <typename T>
TVector<T>::TVector(std::initializer_list<T> data)
{
    _size = data.size();
    _capacity = (_size + STEP_CAPACITY) / STEP_CAPACITY * STEP_CAPACITY;
    _data = new T[_capacity];
    for (int i = 0; i < _size; ++i)
    {
        _data[i] = *(data.begin() + i);
    } 
}

template <typename T>
TVector<T>::~TVector()
{
    if(_data!= nullptr)
    {
        delete[] _data;
    }
}

template <typename T>
inline T*TVector<T>::data() const noexcept
{
    return _data;
}

template <typename T>
inline int TVector<T>::size() const noexcept
{
    return _size;
}

template <typename T>
inline int TVector<T>::capacity() const noexcept
{
    return _capacity;
}

template <typename T>
inline T& TVector<T>::operator[](int pos)
{
    if (pos < 0 || pos >= _size) {
        throw std::out_of_range("index out of range");
    }
    return _data[pos];
}

template <typename T>
inline const T& TVector<T>::operator[](int pos) const
{
    if (pos < 0 || pos >= _size) {
        throw std::out_of_range("index out of range");
    }
    return _data[pos];
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector& other) noexcept
{
    if (this != &other){
        delete[] _data;
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        for (int i = 0; i < _size; ++i){
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template <typename T>
inline T& TVector<T>::front()
{
    if(_size < 1) throw std::logic_error("Vector is empty");
    return _data[0];
}
template <typename T>
inline T&TVector<T>::back()
{
    if(_size < 1) throw std::logic_error("Vector is empty");
    return _data[_size - 1];
}
template <typename T>
inline T&TVector<T>::front() const
{
    if(_size < 1) throw std::logic_error("Vector is empty");
    return _data[0];
}
template <typename T>
inline T&TVector<T>::back() const
{
    if(_size < 1) throw std::logic_error("Vector is empty");
    return _data[_size - 1];
}

template <typename T>
bool TVector<T>::operator==(const TVector& other) const
{
    //std::cout<< "Testttt" << std::endl;
    if (_size != other._size) return false;
    for (int i = 0; i < _size; ++i) 
    {
        //std::cout << "operator: " << i << " , " << _data[i] << " " << other._data[i] << std::endl;
        if (_data[i] != other._data[i]) return false;
    }
    return true;
}

template <typename T>
void TVector<T>::erase(int pos, int count)
{
    for (int i = pos; i < _size - count; ++i)
    {
        _data[i] = _data[i + count];
    }

    _size -= count;
    reset_memory(_size);
}

template <typename T>
void TVector<T>::pop_front()
{
    for (int i = 0; i < _size - 1; ++i)
    {
        _data[i] = _data[i + 1];
    }

    _size -= 1;
    reset_memory(_size);
}
template <typename T>
void TVector<T>::pop_back()
{
    _size -= 1;
    reset_memory(_size);
}

template <typename T>
void TVector<T>::push_front(T value)
{
    _size += 1;
    reset_memory(_size);

    for (int i = _size - 1; i > 0; i--)
    {
        _data[i] = _data[i - 1];
    }
    _data[0] = value;

}
template <typename T>
void TVector<T>::push_back(T value)
{
    _size += 1;
    reset_memory(_size);

    _data[_size - 1] = value;

}
template <typename T>
void TVector<T>::insert(int pos, T value)
{
    if (pos < 1)
    {
        return;
    }
    _size += 1;
    reset_memory(_size);

    for (int i = _size - 1; i >= pos; i--)
    {
        _data[i] = _data[i - 1];
    }
    _data[pos - 1] = value;
}

template <typename T>
void TVector<T>::reset_memory(int new_size)
{
    int new_capacity = (new_size + STEP_CAPACITY - 1) / STEP_CAPACITY * STEP_CAPACITY;

    if (new_capacity > _capacity || new_capacity < _capacity - STEP_CAPACITY)
    {
        T* new_data = new T[new_capacity];

        int elements_to_copy = (new_size < _size) ? new_size : _size;
        for (int i = 0; i < elements_to_copy; ++i)
        {
            new_data[i] = _data[i];
        }

        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    _size = new_size;
}

template <typename T>
TVector<T>::Iterator::Iterator() : _current(nullptr) {}

template <typename T>
TVector<T>::Iterator::Iterator(T* pos) : _current(pos) {}

template <typename T>
TVector<T>::Iterator::Iterator(const Iterator& other) : _current(other._current) {}

template <typename T>
typename TVector<T>::Iterator& TVector<T>::Iterator::operator=(const Iterator& other) {
    _current = other._current;
    return *this;
}

template <typename T>
T& TVector<T>::Iterator::operator*() const {
    return *_current;
}

template <typename T>
bool TVector<T>::Iterator::operator==(const Iterator& other) const {
    return _current == other._current;
}

template <typename T>
bool TVector<T>::Iterator::operator!=(const Iterator& other) const {
    return _current != other._current;
}

template <typename T>
typename TVector<T>::Iterator TVector<T>::Iterator::operator++(int) {
    Iterator temp = *this;
    ++_current;
    return temp;
}

template <typename T>
typename TVector<T>::Iterator& TVector<T>::Iterator::operator++() {
    ++_current;
    return *this;
}

template <typename T>
typename TVector<T>::Iterator TVector<T>::Iterator::operator--(int) {
    Iterator temp = *this;
    --_current;
    return temp;
}

template <typename T>
typename TVector<T>::Iterator& TVector<T>::Iterator::operator--() {
    --_current;
    return *this;
}
