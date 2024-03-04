//
// Created by Alesander Britni on 3/3/23.
//
#ifndef SRC_INCLUDES_S21_LIST_H
#define SRC_INCLUDES_S21_LIST_H

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class List {
 private:
  class Element;

 public:
  class ListIterator;
  class ListConstIterator;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  using iterator = s21::List<value_type>::ListIterator;
  using const_iterator = s21::List<value_type>::ListConstIterator;

  List();
  List(std::initializer_list<T> const &list);
  explicit List(size_t n);
  List(List<T> &other);
  List(List<T> &&other) noexcept;
  ~List();

  List &operator=(const List<T> &other);
  List &operator=(List<T> &&other);

  void Reverse() noexcept;
  void PushFront(const_reference data);
  void PushBack(const_reference data);
  void PopFront();
  void PopBack();
  void Clear() noexcept;
  bool Empty() const noexcept;
  size_t MaxSize() const noexcept;
  size_t Size() const noexcept;
  const_reference Back() const noexcept;
  reference Back() noexcept;
  reference Front() noexcept;
  const_reference Front() const noexcept;
  void Swap(List<T> &other) noexcept;
  void Merge(List<T> &other);
  void Sort();

  iterator Begin();
  const_iterator Cbegin() const;
  iterator End();
  const_iterator Cend() const;
  iterator Insert(iterator pos, const_reference data);
  void Erase(iterator pos);
  void Splice(iterator pos, List<T> &other);

  template <typename... Args>
  iterator Emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void EmplaceBack(Args &&...args);
  template <typename... Args>
  void EmplaceFront(Args &&...args);
  void Unique();

  class ListIterator {
   public:
    using Element = List<T>::Element;
    using value_type = List<T>::value_type;
    using reference = value_type &;
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;

    ListIterator() = delete;

    explicit ListIterator(Element *pElement) noexcept { current_ = pElement; };
    inline void operator=(Element *new_ptr) { current_ = new_ptr; }

    inline reference operator*() const noexcept {
      if (!current_) {
        static value_type default_value_{};
        return default_value_;
      }
      return current_->value_;
    }

    inline bool operator!=(const iterator &other) const noexcept {
      return current_ != other.current_;
    }

    inline bool operator==(const iterator &other) const noexcept {
      return current_ == other.current_;
    }

    inline iterator &operator++() noexcept {
      current_ = this->current_->pNext_;
      return *this;
    }

    inline iterator operator++(int) noexcept {
      iterator temp(*this);
      current_ = current_->pNext_;
      return temp;
    }

    inline iterator &operator--() noexcept {
      current_ = this->current_->pPrev_;
      return *this;
    }

    inline iterator operator--(int) noexcept {
      iterator temp(*this);
      current_ = current_->pPrev_;
      return temp;
    }

   private:
    friend class List<value_type>;
    Element *current_{};
  };
  class ListConstIterator {
   public:
    using Element = List<T>::Element;
    using value_type = List<T>::value_type;
    using reference = const value_type &;
    using iterator = ListIterator;
    using const_iterator = ListConstIterator;

    ListConstIterator() = delete;

    explicit ListConstIterator(const Element *pElement) {
      current_ = pElement;
    };

    ListConstIterator(const iterator &other) { current_ = other.current_; }

    inline reference operator*() const noexcept {
      if (!current_) {
        static value_type default_value_{};
        return default_value_;
      }
      return current_->value_;
    }

    inline const_iterator &operator++() noexcept {
      current_ = this->current_->pNext_;
      return *this;
    }

    inline const_iterator operator++(
        int) noexcept {  // возрващает не константный объект const
      const_iterator temp(*this);
      current_ = current_->pNext_;
      return temp;
    }

    inline const_iterator &operator--() noexcept {
      current_ = this->current_->pPrev_;
      return *this;
    }

    inline const_iterator operator--(int) noexcept {
      const_iterator temp(*this);
      current_ = current_->pPrev_;
      return temp;
    }

    friend bool operator==(const const_iterator &x,
                           const const_iterator &y) noexcept {
      return x.current_ == y.current_;
    }

    friend bool operator!=(const const_iterator &x,
                           const const_iterator &y) noexcept {
      return x.current_ != y.current_;
    }

   private:
    friend class List<value_type>;
    const Element *current_{};
  };

 private:
  class Element {
    friend class List;

   public:
    Element(T value_ = T(), Element *pNext_ = nullptr,
            Element *pPrev_ = nullptr) {
      this->value_ = value_;
      this->pNext_ = pNext_;
      this->pPrev_ = pPrev_;
    }
    T value_{};
    Element *pNext_{};
    Element *pPrev_{};
  };

  Element *root_{};
  Element *begin_{};
  Element *end_{};
  size_t count_elements_{};

  void ReinitializationList(List<T> &other);
  void RootMod();
  void ListDefault();
  void SwapFields(List<T> &other);
  void CopyElements(const List<T> &other);
  void MergeSort(Element **n);
  void SplitElement(Element *n, Element **elem_1, Element **elem_2);
  Element *MergeElements(Element *elem_1, Element *elem_2);
};

