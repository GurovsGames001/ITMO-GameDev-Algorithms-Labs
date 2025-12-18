#pragma once

#include <cstdlib>
#include <utility>
#include <type_traits>
#include <cassert>
#include <new>

template<typename T>
class Array final 
{
public:
    // --- Итератор для обхода в прямом порядке ---
    class Iterator
    {
    public:
        Iterator(Array* array, int position) : owner_(array), pos_(position) {}

        T& operator*() const { return (*owner_)[pos_]; }
        Iterator& operator++() 
        { 
            next(); 
            return *this; 
        }
        Iterator operator++(int) 
        { 
            Iterator tmp = *this; 
            next();
            return tmp; 
        }

        const T& get() const { return (*owner_)[pos_]; }
        void set(const T& value) { (*owner_)[pos_] = value; }
        void next() { pos_++; }
        bool hasNext() const { return pos_ < owner_->size(); }

    private:
        Array<T>* owner_;
        int pos_;
    };

    // --- Константный итератор для обхода в прямом порядке ---
    class ConstIterator
    {
    public:
        ConstIterator(const Array* array, int position) : owner_(array), pos_(position) {}

        const T& operator*() const { return (*owner_)[pos_]; }
        ConstIterator& operator++() 
        { 
            next(); 
            return *this; 
        }
        ConstIterator operator++(int) 
        { 
            ConstIterator tmp = *this; 
            next(); 
            return tmp; 
        }

        const T& get() const { return (*owner_)[pos_]; }
        void next() { pos_++; }
        bool hasNext() const { return pos_ < owner_->size(); }

    private:
        const Array* owner_;
        int pos_;
    };

    // --- Итератор для обхода в обратном порядке ---
    class ReverseIterator
    {
    public:
        ReverseIterator(Array* array, int position) : owner_(array), pos_(position) {}

        T& operator*() { return (*owner_)[pos_]; }
        ReverseIterator& operator--()
        {
            next();
            return *this;
        }
        ReverseIterator operator--(int)
        {
            ReverseIterator tmp = *this;
            next();
            return tmp;
        }

        const T& get() const { return (*owner_)[pos_]; }
        void set(const T& value) { (*owner_)[pos_] = value; }
        void next() { pos_--; }
        bool hasNext() const { return pos_ >= 0; }

    private:
        Array* owner_;
        int pos_;
    };

    // --- Константный итератор для обхода в обратном порядке ---
    class ConstReverseIterator 
    {
    public:
        ConstReverseIterator(const Array* array, int position) : owner_(array), pos_(position) {}

        const T& operator*() const { return (*owner_)[pos_]; }
        ConstReverseIterator& operator--() 
        { 
            next();
            return *this; 
        }
        ConstReverseIterator operator--(int) 
        { 
            ConstReverseIterator tmp = *this; 
            next();
            return tmp; 
        }

        const T& get() const { return (*owner_)[pos_]; }
        void next() { pos_--; }
        bool hasNext() const { return pos_ >= 0; }

    private:
        const Array* owner_;
        int pos_;
    };


    // --- Конструкторы/Деструктор ---
    Array();
    explicit Array(const int capacity);
    Array(const Array& other);
    Array(Array&& other) noexcept;

    ~Array() { clearAndFree(); }

    // --- Перегруженные операторы ---
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;

    const T& operator[](const int index) const;
    T& operator[](const int index);

    // --- Добавление элементов ---
    int insert(const T& value) { return insert(size_, value); };
    int insert(const int index, const T& value);

    // --- Удаление элементов ---
    void remove(const int index);

    int size() const { return size_; }
    int getCapacity() const { return capacity_; }
    bool isEmpty() const { return size_ == 0; }

    // --- Получение итераторов ---
    Iterator iterator() { return Iterator(this, 0); }
    ConstIterator iterator() const { return ConstIterator(this, 0); }

    ReverseIterator reverseIterator() { return ReverseIterator(this, size_ - 1); }
    ConstReverseIterator reverseIterator() const { return ConstReverseIterator(this, size_ - 1); }

    // --- Методы для цикла range-for ---
    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* cbegin() const { return data_; }
    const T* cend() const { return data_ + size_; }

private:
    static constexpr int DEFAULT_CAPACITY = 16;
    static constexpr int GROWTH_FACTOR = 2;

    T* data_ = nullptr;
    int size_ = 0;
    int capacity_ = 0;

