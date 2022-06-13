#ifndef ITERATOR_HPP_
# define ITERATOR_HPP_

# include <cstddef> // ptrdiff_t

namespace ft {
  /* ============================================================ */
  /*                                                              */
  /*                        Category tags                         */
  /*                                                              */
  /* ============================================================ */

  class input_iterator_tag  {};   // 전진만 가능, 한 번에 하나만 읽기 가능
  class output_iterator_tag {};   // 전진만 가능, 한 번에 하나만 쓰기 가능
  class forward_iterator_tag       : public input_iterator_tag         {};  // 전진만 가능, 한 번에 여러 개 읽고 쓰기 가능
  class bidirectional_iterator_tag : public forward_iterator_tag       {};  // 전/후진 모두 가능, 한 번에 여러 개 읽고 쓰기 가능
  class random_access_iterator_tag : public bidirectional_iterator_tag {};  // 반복자를 임의의 위치만큼 전/후진 가능


  /* ============================================================ */
  /*                                                              */
  /*                     Iterator base class                      */
  /*                                                              */
  /* ============================================================ */

  template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
  class iterator {
    public:
    typedef T           value_type;         // 반복자가 가리키는 요소의 유형
    typedef Distance    difference_type;    // 두 반복자 간의 차이
    typedef Pointer     pointer;            // 반복자가 가리키는 요소에 대한 포인터
    typedef Reference   reference;          // 반복자가 가리키는 요소에 대한 레퍼런스
    typedef Category    iterator_category;  // 반복자가 속한 범주, 위의 *_iterator_tag들 중 하나여야 한다.
  };


  /* ============================================================ */
  /*                                                              */
  /*                       Iterator traits                        */
  /*                                                              */
  /* ============================================================ */

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
  ** distance
  ** 반복자 사이의 거리 반환, first와 last 사이의 요소 수를 계산한다.
  ** random-access iterator의 경우, 함수는 operator-를 사용하여 이를 계산한다. 그렇지 않으면 함수가 operator++을 반복적으로 사용한다.
  */
  // template <class InputIterator>
  // typename iterator_traits<InputIterator>::difference_type
  //   distance(InputIterator first, InputIterator last) {
  //     typename ft::iterator_traits<InputIterator>::difference_type dist = 0;
  //     while (first != last) {
  //       first++;
  //       dist++;
  //     }
  //     return (dist);
  //   }

}

#endif