template <typename value_type>
s21::List<value_type>::List() {
  root_ = new Element(value_type{});
  root_->pNext_ = root_;
  root_->pPrev_ = root_;
}

template <typename value_type>
s21::List<value_type>::List(std::initializer_list<value_type> const &list)
    : List() {
  for (auto var : list) PushBack(var);
}

template <typename value_type>
s21::List<value_type>::List(size_t n) : List() {
  for (size_t i = 0; i < n; i++) PushBack(value_type{});
}

template <typename value_type>
s21::List<value_type>::List(List<value_type> &other) : List() {
  if (this != &other) CopyElements(other);
}

template <typename value_type>
s21::List<value_type>::List(List<value_type> &&other) noexcept {
  if (this != &other) {
    count_elements_ = 0;
    begin_ = end_ = nullptr;
    SwapFields(other);
    ReinitializationList(other);
  }
}

template <typename value_type>
s21::List<value_type>::~List() {
  Clear();
  delete root_;
}

template <typename value_type>
s21::List<value_type> &s21::List<value_type>::operator=(
    const List<value_type> &other) {
  if (this != &other) {
    this->Clear();
    begin_ = end_ = nullptr;
    count_elements_ = 0;
    CopyElements(other);
  }
  return (*this);
}

template <typename value_type>
s21::List<value_type> &s21::List<value_type>::operator=(
    List<value_type> &&other) {
  if (this != &other) {
    this->Clear();
    SwapFields(other);
  }
  return *this;
}

template <typename value_type>
void s21::List<value_type>::Reverse() noexcept {
  if (count_elements_ >= 2) {
    iterator it = Begin();
    for (; it != End(); --it) {
      std::swap(it.current_->pNext_, it.current_->pPrev_);
    }
    std::swap(begin_, end_);
    RootMod();
  }
}

template <typename value_type>
void s21::List<value_type>::PushFront(const_reference data) {
  this->Insert(Begin(), data);
}

template <typename value_type>
void s21::List<value_type>::PushBack(const_reference data) {
  this->Insert(End(), data);
}

template <typename value_type>
void s21::List<value_type>::PopFront() {
  Erase(Begin());
}

template <typename value_type>
void s21::List<value_type>::PopBack() {
  Erase(--End());
}

template <typename value_type>
void s21::List<value_type>::Clear() noexcept {
  while (count_elements_) PopFront();
}

template <typename value_type>
bool s21::List<value_type>::Empty() const noexcept {
  return !count_elements_;
}

template <typename value_type>
size_t s21::List<value_type>::MaxSize() const noexcept {
  return ((std::numeric_limits<size_type>::max() / 2) / sizeof(Element));
}

template <typename value_type>
size_t s21::List<value_type>::Size() const noexcept {
  return count_elements_;
}

template <typename value_type>
const value_type &s21::List<value_type>::Back() const noexcept {
  return *(--End());
}

template <typename value_type>
value_type &s21::List<value_type>::Back() noexcept {
  return *(--End());
}

template <typename value_type>
value_type &s21::List<value_type>::Front() noexcept {
  return *Begin();
}

template <typename value_type>
const value_type &s21::List<value_type>::Front() const noexcept {
  return *Begin();
}

template <typename value_type>
void s21::List<value_type>::Swap(List<value_type> &other) noexcept {
  if (this != &other) {
    std::swap(*this, other);
  }
}

