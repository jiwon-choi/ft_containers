#ifndef REVERSE_ITERATOR_HPP_
# define REVERSE_ITERATOR_HPP_

# include "iterator.hpp"

namespace ft {
  template <class Iterator>
  class reverse_iterator {
    protected:
    Iterator _ptr;

    public:
    typedef Iterator                                                iterator_type;
    typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
    typedef typename iterator_traits<Iterator>::value_type          value_type;
    typedef typename iterator_traits<Iterator>::difference_type     difference_type;
    typedef typename iterator_traits<Iterator>::pointer             pointer;
    typedef typename iterator_traits<Iterator>::reference           reference;

    reverse_iterator(void)                                 : _ptr() {}
    explicit reverse_iterator(iterator_type it)            : _ptr(it) {}
    template <class Iter>
    reverse_iterator(const reverse_iterator<Iter>& rev_it) : _ptr(rev_it.base()) {}

    iterator_type base(void) const { return (_ptr); }

    reference operator*(void) const {
      iterator_type tmp(_ptr);
      return (*(--tmp));
    }
    pointer   operator->(void) const {
      return (&(operator*()));
    }
    reference operator[](difference_type n) const {
      return (base()[-n - 1]);
    }

    reverse_iterator operator+(difference_type n) const { return (reverse_iterator(_ptr - n)); }
    reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_ptr + n)); }

    reverse_iterator& operator++(void) {
      --_ptr;
      return (*this);
    }
    reverse_iterator operator++(int) {
      reverse_iterator tmp(*this);
      _ptr--;
      return (tmp);
    }
    reverse_iterator& operator--(void) {
      ++_ptr;
      return (*this);
    }
    reverse_iterator operator--(int) {
      reverse_iterator tmp(*this);
      _ptr++;
      return (tmp);
    }

    reverse_iterator& operator+=(difference_type n) {
      _ptr -= n;
      return (*this);
    }
    reverse_iterator& operator-=(difference_type n) {
      _ptr += n;
      return (*this);
    }
  };

  template <class Iterator>
  bool operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }
  template <class Iterator>
  bool operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }
  template <class Iterator>
  bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }
  template <class Iterator>
  bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }
  template <class Iterator>
  bool operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }
  template <class Iterator>
  bool operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

  template <class Iterator>
  reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
    return (rev_it - n);
  }

  template <class Iterator>
  typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
    return (rhs.base() - lhs.base());
  }

}

#endif
