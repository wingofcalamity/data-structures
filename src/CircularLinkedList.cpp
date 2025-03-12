#include "CircularLinkedList.hpp"

int main() {
  CircularLinkedList<int> cll;

  cll.append(1);
  cll.append(2);
  cll.prepend(3);
  cll.insertAt(2,66);
  cll.status();
  
  return EXIT_SUCCESS;

}