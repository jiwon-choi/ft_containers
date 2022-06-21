#ifndef STACK_HPP_
# define STACK_HPP_

# include "vector.hpp"

namespace ft {
  template < class T, class Container = vector<T> >
  class stack {
    public:
    /* ============================================================ */
    /*                                                              */
    /*                         Member types                         */
    /*                                                              */
    /* ============================================================ */
    typedef Container                             container_type;
    typedef typename Container::value_type        value_type;
    typedef typename Container::size_type         size_type;

    protected:
    container_type    _c;

    /* ============================================================ */
    /*                                                              */
    /*                       Member functions                       */
    /*                                                              */
    /* ============================================================ */

    public:
    /* Constructor */
    explicit stack(const container_type& ctnr = container_type())
      : _c(ctnr) {}

    /* Test whether container is empty */
    bool empty() const {
      return (_c.size() == 0 ? true : false);
    }

    /* Return size */
    size_type size() const {
      return (_c.size());
    }

    /* Access next element */
    value_type& top() {
      return (_c.back());
    }
    const value_type& top() const {
      return (_c.back());
    }

    /* Insert element */
    void push (const value_type& val) {
      return (_c.push_back(val));
    }

    /* Remove top element */
    void pop() {
      return (_c.pop_back());
    }

    template <class T_, class Container_>
    friend bool operator==(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);
    template <class T_, class Container_>
    friend bool operator!=(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);
    template <class T_, class Container_>
    friend bool operator< (const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);
    template <class T_, class Container_>
    friend bool operator<=(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);
    template <class T_, class Container_>
    friend bool operator> (const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);
    template <class T_, class Container_>
    friend bool operator>=(const stack<T_, Container_>& lhs, const stack<T_, Container_>& rhs);
  };

  /* ============================================================ */
  /*                                                              */
  /*                Non-member function overloads                 */
  /*                                                              */
  /* ============================================================ */

  template <class T, class Container>
  bool operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return (lhs._c == rhs._c);
  }
  template <class T, class Container>
  bool operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return (lhs._c != rhs._c);
  }
  template <class T, class Container>
  bool operator< (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return (lhs._c < rhs._c);
  }
  template <class T, class Container>
  bool operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return (lhs._c <= rhs._c);
  }
  template <class T, class Container>
  bool operator> (const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return (lhs._c > rhs._c);
  }
  template <class T, class Container>
  bool operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) {
    return (lhs._c >= rhs._c);
  }
}

#endif
