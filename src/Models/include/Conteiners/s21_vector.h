#ifndef SRC_INCLUDES_CONTAINERS_S21_VECTOR_H
#define SRC_INCLUDES_CONTAINERS_S21_VECTOR_H

#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>

#include "../Iterators/s21_const_sequential_iterator.h"
#include "../Iterators/s21_sequential_iterator.h"
#include "s21_base_container.h"

namespace s21 {
template <typename T>
class Vector : public BaseContainer<T> {
 public:
  //синонимы
  using value_type = T;
  using const_reference = const T &;
  using reference = T &;
  using size_type = size_t;
  using s21_iterator = SequentialIterator<value_type>;
  using s21_const_iterator = ConstSequentialIterator<value_type>;

  //конструкторы
  Vector();
  explicit Vector(size_type n);
  Vector(const Vector &another);
  Vector(Vector &&another);
  Vector(std::initializer_list<value_type> list);

  //деструктор
  ~Vector();

  // методы
  inline size_type Size() noexcept override;
  inline size_type MaxSize() const noexcept;
  inline size_type Capacity() const noexcept;
  inline bool Empty() noexcept override;
  inline void Clear();
  void Reserve(size_type new_capacity);
  void ShrinkToFit();
  reference At(size_type pos);
  reference At(size_type pos) const;
  const_reference Front();
  const_reference Back();
  void PushBack(const_reference value);
  void PushFront(const_reference value);
  inline void PopBack();
  void PopFront();
  inline s21_iterator Begin();
  inline s21_iterator End();
  inline s21_const_iterator CBegin();
  inline s21_const_iterator CEnd();
  inline s21_iterator Data();
  s21_iterator Insert(s21_iterator pos, const_reference value);
  void Erase(s21_iterator pos);
  void Swap(Vector<value_type> &other);
  template <typename... Args>
  void EmplaceBack(Args &&...args);
  template <typename... Args>
  s21_iterator Emplace(s21_iterator pos, Args &&...args);

  // перегрузка
  reference operator()(size_type i);
  reference operator[](size_type i);
  Vector<value_type> &operator=(Vector<value_type> &&v);
  Vector<value_type> &operator=(const Vector<value_type> &v);

 private:
  size_type lenght_{};
  size_type capacity_{};
  value_type *data_{};
  void Push(const T &new_element) override;
  void Pop() override;
};
}  // namespace s21

template <typename T>
s21::Vector<T>::Vector()
    : lenght_{0}, capacity_{7}, data_{new T[capacity_]{}} {}

template <typename T>
s21::Vector<T>::Vector(size_t n)
    : lenght_{0}, capacity_{n + 7}, data_{new T[capacity_]{}} {}

template <typename T>
s21::Vector<T>::Vector(const Vector &another) {
  if (this != &another) {
    lenght_ = another.lenght_;
    capacity_ = another.capacity_;
    data_ = new T[capacity_];
    std::copy(another.data_, another.data_ + lenght_, data_);
  }
}

template <typename T>
s21::Vector<T>::Vector(Vector &&another)
    : lenght_{0}, capacity_{0}, data_{nullptr} {
  Swap(another);
}

template <typename T>
s21::Vector<T>::Vector(std::initializer_list<T> list)
    : lenght_{list.size()},
      capacity_{list.size() + 7},
      data_{new T[capacity_]{}} {
  std::copy(list.begin(), list.end(), data_);
}

template <typename T>
s21::Vector<T>::~Vector() {
  if (data_ != nullptr) delete[] data_;
  lenght_ = 0;
  capacity_ = 0;
}

template <typename T>
inline size_t s21::Vector<T>::Size() noexcept {
  return lenght_;
}

template <typename T>
size_t s21::Vector<T>::Capacity() const noexcept {
  return capacity_;
}

template <typename T>
bool s21::Vector<T>::Empty() noexcept {
  return lenght_ == 0;
}

template <typename T>
void s21::Vector<T>::Clear() {
  lenght_ = 0;
  capacity_ = 5;
  delete[] data_;
  data_ = new T[capacity_];
  memset(data_, '\0', sizeof(T) * capacity_);
}

template <typename T>
void s21::Vector<T>::Push(const T &new_element) {
  if (lenght_ >= capacity_) Reserve(capacity_ += 7);
  data_[lenght_++] = new_element;
}

template <typename T>
void s21::Vector<T>::PushBack(const T &value) {
  Push(value);
}

template <typename T>
void s21::Vector<T>::PushFront(const T &value) {
  if (lenght_ >= capacity_) Reserve(capacity_ += 7);
  T *tmp{data_};
  data_ = new T[capacity_]();
  data_[0] = value;
  lenght_++;
  std::copy(tmp, tmp + lenght_ - 1, data_ + 1);
  delete[] tmp;
}

template <typename T>
void s21::Vector<T>::Pop() {
  if (lenght_ > 0) lenght_--;
}

template <typename T>
void s21::Vector<T>::PopBack() {
  Pop();
}

template <typename T>
void s21::Vector<T>::PopFront() {
  T *tmp{data_};
  data_ = new T[capacity_]();
  std::copy(tmp + 1, tmp + lenght_, data_);
  lenght_--;
  delete[] tmp;
}

