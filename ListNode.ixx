module;
#include <memory>
#include <optional>

export module ListNode;

export template <typename T> struct ListNode
{
  T val;
  std::unique_ptr<ListNode<T>> next;
  ListNode() : val(0), next(nullptr)
  {
  }
  explicit ListNode(T &&x) : val(x), next(nullptr)
  {
  }
  explicit ListNode(T &&x, std::unique_ptr<ListNode<T>> &&next_ptr) : val(std::move(x)), next(std::move(next_ptr))
  {
  }

  struct Iterator
  {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = ListNode<T>;
    using pointer = ListNode<T> *;   // or also value_type*
    using reference = ListNode<T> &; // or also value_type&
    Iterator(pointer ptr) : m_ptr(ptr)
    {
    }

    reference operator*() const
    {
      return *m_ptr;
    }
    pointer operator->()
    {
      return m_ptr;
    }

    // Prefix increment
    Iterator &operator++()
    {
      m_ptr = m_ptr->next.get();
      return *this;
    }

    // Postfix increment
    Iterator operator++(int)
    {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b)
    {
      return a.m_ptr == b.m_ptr;
    };
    friend bool operator!=(const Iterator &a, const Iterator &b)
    {
      return a.m_ptr != b.m_ptr;
    };

  private:
    pointer m_ptr;
  };

  Iterator begin()
  {
    return Iterator(this);
  }
  Iterator end()
  {
    return Iterator(nullptr);
  }
};