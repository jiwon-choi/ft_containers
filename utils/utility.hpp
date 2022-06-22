#ifndef UTILITY_HPP_
# define UTILITY_HPP_

/*
** pair (make_pair)
*/

namespace ft {
  template <class T1, class T2>
  struct pair {
    /* ============================================================ */
    /*                                                              */
    /*                         Member types                         */
    /*                                                              */
    /* ============================================================ */
    typedef T1      first_type;
    typedef T2      second_type;

    /* ============================================================ */
    /*                                                              */
    /*                        Member objects                        */
    /*                                                              */
    /* ============================================================ */
    first_type      first;
    second_type     second;

    /* ============================================================ */
    /*                                                              */
    /*                       Member functions                       */
    /*                                                              */
    /* ============================================================ */

    /* Constructor (1) default */
    pair()                                          : first(first_type()), second(second_type()) {}
    /* Constructor (2) copy */
    template<class U, class V>
    pair(const pair<U, V>& pr)                      : first(pr.first), second_type(pr.second) {}
    /* Constructor (3) initialization */
    pair(const first_type& a, const second_type& b) : first(a), second(b) {}

    /*
    ** Assign contents
    ** implicitly declared
    */
    pair& operator=(const pair& pr) {
      first = pr.first;
      second = pr.second;
      return (*this);
    }
  };

  /* ============================================================ */
  /*                                                              */
  /*                Non-member function overloads                 */
  /*                                                              */
  /* ============================================================ */

  template <class T1, class T2>
  bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return (lhs.first == rhs.first && lhs.second == rhs.second);
  }
  template <class T1, class T2>
  bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return (!(lhs == rhs));
  }
  template <class T1, class T2>
  bool operator< (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
  }
  template <class T1, class T2>
  bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return (!(rhs < lhs));
  }
  template <class T1, class T2>
  bool operator> (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return (rhs < lhs);
  }
  template <class T1, class T2>
  bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
    return (!(lhs < rhs));
  }

  /* make_pair */
  template <class T1, class T2>
  pair<T1, T2> make_pair(T1 x, T2 y) {
    return (pair<T1, T2>(x, y));
  }
}

#endif