template <typename T>
T &s21::Vector<T>::operator()(size_t i) {
  return data_[i];
}

template <typename T>
T &s21::Vector<T>::operator[](size_t i) {
  return data_[i];
}

template <typename T>
s21::Vector<T> &s21::Vector<T>::operator=(Vector<T> &&v) {
  if (this == &v) {
    return *this;
  }
  if (data_ != nullptr) delete[] data_;
  lenght_ = 0;
  capacity_ = 0;
  data_ = nullptr;
  Swap(v);
  return *this;
}

template <typename T>
s21::Vector<T> &s21::Vector<T>::operator=(const Vector<T> &v) {
  if (this == &v) {
    return *this;
  }
  if (data_) delete[] data_;
  lenght_ = v.lenght_;
  capacity_ = v.capacity_;
  data_ = new T[capacity_];
  std::copy(v.data_, v.data_ + v.lenght_, data_);
  return *this;
}

template <typename T>
T &s21::Vector<T>::At(size_t pos) {
  if (pos >= lenght_) throw std::out_of_range("OUT OF RANGE ERROR");
  return data_[pos];
}

template <typename T>
T &s21::Vector<T>::At(size_t pos) const {
  if (pos >= lenght_) throw std::out_of_range("OUT OF RANGE ERROR");
  return data_[pos];
}

template <typename T>
const T &s21::Vector<T>::Front() {
  return data_[0];
}

template <typename T>
const T &s21::Vector<T>::Back() {
  if (lenght_ == 0) return data_[lenght_];
  return data_[lenght_ - 1];
}

template <typename T>
SequentialIterator<T> s21::Vector<T>::Data() {
  s21_iterator _data(data_);
  return _data;
}

template <typename T>
SequentialIterator<T> s21::Vector<T>::Begin() {
  s21_iterator _begin(data_);
  return _begin;
}

template <typename T>
SequentialIterator<T> s21::Vector<T>::End() {
  s21_iterator _end(data_ + lenght_);
  return _end;
}

template <typename T>
ConstSequentialIterator<T> s21::Vector<T>::CBegin() {
  s21_const_iterator _begin(data_);
  return _begin;
}

template <typename T>
ConstSequentialIterator<T> s21::Vector<T>::CEnd() {
  s21_const_iterator _end(data_ + lenght_);
  return _end;
}

template <typename T>
SequentialIterator<T> s21::Vector<T>::Insert(s21_iterator pos, const T &value) {
  size_t index{0};
  for (auto it = Begin(); it != End(); ++it, index++) {
    if (pos == it) {
      break;
    }
  }
  if (index < lenght_) {
    Reserve(++capacity_);
    ++lenght_;
    T *tmp{new T[lenght_]};
    std::copy(data_ + index, data_ + lenght_, tmp);
    data_[index] = value;
    std::copy(tmp, tmp + lenght_ - 1, data_ + index + 1);
    delete[] tmp;
  } else {
    PushBack(value);
  }
  s21_iterator new_pos(data_ + index);
  return new_pos;
}

template <typename T>
void s21::Vector<T>::Erase(s21_iterator pos) {
  size_t index{0};
  for (auto it = Begin(); it != End(); ++it, index++) {
    if (pos == it) {
      break;
    }
  }
  if (index < lenght_) {
    T *tmp{std::find(data_, data_ + lenght_, *pos)};
    std::copy(tmp + 1, tmp + lenght_ - index, data_ + index);
    lenght_--;
  }
}

template <typename T>
void s21::Vector<T>::Reserve(size_t new_capacity) {
  if (new_capacity >= lenght_) {
    capacity_ = new_capacity;
    T *tmp{data_};
    data_ = new T[capacity_]();
    std::copy(tmp, tmp + lenght_, data_);
    delete[] tmp;
  }
}

template <typename T>
size_t s21::Vector<T>::MaxSize() const noexcept {
  char bits = 63;
  if (sizeof(void *) == 4) {
    bits = 31;
  }
  return static_cast<size_type>(pow(2, bits)) / sizeof(value_type) - 1;
}

template <typename T>
void s21::Vector<T>::ShrinkToFit() {
  Reserve(lenght_);
}

template <typename T>
void s21::Vector<T>::Swap(Vector<T> &other) {
  if (this != &other) {
    std::swap(capacity_, other.capacity_);
    std::swap(lenght_, other.lenght_);
    std::swap(data_, other.data_);
  }
}

template <typename T>
template <typename... Args>
void s21::Vector<T>::EmplaceBack(Args &&...args) {
  std::initializer_list<T> list = {args...};
  for (auto it = list.begin(); it != list.end(); ++it) PushBack(*it);
}

template <typename T>
template <typename... Args>
SequentialIterator<T> s21::Vector<T>::Emplace(s21_iterator pos,
                                              Args &&...args) {
  std::initializer_list<T> list = {args...};
  for (auto it = list.begin(); it != list.end(); ++it) {
    pos = Insert(pos, *it);
    ++pos;
  }
  return pos;
}

#endif  //  SRC_INCLUDES_CONTAINERS_S21_VECTOR_H