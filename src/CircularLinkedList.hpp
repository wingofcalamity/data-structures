#include <iostream>
#include <iomanip>
#include <memory>

template <class T> class CircularLinkedList {
#pragma region PRIVATE
  private:

    size_t size;
    struct Node {
      T data;
      std::shared_ptr<Node> prev;
      std::shared_ptr<Node> next;
      Node(T value): data(value), prev(nullptr), next(nullptr) {}
    };
    
    using NodePtr = std::shared_ptr<Node>;

    NodePtr HEAD;
    NodePtr TAIL;
    NodePtr CURRENT;

    void init(std::shared_ptr<Node> newNode) {
      HEAD = newNode;
      TAIL = newNode;
      newNode->prev = newNode;
      newNode->next = newNode;
    }
    void insertBetween(NodePtr before, NodePtr insertee, NodePtr after) {
      before->next = insertee;
      after->prev = insertee;
      insertee->next = after;
      insertee->prev = before;
    }
    void removeBetween(NodePtr before, NodePtr remove, NodePtr after) {
      before->next = after;
      after->prev = before;
      free(remove);
    }
    NodePtr makeNode(T data) {
      return std::make_shared<Node>(data);
    }
#pragma endregion PRIVATE
#pragma region PUBLIC
  public:
  CircularLinkedList(): size(0), HEAD(nullptr), TAIL(nullptr), CURRENT(nullptr) {}
  ~CircularLinkedList() {}

    // ? Insert
    void prepend(T data) {
      NodePtr newNode = makeNode(data);
      if (HEAD == nullptr) {
        init(newNode);
      } else {
        insertBetween(TAIL, newNode, HEAD);
        HEAD = newNode;
      }
      size++;
    }
    void append(T data) {
      NodePtr newNode = makeNode(data);
      if (HEAD == nullptr) {
        init(newNode);
      } else {
        insertBetween(TAIL, newNode, HEAD);
        TAIL = newNode;
      }
      size++;
    }
    void insertAt(size_t position, T data) {
      if (HEAD == nullptr) {
        append(data);
        return;
      }
      if (position > size) {
        return;
      } 
      if (position == size) {
        append(data);
        return;
      }
      if (position == 0) {
        prepend(data);
        return;
      }
      auto currentNode = HEAD;
      for (size_t i = 0; i < position; i++)
      {
        currentNode = currentNode->next;
      }
      
      NodePtr newNode = makeNode(data);
      NodePtr prevNode = currentNode->prev;

      insertBetween(prevNode, newNode, currentNode);

      size++;
    }
    // ? Remove

    // ? Utils
    void printList() {
      if (HEAD == nullptr) {
        std::cout << "List is empty." << std::endl;
        return;
      }
      auto cn = HEAD;
      do {
        std::cout << cn->data << ",";
        cn = cn->next;
      } while (cn != HEAD);
      std::cout << std::endl;
    }
    void status() {
      if (HEAD == nullptr) {
        std::cout << "List is empty." << std::endl;
        return ;
      }
      std::cout <<
        " Value |     Address    |  Prev Address  |  Next Address  | Status \n" << 
        "-------+----------------+----------------+----------------+--------" << std::endl;
      auto currentNode = HEAD;
      do {
        std::cout << " " << std::setw(5)
          << currentNode->data << " | "
          << currentNode << " | "
          << currentNode->prev << " | "
          << currentNode->next << " | [";

        if(currentNode == HEAD) {
          std::cout << "H";
        } else {
          std::cout << "-";
        }

        if(currentNode == TAIL) {
          std::cout << "T";
        } else {
          std::cout << "-";
        }

        // check if prev node links back
        if(currentNode->prev->next == currentNode) {
          std::cout << "P";
        } else {
          std::cout << "-";
        }

        // check if next node links back
        if(currentNode->next->prev == currentNode) {
          std::cout << "N";
        } else {
          std::cout << "-";
        }

        std::cout << "]" << std::endl;

        currentNode = currentNode->next;
      } while (currentNode != HEAD);
      std::cout <<
        "-------+----------------+----------------+----------------+--------\n" <<
        "  HEAD | " << HEAD << "\n" <<
        "  TAIL | " << TAIL << "\n" << std::endl;
    }
};