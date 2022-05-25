#ifndef ITERATOR_HPP_
# define ITERATOR_HPP_

# include <cstddef> // ptrdiff_t

namespace ft {

  class input_iterator_tag  {};
  class output_iterator_tag {};
  class forward_iterator_tag       : public input_iterator_tag         {};
  class bidirectional_iterator_tag : public forward_iterator_tag       {};
  class random_access_iterator_tag : public bidirectional_iterator_tag {};

  template <class Category, class T, class Distance = ptrdiff_t,
            class Pointer = T*, class Reference = T&>
  class iterator {
    public:
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
    typedef Category    iterator_category;
  };

  template <class Iterator>
  class iterator_traits {
    public:
    typedef typename Iterator::difference_type    difference_type;
    typedef typename Iterator::value_type         value_type;
    typedef typename Iterator::pointer            pointer;
    typedef typename Iterator::reference          reference;
    typedef typename Iterator::iterator_category  iterator_category;
  };

  template <class T>
  class iterator_traits<T*> {
    public:
    typedef ptrdiff_t                   difference_type;
    typedef T                           value_type;
    typedef T*                          pointer;
    typedef T&                          reference;
    typedef random_access_iterator_tag  iterator_category;
  };

  template <class T>
  class iterator_traits<const T*> {
    public:
    typedef ptrdiff_t                   difference_type;
    typedef T                           value_type;
    typedef const T*                    pointer;
    typedef const T&                    reference;
    typedef random_access_iterator_tag  iterator_category;
  };

  /*
  ** functions : Iterator operations
  */
  /*
  ** 반복자 사이의 거리 반환, first와 last 사이의 요소 수를 계산한다.
  ** random-access iterator의 경우, 함수는 operator-를 사용하여 이를 계산한다. 그렇지 않으면 함수가 operator++을 반복적으로 사용한다.
  */
  // template <class InputIterator>
  // typename iterator_traits<InputIterator>::difference_type
  //   distance(InputIterator first, InputIterator last) {
  //     typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
  //     while (first != last) {
  //       first++;
  //       rtn++;
  //     }
  //     return (rtn);
  //   }

}

#endif
