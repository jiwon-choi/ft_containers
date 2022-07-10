#ifndef MAP_HPP_
# define MAP_HPP_

# include <functional>  // std::less
# include <memory>      // std::allocator
# include "utils/algorithm.hpp"
# include "utils/iterator.hpp"
# include "utils/rbtree.hpp"
# include "utils/utility.hpp"

namespace ft {
  template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
  class map {
    public:
    /* ============================================================ */
    /*                                                              */
    /*                         Member types                         */
    /*                                                              */
    /* ============================================================ */
    typedef Key                                                           key_type;
    typedef T                                                             mapped_type;
    typedef ft::pair<const key_type, mapped_type>                         value_type;
    typedef Compare                                                       key_compare;
    typedef Alloc                                                         allocator_type;
    typedef typename allocator_type::template rebind<value_type>::other   type_allocator;
    typedef std::allocator_traits<type_allocator>                         type_traits;
    typedef typename type_traits::pointer                                 pointer;
    typedef typename type_traits::const_pointer                           const_pointer;
    typedef value_type&                                                   reference;
    typedef const value_type&                                             const_reference;
    typedef std::size_t                                                   size_type;
    typedef std::ptrdiff_t                                                difference_type;

    class value_compare : public std::binary_function<value_type, value_type, bool> {
      protected:
      key_compare comp;

      public:
      value_compare(key_compare c) : comp(c) {}
      ~value_compare() {}

      bool operator()(const value_type& x, const value_type& y) const {
        return (comp(x.first, y.first));
      }
      bool operator()(const value_type& x, const key_type& y) const {
        return (comp(x.first, y));
      }
      bool operator()(const key_type& x, const value_type& y) const {
        return (comp(x, y.first));
      }
    };

    typedef typename ft::rbtree<value_type, key_type, value_compare, allocator_type>::iterator        iterator;
    typedef typename ft::rbtree<value_type, key_type, value_compare, allocator_type>::const_iterator  const_iterator;
    typedef ft::reverse_iterator<iterator>        reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;

    private:
    key_compare     _key_comp;
    value_compare   _value_comp;
    ft::rbtree<value_type, key_type, value_compare, allocator_type>   _tree;

    public:
    /* ============================================================ */
    /*                                                              */
    /*                       Member functions                       */
    /*                                                              */
    /* ============================================================ */

    /* Constructor (1) empty */
    explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
      : _key_comp(comp), _value_comp(comp), _tree(_value_comp, alloc) {}
    /* Constructor (2) range */
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
      : _key_comp(comp), _value_comp(comp), _tree(_value_comp, alloc) {
        insert(first, last);
      }
    /* Constructor (3) copy */
    map(const map& x)
      : _key_comp(x._key_comp), _value_comp(x._value_comp), _tree(x._tree) {}

    /* Destructor */
    ~map() {}

    /* Copy container content */
    map& operator=(const map& x) {
      if (this != &x) {
        _key_comp = x._key_comp;
        _value_comp = x._value_comp;
        _tree = x._tree;
      }
      return (*this);
    }

    /* ============================================================ */
    /*                          Iterators                           */
    /* ============================================================ */

    /* Return iterator to beginning */
    iterator begin() {
      return (_tree.begin());
    }
    const_iterator begin() const {
      return (_tree.begin());
    }

    /* Return iterator to end */
    iterator end() {
      return (_tree.end());
    }
    const_iterator end() const {
      return (_tree.end());
    }

    /* Return reverse iterator to reverse beginning */
    reverse_iterator rbegin() {
      return (reverse_iterator(end()));
    }
    const_reverse_iterator rbegin() const {
      return (reverse_iterator(end()));
    }

    /* Return reverse iterator to reverse end */
    reverse_iterator rend() {
      return (reverse_iterator(begin()));
    }
    const_reverse_iterator rend() const {
      return (reverse_iterator(begin()));
    }

    /* ============================================================ */
    /*                           Capacity                           */
    /* ============================================================ */

    /* Test whether container is empty */
    bool empty() const {
      return (_tree.empty());
    }

    /* Return container size */
    size_type size() const {
      return (_tree.size());
    }

    /* Return maximum size */
    size_type max_size() const {
      return (_tree.max_size());
    }

    /* ============================================================ */
    /*                        Element access                        */
    /* ============================================================ */

    /*
    ** Access element
    ** k가 컨테이너에 있는 element의 키와 일치하면 mapped value에 대한 참조를 반환한다.
    ** k가 컨테이너에 있는 element의 키와 일치하지 않으면 해당 키가 있는 새 element를 삽입하고 mapped value에 대한 참조를 반환한다.
    ** value는 기본 생성자를 사용하여 구성되고, 새로 추가될 경우 컨테이너 사이즈는 1 증가한다.
    */
    mapped_type& operator[] (const key_type& k) {
      ft::pair<iterator, bool> p = insert(ft::make_pair(k, mapped_type()));
      return (p.first->second);
    }

    /*
    ** Access element
    ** k를 찾아 mapped value에 대한 참조를 반환한다.
    ** k가 컨테이너에 존재하지 않으면 out_of_range 예외를 throw 한다.
    */
    mapped_type& at(const key_type& k) {
      iterator it = find(k);
      if (it == end())
        throw std::out_of_range("ft::map::at");
      return (it->second);
    }
    const mapped_type& at(const key_type& k) const {
      const_iterator it = find(k);
      if (it == end())
        throw std::out_of_range("ft::map::at");
      return (it->second);
    }

