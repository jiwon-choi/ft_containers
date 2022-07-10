#ifndef TYPE_TRAITS_HPP_
# define TYPE_TRAITS_HPP_

/*
** is_integral (integral_constant, true_type, false_type)
** enable_if
*/

namespace ft {

  /* integral_constant */
  template <class T, T v>
  struct integral_constant {
    static const T                    value = v;
    typedef T                         value_type;
    typedef integral_constant<T, v>   type;
  };
  typedef integral_constant<bool, true>   true_type;
  typedef integral_constant<bool, false>  false_type;

  /* is_integral */
  template <class T> struct is_integral : public false_type {};

  template<> struct is_integral<bool> : public true_type {};
  template<> struct is_integral<char> : public true_type {};
  template<> struct is_integral<wchar_t> : public true_type {};
  template<> struct is_integral<signed char> : public true_type {};
  template<> struct is_integral<short int> : public true_type {};
  template<> struct is_integral<int> : public true_type {};
  template<> struct is_integral<long int> : public true_type {};
  template<> struct is_integral<unsigned char> : public true_type {};
  template<> struct is_integral<unsigned short int> : public true_type {};
  template<> struct is_integral<unsigned int> : public true_type {};
  template<> struct is_integral<unsigned long int> : public true_type {};

  template<> struct is_integral<const bool> : public true_type {};
  template<> struct is_integral<const char> : public true_type {};
  template<> struct is_integral<const wchar_t> : public true_type {};
  template<> struct is_integral<const signed char> : public true_type {};
  template<> struct is_integral<const short int> : public true_type {};
  template<> struct is_integral<const int> : public true_type {};
  template<> struct is_integral<const long int> : public true_type {};
  template<> struct is_integral<const unsigned char> : public true_type {};
  template<> struct is_integral<const unsigned short int> : public true_type {};
  template<> struct is_integral<const unsigned int> : public true_type {};
  template<> struct is_integral<const unsigned long int> : public true_type {};

  /* enable_if */
  template <bool Cond, class T = void> struct enable_if {};
  template <class T> struct enable_if<true, T> { typedef T type; };
}

#endif