template <typename value_type>
void s21::List<value_type>::Merge(List<value_type> &other) {
  if (this != &other && !other.Empty()) {
    iterator it_this = Begin();
    iterator it_other = other.Begin();
    for (; it_this != End() && !other.Empty();) {
      if (*it_this <= *it_other) {
        ++it_this;
      } else {
        iterator tmp = it_other;
        ++it_other;
        Insert(it_this, *tmp);
        other.Erase(other.Begin());
      }
    }
    if (!other.Empty()) {
      it_other = other.Begin();
      for (; it_other != other.End();) {
        iterator tmp = it_other;
        ++it_other;
        this->PushBack(*tmp);
        other.Erase(tmp);
      }
    }
    other.ListDefault();
  }
}

template <typename value_type>
void s21::List<value_type>::Sort() {
  if (this->Empty() || count_elements_ == 1) {
    return;
  } else {
    end_->pNext_ = nullptr;
    MergeSort(&begin_);
    RootMod();
  }
}

template <typename value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::Begin() {
  return iterator(root_->pNext_);
}

template <typename value_type>
typename s21::List<value_type>::const_iterator s21::List<value_type>::Cbegin()
    const {
  return const_iterator(root_->pNext_);
}

template <typename value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::End() {
  return iterator(root_);
}

template <typename value_type>
typename s21::List<value_type>::const_iterator s21::List<value_type>::Cend()
    const {
  return const_iterator(root_);
}

template <typename value_type>
typename s21::List<value_type>::iterator s21::List<value_type>::Insert(
    iterator pos, const_reference data) {
  if (this->Empty()) {
    begin_ = end_ = new Element(data);
    if (!begin_ || !end_) throw std::bad_alloc();
    begin_->pNext_ = end_;
    end_->pPrev_ = begin_;
    pos = iterator(begin_);
  } else {
    Element *new_element =
        new Element(data, pos.current_, pos.current_->pPrev_);

    pos.current_->pPrev_->pNext_ = new_element;
    pos.current_->pPrev_ = new_element;

    if (pos.current_ == begin_) {
      begin_ = pos.current_->pPrev_;
      root_->pNext_ = begin_;
    }
    if (pos.current_ == root_) end_ = pos.current_->pPrev_;
  }

  RootMod();

  if (count_elements_ == 0)
    pos = iterator(root_->pNext_);
  else
    pos = iterator(pos.current_->pPrev_);
  count_elements_++;
  return pos;
}

template <typename value_type>
void s21::List<value_type>::Erase(iterator pos) {
  if (pos.current_ == root_) throw std::out_of_range("Iter doesn't exist");
  if (Empty()) throw std::out_of_range("List doesn't have elements");
  Element *currElement = pos.current_;
  if (count_elements_ > 1) {
    Element *prevElement = currElement->pPrev_;
    std::swap(currElement->pPrev_, currElement->pNext_->pPrev_);
    prevElement->pNext_ = currElement->pNext_;
    if (pos.current_ == begin_) begin_ = prevElement->pNext_;
    if (pos.current_ == end_) end_ = prevElement;
    RootMod();
  } else {
    root_->pNext_ = root_;
    root_->pPrev_ = root_;
  }
  count_elements_--;
  delete currElement;
  currElement = nullptr;
}

template <typename value_type>
void s21::List<value_type>::Splice(iterator pos, List<value_type> &other) {
  if (other.Empty()) throw std::out_of_range("The other list is empty");
  if (this != &other) {
    Element *currElement = pos.current_;
    currElement->pPrev_->pNext_ = other.begin_;
    other.begin_->pPrev_ = currElement->pPrev_;
    currElement->pNext_->pPrev_ = other.end_;

    other.end_->pNext_ = currElement;
    if (pos.current_ == begin_) {
      begin_ = other.begin_;
      root_->pNext_ = begin_;
    }
    if (pos.current_ == root_) {
      root_->pPrev_ = end_;
      end_ = other.end_;
    }
    RootMod();
    count_elements_ += other.count_elements_;
    other.ListDefault();
  } else {
    this->Clear();
  }
}

