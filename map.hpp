#ifndef MAP_HPP_
# define MAP_HPP_

# include <functional>  // std::less
# include <memory>      // std::allocator
# include "utils/algorithm.hpp"
# include "utils/iterator.hpp"
# include "utils/rbtree.hpp"
# include "utils/utility.hpp"

namespace ft {
  template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
  class map {
    public:
    /* ============================================================ */
    /*                                                              */
    /*                         Member types                         */
    /*                                                              */
    /* ============================================================ */
    typedef Key                                                           key_type;
    typedef T                                                             mapped_type;
    typedef pair<const key_type, mapped_type>                             value_type;
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

    typedef typename rbtree<value_type, key_type, value_compare, allocator_type>::iterator           iterator;
    typedef typename rbtree<value_type, key_type, value_compare, allocator_type>::const_iterator  const_iterator;
    typedef ft::reverse_iterator<iterator>        reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;

    private:
    key_compare     _key_comp;
    value_compare   _value_comp;
    rbtree<value_type, key_type, value_compare, allocator_type>   _tree;

    public:
    /* ============================================================ */
    /*                                                              */
    /*                       Member functions                       */
    /*                                                              */
    /* ============================================================ */

    /* Constructor (1) */
    explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
      : _key_comp(comp), _value_comp(comp), _tree(_value_comp, alloc) {}
    /* Constructor (2) */
    template <class InputIterator>
    map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
      : _key_comp(comp), _value_comp(comp), _tree(_value_comp, alloc) {
        insert(first, last);
      }
    /* Constructor (3) */
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

    /* Access element */
    mapped_type& operator[] (const key_type& k) {
      pair<iterator, bool> p = insert(ft::make_pair(k, mapped_type()));
      return (p.first->second);
    }

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

    /* Insert element */
    pair<iterator, bool> insert(const value_type& val) {
      return (_tree.insert(val));
    }
    iterator insert(iterator position, const value_type& val) {
      return (_tree.insert(position, val));
    }
    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
      return (_tree.insert(first, last));
    }

    /* Erase element */
    void erase(iterator position) {
      _tree.erase(position);
    }
    size_type erase(const key_type& k) {
      return (_tree.erase(k));
    }
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

    /* Return key comparison object */
    key_compare key_comp() const {
      return (_key_comp);
    }

    /* Return value comparison object */
    value_compare value_comp() const {
      return (_value_comp);
    }

    /* ============================================================ */
    /*                          Operations                          */
    /* ============================================================ */

    /* Get iterator to element */
    iterator find(const key_type& k) {
      return (_tree.find(k));
    }
    const_iterator find(const key_type& k) const {
      return (_tree.find(k));
    }

    /* Count elements with a specific key */
    size_type count(const key_type& k) const {
      return (!(find(k) == end()));
    }

    /* Return iterator to lower bound */
    iterator lower_bound(const key_type& k) {
      return (_tree.lower_bound(k));
    }
    const_iterator lower_bound(const key_type& k) const {
      return (_tree.lower_bound(k));
    }

    /* Return iteartor to upper bound */
    iterator upper_bound(const key_type& k) {
      return (_tree.upper_bound(k));
    }
    const_iterator upper_bound(const key_type& k) const {
      return (_tree.upper_bound(k));
    }

    /* Get range of equal element */
    pair<const_iterator, const_iterator> equal_range(const key_type& k) const {
      return (_tree.equal_range(k));
    }
    pair<iterator, iterator> equal_range(const key_type& k) {
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
    return (lhs.size() == rhs.size() && equal(lhs.begin(), lhs.end(), rhs.begin()));
  }
  template <class Key, class T, class Compare, class Alloc>
  bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
    return (!(lhs == rhs));
  }
  template <class Key, class T, class Compare, class Alloc>
  bool operator< (const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) {
    return (lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
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