    /* ============================================================ */
    /*                          Modifiers                           */
    /* ============================================================ */

    /*
    ** Insert element (1) single element
    ** pair를 반환하는데 first는 삽입한 element의 iterator이고,
    ** second는 bool이다(새로 삽입했다면 true, 이미 존재했다면 false).
    */
    ft::pair<iterator, bool> insert(const value_type& val) {
      return (_tree.insert(val));
    }
    /*
    ** Insert element (2) with hint
    ** 새로 삽입한 요소(이미 있었다면 해당 요소)를 가리키는 iterator를 반환한다.
    ** position이 hint인데, 새 삽입 element 앞에 올 element를 가리키는 경우 삽입하는 시간을 최적화한다.
    ** 하지만 hint는 hint일 뿐 그 자리에 강제로 삽입한다는 의미가 아니다.
    */
    iterator insert(iterator position, const value_type& val) {
      return (_tree.insert(position, val));
    }
    /* Insert element (3) range */
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
      return (_tree.insert(first, last));
    }

    /* Erase element (1) single element */
    void erase(iterator position) {
      _tree.erase(position);
    }
    /*
    ** Erase element (2)
    ** key 값에 해당하는 element를 모두 지우고 지운 element의 수를 반환한다.
    */
    size_type erase(const key_type& k) {
      return (_tree.erase(k));
    }
    /* Erase element (3) range of elements */
    void erase(iterator first, iterator last) {
      _tree.erase(first, last);
    }

    /* Swap content */
    void swap(map& x) {
      _tree.swap(x._tree);
    }

    /* Clear content */
    void clear() {
      _tree.clear();
    }

    /* ============================================================ */
    /*                          Observers                           */
    /* ============================================================ */

    /*
    ** Return key comparison object
    ** 컨테이너가 키를 비교하는데 사용하는 비교 객체를 반환한다.
    */
    key_compare key_comp() const {
      return (_key_comp);
    }

    /*
    ** Return value comparison object
    ** 두 element를 비교하는 데 사용하는 비교 객체를 반환한다.
    */
    value_compare value_comp() const {
      return (_value_comp);
    }

    /* ============================================================ */
    /*                          Operations                          */
    /* ============================================================ */

    /*
    ** Get iterator to element
    ** 컨테이너에서 k에 해당하는 키가 있는지 검색하고, 발견하면 해당 iterator를 반환한다.
    ** 검색에 실패했을 경우 end를 반환한다.
    */
    iterator find(const key_type& k) {
      return (_tree.find(k));
    }
    const_iterator find(const key_type& k) const {
      return (_tree.find(k));
    }

    /*
    ** Count elements with a specific key
    ** 컨테이너에서 k에 해당하는 키가 있는지 검색하고, 일치하는 항목의 수를 반환한다.
    ** map 컨테이너의 모든 element는 unique하기 때문에 1 또는 0만 반환된다.
    */
    size_type count(const key_type& k) const {
      return (!(find(k) == end()));
    }

    /*
    ** Return iterator to lower bound
    ** 키 값이 k와 같거나 k보다 큰 값 중 가장 작은 element의 iterator를 반환한다.
    */
    iterator lower_bound(const key_type& k) {
      return (_tree.lower_bound(k));
    }
    const_iterator lower_bound(const key_type& k) const {
      return (_tree.lower_bound(k));
    }

    /*
    ** Return iteartor to upper bound
    ** 키 값이 k보다 큰 값 중 가장 작은 element의 iterator를 반환한다.
    */
    iterator upper_bound(const key_type& k) {
      return (_tree.upper_bound(k));
    }
    const_iterator upper_bound(const key_type& k) const {
      return (_tree.upper_bound(k));
    }

    /*
    ** Get range of equal element
    ** 키 값이 k인 모든 요소를 포함하는 범위를 반환한다.
    ** map 컨테이너의 모든 element는 unique하기 때문에 범위는 최대 1이다.
    ** 일치하는 항목이 없으면 반환된 범위의 길이는 0이고,
    ** 두 반복자는 key_compare에 따라 k 다음에 오는 요소를 가리킨다.
    */
    ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
      return (_tree.equal_range(k));
    }
    ft::pair<iterator, iterator> equal_range(const key_type& k) {
      return (_tree.equal_range(k));
    }

    /* ============================================================ */
    /*                          Allocator                           */
    /* ============================================================ */

    /* Get allocator */
    allocator_type get_allocator() const {
      return (_tree.get_allocator());
    }
  };

  template <class Key, class T, class Compare, class Alloc>
  bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
    return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
  template <class Key, class T, class Compare, class Alloc>
  bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
    return (!(lhs == rhs));
  }
  template <class Key, class T, class Compare, class Alloc>
  bool operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
  }
  template <class Key, class T, class Compare, class Alloc>
  bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
    return (!(rhs < lhs));
  }
  template <class Key, class T, class Compare, class Alloc>
  bool operator> (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
    return (rhs < lhs);
  }
  template <class Key, class T, class Compare, class Alloc>
  bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
    return (!(lhs < rhs));
  }

  template <class Key, class T, class Compare, class Alloc>
  void swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs) {
    lhs.swap(rhs);
  }
}

#endif
