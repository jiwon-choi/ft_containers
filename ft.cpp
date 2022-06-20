#include <iostream>
#include <vector>
#include "vector.hpp"
#include "random_access_iterator.hpp"

int main(void) {
  ft::vector<int> vec;
  for (int i = 0; i < 5; i++)
    vec.push_back(i);

  for (ft::vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
    std::cout << *it << " ";

  std::cout << "\n\n";

  for (ft::vector<int>::reverse_iterator rit = vec.rbegin(); rit != vec.rend(); rit++)
    std::cout << *rit << " ";

  std::cout << "\n\n";

  std::cout << "    size : " << vec.size() << "\n"
            << "capacity : " << vec.capacity() << "\n"
            // << "   empty : " << vec.empty() << "\n"
            // << "max size : " << vec.max_size() << "\n"
            << "\n"
            << "    *rbegin : " << *vec.rbegin() << "\n"
            << "       back : " << vec.back() << "\n"
            << "*(rend + 1) : " << *(vec.rend() + 1) << "\n"
            << "      front : " << vec.front() << "\n"
            << "      *rend : " << *vec.rend() << "\n";

  return (0);
}
