#ifndef UTILS_HPP_
# define UTILS_HPP_

namespace ft {

  /* enable_if */
  template <bool Cond, class T = void> struct enable_if {};
  template <class T> struct enable_if<true, T> { typedef T type; };

  /* equal */
  template <class InputIterator1, class InputIterator2>
  bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
    while (first1 != last1) {
      if (!(*first1 == *first2)) return (false);
      ++first1;
      ++first2;
    }
    return (true);
  }
  template <class InputIterator1, class InputIterator2, class BinaryPredicate>
  bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
    while (first1 != last1) {
      if (!pred(*first1, *first2)) return (false);
      ++first1;
      ++first2;
    }
    return (true);
  }

  /* lexicographical_compare */
  template <class InputIterator1, class InputIterator2>
  bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2) {
      while (first1 != last1) {
        if (first2 == last2 || *first2 < *first1) return (false);
        else if (*first1 < *first2) return (true);
        ++first1;
        ++first2;
      }
      return (first2 != last2);
    }
  template <class InputIterator1, class InputIterator2, class Compare>
  bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2, Compare comp) {
      for (; (first1 != last1) && (first2 != last2); ++first1, ++first2) {
        if (comp(*first1, *first2)) return (true);
        if (comp(*first2, *first1)) return (false);
      }
      return ((first1 == last1) && (first2 != last2));
    }
}

#endif