    void reallocate();
    void clearAndFree();

    void construct_at(const int index, const T& value) { ::new (static_cast<void*>(data_ + index)) T(value); }
    void construct_at(const int index, T&& value) { ::new (static_cast<void*>(data_ + index)) T(std::move(value)); }
    void construct_at(T* otherData, const int index, const T& value) { ::new (static_cast<void*>(otherData + index)) T(value); }
    void construct_at(T* otherData, const int index, T&& value) { ::new (static_cast<void*>(otherData + index)) T(std::move(value)); }
    void destroy_at(const int index) { data_[index].~T(); }

    void swap(Array& other) noexcept;
    void moveElementToNewPosition(const int targetIndex, const int sourceIndex);
    void moveElementToOtherData(T* targetData, const int index);
};

// ==================== Конструкторы ====================

template<typename T>
Array<T>::Array() : capacity_(DEFAULT_CAPACITY), size_(0)
{
    data_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
}

template<typename T>
Array<T>::Array(const int capacity) : size_(0)
{
    capacity_ = (capacity > 0) ? capacity : DEFAULT_CAPACITY;
    data_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
}

template<typename T>
Array<T>::Array(const Array& other) : size_(other.size_), capacity_(other.capacity_)
{
    data_ = static_cast<T*>(malloc(sizeof(T) * capacity_));
    for (int i = 0; i < size_; i++)
    {
        construct_at(i, other.data_[i]);
    }
}

template<typename T>
Array<T>::Array(Array&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

// ==================== Перегруженные операторы ====================

template<typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
    Array temp(other);
    this->swap(temp);
    return *this;
}

template<typename T>
Array<T>& Array<T>::operator=(Array&& other) noexcept
{
    this->swap(other);
    return *this;
}

template<typename T>
const T& Array<T>::operator[](const int index) const
{
    assert(index >= 0 && index < size_);
    return data_[index];
}

template<typename T>
T& Array<T>::operator[](const int index)
{
    assert(index >= 0 && index < size_);
    return data_[index];
}

// ==================== Публичные методы ====================

template<typename T>
int Array<T>::insert(const int index, const T& value)
{
    assert(index >= 0 && index <= size_);

    if (size_ == capacity_) 
    {
        reallocate();
    }

    for (int i = size_; i > index; i--) 
    {
        moveElementToNewPosition(i, i - 1);
    }

    construct_at(index, value);
    size_++;
    return index;
}

template<typename T>
void Array<T>::remove(const int index)
{
    assert(index >= 0 && index < size_);

    destroy_at(index);

    for (int i = index; i < size_ - 1; i++) 
    {
        moveElementToNewPosition(i, i + 1);
    }
    size_--;
}

// ==================== Приватные методы ====================

template<typename T>
void Array<T>::reallocate()
{
    int newCapacity = (capacity_ == 0) ? DEFAULT_CAPACITY : capacity_ * GROWTH_FACTOR;

    void* p = malloc(sizeof(T) * newCapacity);
    if (!p) 
    {
        throw std::bad_alloc();
    }
    T* newData = static_cast<T*>(p);

    for (int i = 0; i < size_; i++)
    {
        moveElementToOtherData(newData, i);
    }

    free(data_);
    data_ = newData;
    capacity_ = newCapacity;
}

template<typename T>
void Array<T>::clearAndFree()
{
    for (int i = 0; i < size_; i++)
    {
        destroy_at(i);
    }
    free(data_);
}

template<typename T>
void Array<T>::swap(Array& other) noexcept
{
    std::swap(this->data_, other.data_);
    std::swap(this->size_, other.size_);
    std::swap(this->capacity_, other.capacity_);
}

template<typename T>
void Array<T>::moveElementToNewPosition(const int targetIndex, const int sourceIndex) 
{
    if constexpr (std::is_move_constructible_v<T>)
    {
        construct_at(targetIndex, std::move(data_[sourceIndex]));
    }
    else
    {
        construct_at(targetIndex, data_[sourceIndex]);
    }
    destroy_at(sourceIndex);
}

template<typename T>
void Array<T>::moveElementToOtherData(T* targetData, const int index)
{
    if constexpr (std::is_move_constructible_v<T>)
    {
        construct_at(targetData, index, std::move(data_[index]));
    }
    else
    {
        construct_at(targetData, index, data_[index]);
    }
    destroy_at(index);
}
