#include <iostream>
#include <vector>
#include "vector.hpp"
#include "random_access_iterator.hpp"

int main(void) {
  // constructors used in the same order as described above:
  ft::vector<int> vec1;                                // empty vector of ints
  // ft::vector<int> second (4,100);                       // four ints with value 100
  // ft::vector<int> third (second.begin(),second.end());  // iterating through second
  // ft::vector<int> fourth (third);                       // a copy of third

  // // the iterator constructor can also be used to construct from arrays:
  // int myints[] = {16,2,77,29};
  // ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  // std::cout << "The contents of fifth are:";
  // for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
  //   std::cout << ' ' << *it;
  // std::cout << '\n';


  // ft::reverse_iterator<ft::random_access_iterator<int> > rit;
  // std::cout << "[reverse iterator]" << '\n';
  // for (rit = vec1.rbegin(); rit != vec1.rend(); rit++)
  //   std::cout << *rit << ' ';
  // std::cout << "\n\n";

  std::vector<int> stdvec;
  for (int i = 0; i < 4; i++)
    stdvec.push_back(i + 300);
  stdvec.pop_back();
  for (std::vector<int>::iterator it = stdvec.begin(); it != stdvec.end(); it++)
    std::cout << *it << ' ';
  std::cout << "\n" << *stdvec.begin() << " " << *stdvec.end() << "\n\n";
  
  

  for (int i = 0; i < 4; i++)
    vec1.push_back(i + 100);

  // vec1.resize(9, 555);

  std::cout << "[operator[]]" << '\n';
  for (size_t i = 0; i < vec1.size(); i++)
    std::cout << vec1[i] << ' ';
  std::cout << "\n\n";


  std::cout << "    size : " << vec1.size() << "\n"
            << "capacity : " << vec1.capacity() << "\n\n";

  // vec1.reserve(vec1.size() + 1);

  std::cout << "    size : " << vec1.size() << "\n"
            << "capacity : " << vec1.capacity() << "\n\n";

  vec1.insert(vec1.begin() + 3, 9999);
  // vec1.insert(vec1.begin() + 3, 9999);
  // vec1.insert(vec1.begin() + 3, 9999);
  // vec1.insert(vec1.begin() + 3, 9999);

  // vec1.insert(vec1.begin() + 3, 9999);

  ft::vector<int>::iterator it;
  std::cout << "[iterator]" << '\n';
  for (it = vec1.begin(); it != vec1.end(); it++)
    std::cout << *it << ' ';
  std::cout << "\n\n";


  std::cout << "    size : " << vec1.size() << '\n'
            << "capacity : " << vec1.capacity() << '\n'
            // << "   empty : " << vec1.empty() << '\n'
            // << "max size : " << vec1.max_size() << '\n'
            << '\n'
            << "   front : " << vec1.front() << '\n'
            << "    back : " << vec1.back() << '\n'
            << "   begin : " << *vec1.begin() << '\n'
            << "test end : " << *(vec1.end() - 1) << '\n'
            << "     end : " << *vec1.end() << '\n';

  return (0);
}