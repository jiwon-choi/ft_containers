#ifndef STACK_HPP_
# define STACK_HPP_

# include "vector.hpp"

namespace ft {
  template < class T, class Container = ft::vector<T> >
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
    stack(const stack& other)
      : _c(other._c) {}

    /* Destructor */
    ~stack() {}

    /* Assign values to the container adaptor */
    stack& operator=(const stack& other) {
      if (this != &other) {
        _c = other._c;
      }
      return (*this);
    }

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

    /* ============================================================ */
    /*                                                              */
    /*                Non-member function overloads                 */
    /*                                                              */
    /* ============================================================ */

    friend bool operator==(const stack& lhs, const stack& rhs) {
      return (lhs._c == rhs._c);
    }
    friend bool operator!=(const stack& lhs, const stack& rhs) {
      return (lhs._c != rhs._c);
    }
    friend bool operator< (const stack& lhs, const stack& rhs) {
      return (lhs._c < rhs._c);
    }
    friend bool operator<=(const stack& lhs, const stack& rhs) {
      return (lhs._c <= rhs._c);
    }
    friend bool operator> (const stack& lhs, const stack& rhs) {
      return (lhs._c > rhs._c);
    }
    friend bool operator>=(const stack& lhs, const stack& rhs) {
      return (lhs._c >= rhs._c);
    }
  };

}

#endif
