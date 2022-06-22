#ifndef MAP_HPP_
# define MAP_HPP_

# include <functional> // std::less
# include <memory> // std::allocator
# include "utils/pair.hpp"

namespace ft {
  template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
  class map {
    public:
    /* ============================================================ */
    /*                                                              */
    /*                         Member types                         */
    /*                                                              */
    /* ============================================================ */
    typedef Key                                                   key_type;
    typedef T                                                     mapped_type;
    typedef pair<const key_type, mapped_type>                     value_type;
    typedef Compare                                               key_compare;
    typedef value_compare;
    typedef Alloc                                                 allocator_type;
    typedef typename allocator_type::reference                    reference;
    typedef typename allocator_type::const_reference              const_reference;
    typedef typename allocator_type::pointer                      pointer;
    typedef typename allocator_type::const_pointer                const_pointer;
    typedef ft::bidirectional_iterator<value_type>                iterator;
    typedef ft::bidirectional_iterator<const value_type>          const_iterator;
    typedef ft::reverse_iterator<iterator>                        reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                  const_reverse_iterator;
    typedef typename iterator_traits<iterator>::difference_type   difference_type;
    typedef typename allocator_type::size_type                    size_type;

    public:
    /* ============================================================ */
    /*                                                              */
    /*                       Member functions                       */
    /*                                                              */
    /* ============================================================ */

    /* Constructor (1) */
    /* Constructor (2) */
    /* Constructor (3) */

    /* Destructor */

    /* Copy container content */

    /* ============================================================ */
    /*                          Iterators                           */
    /* ============================================================ */

    /* Return iterator to beginning */

    /* Return iterator to end */

    /* Return reverse iterator to reverse beginning */

    /* Return reverse iterator to reverse end */

    /* ============================================================ */
    /*                           Capacity                           */
    /* ============================================================ */

    /* Test whether container is empty */

    /* Return container size */

    /* Return maximum size */

    /* ============================================================ */
    /*                        Element access                        */
    /* ============================================================ */

    /* Access element */

    /* ============================================================ */
    /*                          Modifiers                           */
    /* ============================================================ */

    /* Insert element */

    /* Erase element */

    /* Swap content */

    /* Clear content */

    /* ============================================================ */
    /*                          Observers                           */
    /* ============================================================ */

    /* Return key comparison object */

    /* Return value comparison object */

    /* ============================================================ */
    /*                          Operations                          */
    /* ============================================================ */

    /* Get iterator to element */

    /* Count elements with a specific key */

    /* Return iterator to lower bound */

    /* Return iteartor to upper bound */

    /* Get range of equal element */

    /* ============================================================ */
    /*                          Allocator                           */
    /* ============================================================ */

    /* Get allocator */
  };
}

#endif
