module;
#include <memory>
#include <optional>

export module listnode;

namespace listnode
{

export template <typename T> struct ListNode
{
  T value;
  std::unique_ptr<ListNode<T>> next;

  ListNode<T> &operator=(T val)
  {
    value = std::move(val);
    return *this;
  }

  using value_type = T;
};

export template <typename T> auto make_node(T val) -> ListNode<T>
{
  return ListNode<T>{.value = val, .next = nullptr};
}

export template <class NodeType> struct Iterator
{
public:
  using iterator_category = std::forward_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = NodeType;
  using pointer = NodeType *;
  using reference = NodeType &;

  explicit Iterator(pointer ptr) : m_ptr(ptr)
  {
  }

  reference &operator*() const
  {
    return *m_ptr;
  }

  pointer operator->()
  {
    return m_ptr;
  }

  // Prefix increment
  Iterator<NodeType> &operator++()
  {
    m_ptr = m_ptr->next.get();
    return *this;
  }

  // Postfix increment
  Iterator<NodeType> &operator++(int)
  {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  friend bool operator==(const Iterator<NodeType> &a, const Iterator<NodeType> &b)
  {
    return a.m_ptr == b.m_ptr;
  };
  friend bool operator!=(const Iterator<NodeType> &a, const Iterator<NodeType> &b)
  {
    return a.m_ptr != b.m_ptr;
  };

private:
  pointer m_ptr;
};

export template <typename T> struct OutputIterator
{
public:
  using iterator_category = std::output_iterator_tag;
  using difference_type = std::ptrdiff_t;
  using value_type = ListNode<T>;
  using pointer = ListNode<T> *;
  using reference = ListNode<T> &;

  explicit OutputIterator(pointer ptr) : m_ptr(ptr), m_at_begin(true)
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
      this->m_ptr->next = std::make_unique<value_type>();

    this->m_ptr = this->m_ptr->next.get();
    *this->m_ptr = val;
    return *this;
  }

private:
  pointer m_ptr;
  bool m_at_begin;
};

export template <typename T> Iterator<ListNode<T>> begin(ListNode<T> &node)
{
  return Iterator<ListNode<T>>(&node);
}
export template <typename T> Iterator<ListNode<T>> end(ListNode<T> &)
{
  return Iterator<ListNode<T>>(nullptr);
}

export template <typename T> Iterator<const ListNode<T>> begin(const ListNode<T> &node)
{
  return Iterator<const ListNode<T>>(&node);
}
export template <typename T> Iterator<const ListNode<T>> end(const ListNode<T> &)
{
  return Iterator<const ListNode<T>>(nullptr);
}

export template <typename T> OutputIterator<T> back_inserter(ListNode<T> &node)
{
  return OutputIterator<T>(&node);
}

} // namespace listnode