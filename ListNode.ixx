module;
#include <memory>
#include <optional>

export module ListNode;

namespace listnode
{

export template <typename T> struct ListNode
{
  T value;
  std::unique_ptr<ListNode<T>> next;
  explicit ListNode() : next(nullptr)
  {
  }
  explicit ListNode(T &&x) : value(x), next(nullptr)
  {
  }
  explicit ListNode(T &&x, std::unique_ptr<ListNode<T>> &&next_ptr) : value(std::move(x)), next(std::move(next_ptr))
  {
  }

  ListNode<T> &operator=(T val)
  {
    value = val;
    return *this;
  }
};

export template <typename T> struct IteratorBase
{
public:
  using difference_type = std::ptrdiff_t;
  using value_type = ListNode<T>;
  using pointer = ListNode<T> *;
  using reference = ListNode<T> &;

  explicit IteratorBase(pointer ptr) : m_ptr(ptr)
  {
  }

  pointer operator->()
  {
    return m_ptr;
  }

protected:
  pointer m_ptr;
};

export template <typename T> struct Iterator : public IteratorBase<T>
{
public:
  using iterator_category = std::forward_iterator_tag;

  explicit Iterator(IteratorBase<T>::pointer ptr) : IteratorBase<T>(ptr)
  {
  }

  IteratorBase<T>::reference &operator*() const
  {
    return *this->m_ptr;
  }

  // Prefix increment
  Iterator<T> &operator++()
  {
    this->m_ptr = this->m_ptr->next.get();
    return *this;
  }

  // Postfix increment
  Iterator<T> &operator++(int)
  {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  friend bool operator==(const Iterator<T> &a, const Iterator<T> &b)
  {
    return a.m_ptr == b.m_ptr;
  };
  friend bool operator!=(const Iterator<T> &a, const Iterator<T> &b)
  {
    return a.m_ptr != b.m_ptr;
  };
};

export template <typename T> struct OutputIterator : public IteratorBase<T>
{
public:
  using iterator_category = std::output_iterator_tag;

  explicit OutputIterator(IteratorBase<T>::pointer ptr) : IteratorBase<T>(ptr), m_at_begin(true)
  {
  }

  OutputIterator<T> &operator*()
  {
    return *this;
  }

  OutputIterator<T> &operator++()
  {
    return *this;
  }

  OutputIterator<T> &operator++(int)
  {
    return *this;
  }

  OutputIterator<T> &operator=(const T &val)
  {
    if (!this->m_ptr)
      return *this;

    if (m_at_begin)
    {
      *this->m_ptr = val;
      m_at_begin = false;
      return *this;
    }

    if (!this->m_ptr->next)
      this->m_ptr->next = std::make_unique<IteratorBase<T>::value_type>();

    this->m_ptr = this->m_ptr->next.get();
    *this->m_ptr = val;
    return *this;
  }

private:
  bool m_at_begin;
};

export template <typename T> Iterator<T> begin(ListNode<T> &node)
{
  return Iterator<T>(&node);
}
export template <typename T> Iterator<T> end(ListNode<T> &)
{
  return Iterator<T>(nullptr);
}

export template <typename T> OutputIterator<T> back_inserter(ListNode<T> &node)
{
  return OutputIterator<T>(&node);
}

} // namespace listnode