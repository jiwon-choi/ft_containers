#ifndef VECTOR_HPP_
# define VECTOR_HPP_

# include <memory>  // std::allocator
# include "utils/iterator.hpp"
# include "utils/algorithm.hpp"
# include "utils/type_traits.hpp"

namespace ft {
  template < class T, class Alloc = std::allocator<T> >
  class vector {
    public:
    /* ============================================================ */
    /*                                                              */
    /*                         Member types                         */
    /*                                                              */
    /* ============================================================ */
    typedef T                                                     value_type;
    typedef Alloc                                                 allocator_type;
    typedef typename allocator_type::reference                    reference;                // T&
    typedef typename allocator_type::const_reference              const_reference;          // const T&
    typedef typename allocator_type::pointer                      pointer;                  // T*
    typedef typename allocator_type::const_pointer                const_pointer;            // const T*
    typedef ft::random_access_iterator<value_type>                iterator;
    typedef ft::random_access_iterator<const value_type>          const_iterator;
    typedef ft::reverse_iterator<iterator>                        reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                  const_reverse_iterator;
    typedef typename iterator_traits<iterator>::difference_type   difference_type;          // ptrdiff_t
    typedef typename allocator_type::size_type                    size_type;                // size_t

    private:
    allocator_type    _alloc;
    pointer           _ptr;
    size_type         _capacity;  // 할당된 사이즈
    size_type         _size;      // 실제로 담겨 있는 데이터의 수

    public:
    /* ============================================================ */
    /*                                                              */
    /*                       Member functions                       */
    /*                                                              */
    /* ============================================================ */

    /*
    ** Constructor (1) default
    ** element가 없는 빈 컨테이너를 생성한다.
    */
    explicit vector(const allocator_type& alloc = allocator_type())
      : _alloc(alloc), _ptr(NULL), _capacity(0), _size(0) {}
    /*
    ** Constructor (2) fill
    ** n개의 element를 가지는 컨테이너를 생성하고, 각 element는 val을 복사해 채운다.
    */
    explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
      : _alloc(alloc), _ptr(NULL), _capacity(n), _size(n) {
        _ptr = _alloc.allocate(n);
        for (size_type i = 0; i < n; i++)
          _alloc.construct(_ptr + i, val);
      }
    /*
    ** Constructor (3) range
    ** range[first, last]만큼의 element를 가지는 컨테이너를 생성하고, 각 element는 range와 동일한 순서로 구성된다.
    */
    template <class InputIterator>
    vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
      typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr)
      : _alloc(alloc), _size(0) {
        difference_type n = last - first;
        _ptr = _alloc.allocate(n);
        _capacity = n;
        for (; first != last; first++)
          push_back(*first);
      }
    /*
    ** Constructor (4) copy
    ** x에 있는 각 element의 복사본을 동일한 순서대로 복사하여 컨테이너를 생성한다.
        _capacity = n;
    */
    vector(const vector& x)
      : _alloc(allocator_type()), _ptr(NULL), _capacity(0), _size(0) {
        *this = x;
      }

    /*
    ** Destructor
    ** 모든 element를 파괴하고 allocator를 사용하여 할당 해제한다.
    */
    ~vector() {
      clear();
      if (_capacity > 0)
        _alloc.deallocate(_ptr, _capacity);
    }

    /*
    ** Assign content
    ** 재할당하는 경우 현재 allocator를 유지한다.
    */
    vector& operator=(const vector& x) {
      if (this != &x) {
        clear();
        assign(x.begin(), x.end());
      }
      return (*this);
    }

    /* ============================================================ */
    /*                          Iterators                           */
    /* ============================================================ */

    /*
    ** Return iterator to beginning
    ** 벡터의 첫 번째 element를 가리키는 반복자를 반환한다. 직접 참조를 반환하는 front와 달리 랜덤 액세스 반복자를 반환한다.
    */
    iterator begin() {
      return (iterator(_ptr));
    }
    const_iterator begin() const {
      return (const_iterator(_ptr));
    }

    /*
    ** Return iterator to end
    ** 벡터의 마지막 element의 뒤에 있는 이론적 요소의 iterator를 반환한다. 컨테이너가 비어 있다면 begin과 동일한 결과를 반환한다.
    ** 실질적인 element를 가리키는 것이 아니므로 역참조는 불가능하다.
    */
    iterator end() {
      return (iterator(_ptr + _size));
    }
    const_iterator end() const {
      return (const_iterator(_ptr + _size));
    }

    /*
    ** Return reverse iterator to reverse beginning
    ** 벡터의 마지막 element를 가리키는 역방향 반복자를 반환한다. 직접 참조를 반환하는 back과 다르게 역방향 랜덤 액세스 반복자를 반환한다.
    */
    reverse_iterator rbegin() {
      return (reverse_iterator(end()));
    }
    const_reverse_iterator rbegin() const {
      return (const_reverse_iterator(end()));
    }

