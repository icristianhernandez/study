#include <functional>
#include <iostream>

using namespace std;

template <typename T> class DoublyLinkedList {
  private:
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    Node *head;
    Node *tail;
    int size;
    function<bool(T, T)> insertLogic;
    function<void(const T &)> nodePrinter;

  public:
    DoublyLinkedList();
    ~DoublyLinkedList();
    void setInsertLogic(function<bool(T, T)> predicate);
    void insert(T data);
    void setNodePrinter(function<void(const T &)> printer);
    DoublyLinkedList<T> remove(function<bool(T)> predicate);
    DoublyLinkedList<T> search(function<bool(T)> predicate);
    void print();
    int getSize();
    bool isEmpty();
    void clear();
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList()
    : head(nullptr), tail(nullptr), size(0) {
    setInsertLogic([](T, T) { return false; });
}

template <typename T> DoublyLinkedList<T>::~DoublyLinkedList() { clear(); }

template <typename T>
void DoublyLinkedList<T>::setInsertLogic(function<bool(T, T)> predicate) {
    insertLogic = predicate;
}

template <typename T>
void DoublyLinkedList<T>::setNodePrinter(function<void(const T &)> printer) {
    nodePrinter = printer;
}

template <typename T> void DoublyLinkedList<T>::insert(T data) {
    Node *newNode = new Node{data, nullptr, nullptr};

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        Node *current = head;
        bool inserted = false;
        while (current) {
            if (insertLogic(current->data, data)) {
                newNode->next = current;
                newNode->prev = current->prev;
                if (current->prev) {
                    current->prev->next = newNode;
                } else {
                    head = newNode;
                }
                current->prev = newNode;
                inserted = true;
                break;
            }
            current = current->next;
        }
        if (!inserted) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    ++size;
}

template <typename T>
DoublyLinkedList<T> DoublyLinkedList<T>::remove(function<bool(T)> predicate) {
    DoublyLinkedList<T> removed;
    Node *current = head;
    while (current) {
        Node *next = current->next;
        if (predicate(current->data)) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            current->next = current->prev = nullptr;
            removed.insert(current->data);
            delete current;
            --size;
        }
        current = next;
    }

    removed.setInsertLogic(insertLogic);
    removed.setNodePrinter(nodePrinter);
    return removed;
}

template <typename T>
DoublyLinkedList<T> DoublyLinkedList<T>::search(function<bool(T)> predicate) {
    DoublyLinkedList<T> found;
    Node *current = head;

    while (current) {
        if (predicate(current->data)) {
            found.insert(current->data);
        }
        current = current->next;
    }

    found.setInsertLogic(insertLogic);
    found.setNodePrinter(nodePrinter);
    return found;
}

template <typename T> void DoublyLinkedList<T>::print() {
    if (isEmpty()) {
        cout << "Empty list" << endl;
        return;
    }

    // if nodePrinter is not set, not print anything
    if (!nodePrinter) {
        return;
    }

    Node *current = head;
    while (current) {
        nodePrinter(current->data);

        current = current->next;
    }
}

template <typename T> int DoublyLinkedList<T>::getSize() { return size; }

template <typename T> bool DoublyLinkedList<T>::isEmpty() { return size == 0; }

template <typename T> void DoublyLinkedList<T>::clear() {
    Node *current = head;
    while (current) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}
