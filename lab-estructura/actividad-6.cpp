/*
Aplicación para usar listas enlazadas para almacenar y gestionar una lista de
empleados.

La aplicación debe tener las siguientes características:
    Un menú con las siguientes opciones:
        - Agregar empleado
        - Eliminar empleados (por id o salario)
        - Buscar por salario, id, rango de fechas
        - Ver lista
*/

#include "my-basic-utils-2.h"

using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

class EmployeeNode {
  public:
    int id;
    string name;
    int salary;
    Date enter_date;
    Date birthday;
    Date last_promotion_date;

    EmployeeNode *next;

    EmployeeNode(int id, string name, int salary, Date enter_date,
                 Date birthday, Date last_promotion_date) {
        this->id = id;
        this->name = name;
        this->salary = salary;
        this->enter_date = enter_date;
        this->birthday = birthday;
        this->last_promotion_date = last_promotion_date;

        this->next = nullptr;
    }

    void print() {
        cout << "ID: " << this->id << endl;
        cout << "Nombre: " << this->name << endl;
        cout << "Salario: " << this->salary << endl;
        cout << "Fecha de ingreso: " << this->enter_date.day << "/"
             << this->enter_date.month << "/" << this->enter_date.year << endl;
        cout << "Cumpleaños: " << this->birthday.day << "/"
             << this->birthday.month << "/" << this->birthday.year << endl;
        cout << "Fecha de última promoción: " << this->last_promotion_date.day
             << "/" << this->last_promotion_date.month << "/"
             << this->last_promotion_date.year << endl;
    }

  private:
};

template <typename NodeType> class LinkedListActions {
  public:
    // change insert behaviour
    void setInsertBehaviour(
        function<bool(NodeType *, NodeType *, NodeType *)> new_behaviour) {
        this->insert_behaviour = new_behaviour;
    }

    void insertNode(NodeType *&first_node_ptr, NodeType *add_node_ptr) {
        if (first_node_ptr == nullptr) {
            first_node_ptr = add_node_ptr;
            return;
        }

        NodeType *previous_ptr = nullptr;
        NodeType *current_ptr = first_node_ptr;

        while (
            current_ptr != nullptr &&
            !this->insert_behaviour(previous_ptr, current_ptr, add_node_ptr)) {
            previous_ptr = current_ptr;
            current_ptr = current_ptr->next;
        }

        if (previous_ptr == nullptr) {
            add_node_ptr->next = first_node_ptr;
            first_node_ptr = add_node_ptr;
        } else {
            previous_ptr->next = add_node_ptr;
            add_node_ptr->next = current_ptr;
        }
    }

    /*template <typename T>*/
    /*void removeNode(NodeType* first_node_ptr, T nodeCheck) {*/
    /*    NodeType* previous_ptr = first_node_ptr;*/
    /*    NodeType* current_ptr = first_node_ptr;*/
    /**/
    /*    while (current_ptr->next != nullptr) {*/
    /*        previous_ptr = current_ptr;*/
    /*        current_ptr = current_ptr->next;*/
    /**/
    /*        if (nodeCheck(current_ptr)) {*/
    /*            previous_ptr->next = current_ptr->next;*/
    /*            delete current_ptr;*/
    /*            return;*/
    /*        }*/
    /*    }*/
    /*}*/

    template <typename T>
    void removeNode(NodeType *first_node_ptr, T nodeCheck) {
        NodeType *previous_ptr = first_node_ptr;
        NodeType *current_ptr = first_node_ptr;

        while (current_ptr != nullptr) {
            if (nodeCheck(current_ptr)) {
                if (current_ptr == first_node_ptr) {
                    first_node_ptr = current_ptr->next;
                } else {
                    previous_ptr->next = current_ptr->next;
                }
                delete current_ptr;
                return;
            }
            previous_ptr = current_ptr;
            current_ptr = current_ptr->next;
        }
    }

    template <typename T>
    NodeType *searchNodes(NodeType *first_node_ptr, T nodeCheck) {
        NodeType *new_head = nullptr;
        NodeType *new_tail = nullptr;

        NodeType *current_ptr = first_node_ptr;

        while (current_ptr != nullptr) {
            if (nodeCheck(current_ptr)) {
                NodeType *new_node = new NodeType(*current_ptr);

                if (new_head == nullptr) {
                    new_head = new_node;
                    new_tail = new_node;
                } else {
                    new_tail->next = new_node;
                    new_tail = new_node;
                }
            }

            current_ptr = current_ptr->next;
        }

        if (new_tail != nullptr) {
            new_tail->next = nullptr;
        }

        return new_head;
    }

    void printList(NodeType *first_node_ptr) {
        NodeType *current_ptr = first_node_ptr;

        while (current_ptr != nullptr) {
            current_ptr->print();
            cout << endl;
            cout << "----------------" << endl;
            current_ptr = current_ptr->next;
            // debug
        }
    }

  private:
    // implement default insert lambda behaviour (always insert at the end of
    // list)
    function<bool(NodeType *, NodeType *, NodeType *)> insert_behaviour =
        [](NodeType *previous_ptr, NodeType *actual_ptr, NodeType *add_ptr) {
            if (actual_ptr->next == nullptr) {
                actual_ptr->next = add_ptr;
                return true;
            }

            return false;
        };
};

int main() {
    EmployeeNode *employee_list = nullptr;
    LinkedListActions<EmployeeNode> employee_actions;

    // explain what happening
    cout << "Se define el orden de inserción de los empleados por el salario, "
            "de manera descendente."
         << endl;

    cout << "Se insertan los empleados en el siguiente orden:" << endl;
    cout << "1. Pedro Almirante, salario: 1000" << endl;
    cout << "2. Jane Doe, salario: 2000" << endl;
    cout << "3. John Smith, salario: 1600" << endl;
    cout << "4. Jane Smith, salario: 2500" << endl;
    cout << endl << endl;

    employee_actions.setInsertBehaviour([](EmployeeNode *previous_ptr,
                                           EmployeeNode *actual_ptr,
                                           EmployeeNode *add_ptr) {
        return add_ptr->salary > actual_ptr->salary;
    });

    employee_actions.insertNode(employee_list,
                                new EmployeeNode(1, "Pedro Almirante", 1000,
                                                 {1, 1, 2000}, {1, 1, 1990},
                                                 {1, 1, 2005}));
    employee_actions.insertNode(
        employee_list, new EmployeeNode(2, "Jane Doe", 2000, {1, 1, 2000},
                                        {1, 1, 1990}, {1, 1, 2005}));
    employee_actions.insertNode(
        employee_list, new EmployeeNode(3, "John Smith", 1600, {1, 1, 2000},
                                        {1, 1, 1990}, {1, 1, 2005}));
    employee_actions.insertNode(
        employee_list, new EmployeeNode(4, "Jane Smith", 2500, {1, 1, 2000},
                                        {1, 1, 1990}, {1, 1, 2005}));

    employee_actions.printList(employee_list);

    pauseScreen();
    clearScreen();

    cout << "Se elimina el empleado con ID 2 (Jane Doe)" << endl;

    employee_actions.removeNode(
        employee_list, [](EmployeeNode *node) { return node->id == 2; });

    employee_actions.printList(employee_list);

    pauseScreen();
    clearScreen();

    cout << "Se busca a los empleados con salario mayor a 1500" << endl;

    EmployeeNode *search_result = employee_actions.searchNodes(
        employee_list, [](EmployeeNode *node) { return node->salary > 5000; });

    employee_actions.printList(search_result);

    pauseScreen();
    clearScreen();

    return 0;
}