template <typename value_type>
template <typename... Args>
typename s21::List<value_type>::iterator s21::List<value_type>::Emplace(
    const_iterator pos, Args &&...args) {
  iterator it(const_cast<Element *>(pos.current_));
  return this->Insert(it, value_type(std::forward<Args>(args)...));
}

template <typename value_type>
template <typename... Args>
void s21::List<value_type>::EmplaceBack(Args &&...args) {
  PushBack(value_type(std::forward<Args>(args)...));
}

template <typename value_type>
template <typename... Args>
void s21::List<value_type>::EmplaceFront(Args &&...args) {
  PushFront(value_type(std::forward<Args>(args)...));
}

template <typename value_type>
void s21::List<value_type>::Unique() {
  if (count_elements_ <= 1) return;
  iterator it = Begin();
  for (; it != End();) {
    iterator tmp = it;
    ++it;
    if (*tmp == tmp.current_->pNext_->value_ && count_elements_ > 1) {
      this->Erase(tmp);
    }
  }
}

template <typename value_type>
void s21::List<value_type>::RootMod() {
  root_->pNext_ = begin_;
  root_->pPrev_ = end_;
  begin_->pPrev_ = root_;
  end_->pNext_ = root_;
}

template <typename value_type>
void s21::List<value_type>::ListDefault() {
  count_elements_ = 0;
  begin_ = nullptr;
  end_ = nullptr;
  root_->pNext_ = root_;
  root_->pPrev_ = root_;
}

template <typename value_type>
void s21::List<value_type>::SwapFields(List<value_type> &other) {
  if (this != &other) {
    std::swap(root_, other.root_);
    std::swap(begin_, other.begin_);
    std::swap(end_, other.end_);
    std::swap(count_elements_, other.count_elements_);
  }
}

template <typename value_type>
void s21::List<value_type>::CopyElements(const List<value_type> &other) {
  const_iterator it_other = other.Cbegin();
  for (; it_other != other.Cend(); ++it_other) PushBack(*it_other);
}

template <typename value_type>
void s21::List<value_type>::MergeSort(Element **n) {
  Element *copy_n = *n;
  if (copy_n == nullptr || copy_n->pNext_ == nullptr) return;
  Element *elem_1;
  Element *elem_2;
  SplitElement(copy_n, &elem_1, &elem_2);
  MergeSort(&elem_1);
  MergeSort(&elem_2);
  *n = MergeElements(elem_1, elem_2);
}

template <typename value_type>
void s21::List<value_type>::SplitElement(Element *n, Element **elem_1,
                                         Element **elem_2) {
  Element *slow = n;
  Element *fast = n;

  while (fast->pNext_ != nullptr && fast->pNext_->pNext_ != nullptr) {
    slow = slow->pNext_;
    fast = fast->pNext_->pNext_;
  }
  *elem_1 = n;
  *elem_2 = slow->pNext_;
  if (slow->pNext_ != nullptr) {
    slow->pNext_ = nullptr;
  }
}

template <typename value_type>
typename s21::List<value_type>::Element *s21::List<value_type>::MergeElements(
    Element *elem_1, Element *elem_2) {
  if (!elem_1) return elem_2;
  if (!elem_2) return elem_1;

  Element *return_element{};
  if (elem_1->value_ < elem_2->value_) {
    elem_1->pNext_ = MergeElements(elem_1->pNext_, elem_2);
    elem_1->pNext_->pPrev_ = elem_1;
    elem_1->pPrev_ = nullptr;
    if (elem_2->value_ > end_->value_) {
      end_ = elem_2;
    }
    return_element = elem_1;
  } else {
    elem_2->pNext_ = MergeElements(elem_1, elem_2->pNext_);
    elem_2->pNext_->pPrev_ = elem_2;
    elem_2->pPrev_ = nullptr;
    if (elem_1->value_ > end_->value_) {
      end_ = elem_1;
    }
    return_element = elem_2;
  }
  return return_element;
}

template <typename value_type>
void s21::List<value_type>::ReinitializationList(List<value_type> &other) {
  other.root_ = new Element(value_type{});
  other.root_->pNext_ = other.root_;
  other.root_->pPrev_ = other.root_;
}

}  // namespace s21

#endif  //  SRC_INCLUDES_S21_LIST_H