    /*
    ** Return reverse iterator to reverse end
    ** 벡터의 첫 번째 element의 앞에 있는 이론적인 요소를 가리키는 reverse iterator를 반환한다.
    */
    reverse_iterator rend() {
      return (reverse_iterator(begin()));
    }
    const_reverse_iterator rend() const {
      return (const_reverse_iterator(begin()));
    }

    /* ============================================================ */
    /*                           Capacity                           */
    /* ============================================================ */

    /*
    ** Return size
    ** 실제로 벡터에 저장된 수를 의미하며, allocator에 의해 할당된 사이즈와 동일하지 않을 수 있다
    */
    size_type size() const {
      return (_size);
    }

    /*
    ** Return maximum size
    ** 컨테이너가 잠재적으로 할당될 수 있는 최대 사이즈를 반환한다.
    */
    size_type max_size() const {
      return (_alloc.max_size());
    }

    /*
    ** Change size
    ** n개의 element를 포함할 수 있도록 컨테이너의 크기를 조정한다.
    ** n이 현재 사이즈보다 작은 경우 사이즈를 n으로 축소하고 이후 element를 제거 및 해제한다.
    ** n이 현재 사이즈보다 큰 경우 val을 복사해서 크기가 n이 되도록 확장한다.
    ** n이 현재 capacity보다 큰 경우 메모리를 재할당한다.
    */
    void resize(size_type n, value_type val = value_type()) {
      if (n > _capacity) reserve(n);
      if (n >= _size) {
        for (size_type i = _size; i < n; i++)
          _alloc.construct(_ptr + i, val);
      } else {
        for (size_type i = n; i < _size; i++)
          _alloc.destroy(_ptr + i);
        _capacity = n;
      }
      _size = n;
    }

    /*
    ** Return size of allocated storage capacity
    ** 벡터의 현재 할당된 메모리 크기를 반환한다. 벡터의 size보다 같거나 클 수 있다.
    */
    size_type capacity() const {
      return (_capacity);
    }

    /* Test whether vector is empty */
    bool empty() const {
      return (size() == 0 ? true : false);
    }

    /*
    ** Request a change in capacity
    ** n이 현재 capacity보다 크면 컨테이너가 스토리지를 재할당하도록 요청한다.
    ** 요청한 크기가 max_size보다 크면 length_error를 throw 한다.
    ** 재할당에 실패할 경우 예외가 발생할 수 있고, bad_alloc이 throw 된다.
    */
    void reserve(size_type n) {
      if (n > max_size()) {
        throw (std::length_error("ft::vector::reserve"));
      } else if (n > _capacity) {
        pointer new_ptr = _alloc.allocate(n);
        for (size_type i = 0; i < _size; i++)
          _alloc.construct(new_ptr + i, *(_ptr + i));
        _alloc.deallocate(_ptr, _capacity);
        _ptr = new_ptr;
        _capacity = n;
      }
    }

    /* ============================================================ */
    /*                        Element access                        */
    /* ============================================================ */

    /*
    ** Access element
    ** 벡터 컨테이너의 n번째 element에 대한 참조를 반환한다.
    ** at 함수와 동작이 동일하지만, at은 경계를 확인하고 요청된 위치가 범위를 벗어난 경우 out_of_range 예외를 throw 한다는 점이 다르다.
    */
    reference operator[](size_type n) {
      return (_ptr[n]);
    }
    const_reference operator[](size_type n) const {
      return (_ptr[n]);
    }

    /*
    ** Access element
    ** 벡터 컨테이너의 n번째 element에 대한 참조를 반환한다.
    ** 유효한 범위인지 확인하여 범위를 넘어가는 경우 out_of_range 예외를 throw 한다.
    */
    reference at(size_type n) {
      if (n >= size()) {
        throw (std::out_of_range("ft::vector::at"));
      } else {
        return (_ptr[n]);
      }
    }
    const_reference at(size_type n) const {
      if (n >= size()) {
        throw (std::out_of_range("ft::vector::at"));
      } else {
        return (_ptr[n]);
      }
    }

    /*
    ** Access first element
    ** 동일한 element에 대해 iterator를 반환하는 begin과 달리 front는 직접 참조를 반환한다.
    ** 빈 컨테이너에서 함수를 호출할 시 정의되지 않은 동작이 발생한다.
    */
    reference front() {
      return (*begin());
    }
    const_reference front() const {
      return (*begin());
    }

    /* Access last element */
    reference back() {
      return (*(end() - 1));
    }
    const_reference back() const {
      return (*(end() - 1));
    }

    /* ============================================================ */
    /*                          Modifiers                           */
    /* ============================================================ */

