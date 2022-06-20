#include <iostream>
#include <vector>
#include "vector.hpp"
#include "random_access_iterator.hpp"

int main(void) {
  /*
  // constructors used in the same order as described above:
  ft::vector<int> first;                                // empty vector of ints
  ft::vector<int> second (4,100);                       // four ints with value 100
  ft::vector<int> third (second.begin(),second.end());  // iterating through second
  ft::vector<int> fourth (third);                       // a copy of third

  // the iterator constructor can also be used to construct from arrays:
  int myints[] = {16,2,77,29};
  ft::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  std::cout << "The contents of fifth are:";
  for (ft::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << " " << *it;
  std::cout << "\n";
  std::cout << "capacity : " << fifth.capacity() << "\n";


  ft::vector<int>::reverse_iterator rit;
  std::cout << "[reverse iterator]" << "\n";
  for (rit = fifth.rbegin(); rit != fifth.rend(); rit++)
    std::cout << *rit << " ";
  std::cout << "\n\n";
  std::cout << "capacity : " << fifth.capacity() << "\n";


  for (int i = 0; i < 4; i++)
    fifth.push_back(i + 100);

  std::cout << "    size : " << fifth.size() << "\n"
            << "capacity : " << fifth.capacity() << "\n\n";

  fifth.insert(fifth.begin() + 3, 9999);
  fifth.insert(fifth.begin(), 4, 1010);
  fifth.insert(fifth.end(), fifth.begin(), fifth.end());

  ft::vector<int>::iterator it;
  std::cout << "[iterator]" << "\n";
  for (it = fifth.begin(); it != fifth.end(); it++)
    std::cout << *it << " ";
  std::cout << "\n\n";

  std::cout << "    size : " << fifth.size() << "\n"
            << "capacity : " << fifth.capacity() << "\n"
            // << "   empty : " << fifth.empty() << "\n"
            // << "max size : " << fifth.max_size() << "\n"
            << "\n"
            << "   front : " << fifth.front() << "\n"
            << "    back : " << fifth.back() << "\n"
            << "   begin : " << *fifth.begin() << "\n"
            << "test end : " << *(fifth.end() - 1) << "\n"
            << "     end : " << *fifth.end() << "\n";

  return (0);
  */


  const int size = 5;
  // std::vector<int> vec(size);
  // std::vector<int>::iterator it = vec.begin();
  // std::vector<int>::const_iterator ite = vec.begin();

  ft::vector<int> vct(size);
  ft::vector<int>::iterator it = vct.begin();
  ft::vector<int>::const_iterator ite = vct.begin();

  for (int i = 0; i < size; ++i)
    it[i] = (size - i) * 5;
  // prepost_incdec(vct);
  for (int i = 0; i < size; i++)
    std::cout << it[i] << " ";
  std::cout << "\n";

  it = it + 5;
  it = 1 + it;
  it = it - 4;
  std::cout << *(it += 2) << std::endl;
  std::cout << *(it -= 1) << std::endl;

  *(it -= 2) = 42;
  *(it += 2) = 21;

  // std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
  // std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

  // std::cout << "(it == const_it): " << (ite == it) << std::endl;
  // std::cout << "(const_ite - it): " << (ite - it) << std::endl;
  // std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

  // printSize(vct, true);
  return (0);
}