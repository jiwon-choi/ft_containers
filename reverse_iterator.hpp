#ifndef REVERSE_ITERATOR_HPP_
# define REVERSE_ITERATOR_HPP_

# include "iterator.hpp"

namespace ft {
  template <class Iterator>
  class reverse_iterator {
    protected:
    Iterator _base;

    public:
    typedef Iterator                                                iterator_type;
    typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
    typedef typename iterator_traits<Iterator>::value_type          value_type;
    typedef typename iterator_traits<Iterator>::difference_type     difference_type;
    typedef typename iterator_traits<Iterator>::pointer             pointer;
    typedef typename iterator_traits<Iterator>::reference           reference;

    reverse_iterator(void)                                 : _base(nullptr) {}
    explicit reverse_iterator(iterator_type it)            : _base(it) {}
    template <class Iter>
    reverse_iterator(const reverse_iterator<Iter>& rev_it) : _base(rev_it.base()) {}

    operator reverse_iterator<const iterator_type>() const {
      return reverse_iterator<const iterator_type>(_base);
    }

    template <class U>
    reverse_iterator& operator=(const reverse_iterator<U>& other) {
      // if (this != &other)
      _base = other.base();
      return (*this);
    }

    iterator_type base(void) const { return (_base); }

    reference operator*(void) const {
      iterator_type tmp(_base);
      return (*--tmp);
    }
    pointer   operator->(void) const {
      return (&(operator*()));
    }
    reference operator[](difference_type n) const {
      return (base()[-n - 1]);
    }

    reverse_iterator operator+(difference_type n) const { return (reverse_iterator(base() - n)); }
    reverse_iterator operator-(difference_type n) const { return (reverse_iterator(base() + n)); }

    reverse_iterator& operator++(void) {
      --_base;
      return (*this);
    }
    reverse_iterator operator++(int) {
      reverse_iterator tmp(*this);
      _base--;
      return (tmp);
    }
    reverse_iterator& operator--(void) {
      ++_base;
      return (*this);
    }
    reverse_iterator operator--(int) {
      reverse_iterator tmp(*this);
      _base++;
      return (tmp);
    }

    reverse_iterator& operator+=(difference_type n) {
      _base -= n;
      return (*this);
    }
    reverse_iterator& operator-=(difference_type n) {
      _base += n;
      return (*this);
    }
  };

  template <class Iterator1, class Iterator2>
  bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs.base() == rhs.base()); }
  template <class Iterator1, class Iterator2>
  bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs.base() != rhs.base()); }
  template <class Iterator1, class Iterator2>
  bool operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs.base() > rhs.base()); }
  template <class Iterator1, class Iterator2>
  bool operator> (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs.base() < rhs.base()); }
  template <class Iterator1, class Iterator2>
  bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs.base() >= rhs.base()); }
  template <class Iterator1, class Iterator2>
  bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) { return (lhs.base() <= rhs.base()); }

  template <class Iterator>
  reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) {
    return (rev_it + n);
  }

  template <class Iterator1, class Iterator2>
  typename reverse_iterator<Iterator1>::difference_type operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return (rhs.base() - lhs.base());
  }

}

#endif
