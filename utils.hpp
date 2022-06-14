#ifndef UTILS_HPP_
# define UTILS_HPP_

namespace ft {
  template <bool Cond, class T = void>
  struct enable_if {
    private:
    typedef type  T;
  };
}

#endif
