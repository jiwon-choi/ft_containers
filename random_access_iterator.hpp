#ifndef RANDOM_ACCESS_ITERATOR_HPP_
# define RANDOM_ACCESS_ITERATOR_HPP_

# include "iterator.hpp"

namespace ft {
  template <typename T>
  class random_access_iterator : public iterator<random_access_iterator_tag, T> {
    public:
    typedef typename iterator<random_access_iterator_tag, T>::value_type          value_type;
    typedef typename iterator<random_access_iterator_tag, T>::difference_type     difference_type;
    typedef typename iterator<random_access_iterator_tag, T>::pointer             pointer;
    typedef typename iterator<random_access_iterator_tag, T>::reference           reference;
    typedef typename iterator<random_access_iterator_tag, T>::iterator_category   iterator_category;

    protected:
    pointer _ptr;

    public:
    random_access_iterator(void)                              : _ptr(nullptr) {}
    random_access_iterator(pointer ptr)                       : _ptr(ptr) {}
    random_access_iterator(const random_access_iterator<T>& ref) : _ptr(ref._ptr) {}

    operator random_access_iterator<const value_type>() const {
      return random_access_iterator<const value_type>(_ptr);
    }

    random_access_iterator& operator=(const random_access_iterator& ref) {
      if (this != &ref)
        _ptr = ref._ptr;
      return (*this);
    }

    virtual ~random_access_iterator() {}

    pointer base(void) const { return (_ptr); }

    reference operator* (void) const              { return (*_ptr); }
    pointer   operator->(void) const              { return (&(operator*())); }
    reference operator[](difference_type n) const { return (_ptr[n]); }

    random_access_iterator operator+(difference_type n) const { return (_ptr + n); }
    random_access_iterator operator-(difference_type n) const { return (_ptr - n); }

    random_access_iterator& operator++(void) {
      ++_ptr;
      return (*this);
    }
    random_access_iterator operator++(int) {
      random_access_iterator tmp(*this);
      _ptr++;
      return (tmp);
    }
    random_access_iterator& operator--(void) {
      --_ptr;
      return (*this);
    }
    random_access_iterator operator--(int) {
      random_access_iterator tmp(*this);
      _ptr--;
      return (tmp);
    }

    random_access_iterator& operator+=(difference_type n) {
      _ptr += n;
      return (*this);
    }
    random_access_iterator& operator-=(difference_type n) {
      _ptr -= n;
      return (*this);
    }
  };

  template <typename T>
  bool operator==(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return (lhs.base() == rhs.base()); }
  template <typename T>
  bool operator!=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return (lhs.base() != rhs.base()); }
  template <typename T>
  bool operator< (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return (lhs.base() < rhs.base()); }
  template <typename T>
  bool operator> (const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return (lhs.base() > rhs.base()); }
  template <typename T>
  bool operator<=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return (lhs.base() <= rhs.base()); }
  template <typename T>
  bool operator>=(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) { return (lhs.base() >= rhs.base()); }

  template <typename T>
  random_access_iterator<T> operator+(typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& rev_it) {
    return (rev_it + n);
  }

  template <typename T>
  typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T>& lhs, const random_access_iterator<T>& rhs) {
    return (lhs.base() - rhs.base());
  }
}

#endif