    /*
    ** Assign vector content
    ** 벡터에 새 컨텐츠를 할당해 데이터를 바꾸고, 그에 따라 size를 수정한다.
    */
    template <class InputIterator>
    void assign(InputIterator first, InputIterator last,
      typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr) {
        clear();
        size_type n = last - first;
        if (n == 0) return ;
        if (n > _capacity) {
          _alloc.deallocate(_ptr, _capacity);
          _ptr = _alloc.allocate(n);
          _capacity = n;
        }
        for (; first != last; first++)
          push_back(*first);
      }
    void assign(size_type n, const value_type& val) {
      clear();
      if (n == 0) return ;
      if (n > _capacity) {
        _alloc.deallocate(_ptr, _capacity);
        _ptr = _alloc.allocate(n);
        _capacity = n;
      }
      for (size_type i = 0; i < n; i++)
        push_back(val);
    }

    /*
    ** Add element at the end
    ** 벡터의 끝에 val를 추가한다.
    */
    void push_back(const value_type& val) {
      if (_size == _capacity)
        empty() ? reserve(1) : reserve(_size * 2);
      _alloc.construct(_ptr + _size, val);
      _size++;
    }

    /*
    ** Delete last element
    ** 마지막 element를 삭제한다.
    */
    void pop_back() {
      if (_size > 0) {
        _alloc.destroy(_ptr + (_size - 1));
        _size--;
      }
    }

    /*
    ** Insert elements
    ** 지정된 위치에 새 element를 삽입힌다.
    */
    iterator insert(iterator position, const value_type& val) {
      size_type idx = position - begin();
      reserve(_size + 1);
      position = begin() + idx;
      move_backward(position);
      _alloc.construct(&(*position), val);
      _size++;
      return (position);
    }
    void insert(iterator position, size_type n, const value_type& val) {
      size_type idx = position - begin();
      reserve(_size + n);
      position = begin() + idx;
      move_backward(position, n);
      for (size_type i = 0; i < n; i++)
        _alloc.construct(&(*(position + i)), val);
      _size += n;
    }
    template <class InputIterator>
    void insert(iterator position, InputIterator first, InputIterator last,
      typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type* = nullptr) {
        size_type idx = position - begin();
        size_type n = last - first;
        reserve(_size + n);
        position = begin() + idx;
        move_backward(position, n);
        for (size_type i = 0; i < n; i++)
          _alloc.construct(&(*(position + i)), *(first + i));
        _size += n;
      }

    /*
    ** Erase elements
    ** 지정된 위치의 단일 element 또는 범위를 제거한다.
    */
    iterator erase(iterator position) {
      if (empty()) return (end());
      iterator it = begin();
      while (it != position) it++;
      _alloc.destroy(&(*it));
      while (it + 1 != end()) {
        _alloc.construct(&(*it), *(it + 1));
        it++;
      }
      pop_back();
      return (position);
    }
    iterator erase(iterator first, iterator last) {
      if (empty()) return (end());
      iterator it = begin();
      iterator rtn = first;
      difference_type dist = last - first;
      while (it != first) it++;
      for (; first != last; first++)
        _alloc.destroy(&(*first));
      while (it + dist != end()) {
        _alloc.construct(&(*it), *(it + dist));
        it++;
      }
      while (dist-- > 0) pop_back();
      return (rtn);
    }

    /* Swap content */
    void swap(vector& x) {
      allocator_type    tmp_alloc = _alloc;
      pointer           tmp_ptr = _ptr;
      size_type         tmp_capacity = _capacity;
      size_type         tmp_size = _size;

      _alloc = x._alloc;
      _ptr = x._ptr;
      _capacity = x._capacity;
      _size = x._size;

      x._alloc = tmp_alloc;
      x._ptr = tmp_ptr;
      x._capacity = tmp_capacity;
      x._size = tmp_size;
    }

    /*
    ** Clear content
    ** 벡터의 모든 element를 제거하고 컨테이너의 크기를 0으로 유지한다.
    */
    void clear() {
      if (_size > 0) {
        for (iterator it = begin(); it != end(); it++)
          _alloc.destroy(&(*it));
        _size = 0;
      }
    }

    /* ============================================================ */
    /*                          Allocator                           */
    /* ============================================================ */

    /* Get allocator */
    allocator_type get_allocator() const {
      return (Alloc(_alloc));
    }


    void move_backward(iterator position, size_type n = 1) {
      if (position == end()) return ;
        move_backward(position + 1, n);
      _alloc.construct(&(*(position + n)), *position);

      // for (iterator it = end(); it != position; it--) {
      //   _alloc.construct(&(*it), *(it - n));
      // }
    }
  };

  /* ============================================================ */
  /*                                                              */
  /*                Non-member function overloads                 */
  /*                                                              */
  /* ============================================================ */

  template <class T, class Alloc>
  bool operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
  template <class T, class Alloc>
  bool operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (!(lhs == rhs));
  }
  template <class T, class Alloc>
  bool operator< (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
  }
  template <class T, class Alloc>
  bool operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (!(lhs > rhs));
  }
  template <class T, class Alloc>
  bool operator> (const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (rhs < lhs);
  }
  template <class T, class Alloc>
  bool operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) {
    return (!(lhs < rhs));
  }

  template <class T, class Alloc>
  void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
    x.swap(y);
  }
}

#endif
