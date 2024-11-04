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
#include <iomanip>
#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

struct Date {
    int year;
    int month;
    int day;
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

    void printEmployeeData() {
        int labelWidth = 0;
        for (const auto &label : {"ID", "Nombre", "Salario", "Fecha de ingreso",
                                  "Cumpleaños", "Fecha de última promoción"}) {
            labelWidth =
                max(labelWidth, static_cast<int>(string(label).length()));
        }
        labelWidth += 3;

        cout << "=============================" << endl;
        cout << "      Datos del Empleado    " << endl;
        cout << "=============================" << endl;

        // Print labels without setw
        cout << left << setw(labelWidth) << "ID:";
        cout << this->id << endl;

        cout << left << setw(labelWidth) << "Nombre:";
        cout << this->name << endl;

        cout << left << setw(labelWidth) << "Salario:";
        cout << this->salary << endl;

        cout << left << setw(labelWidth) << "Fecha de ingreso:";
        cout << this->enter_date.day << "/" << this->enter_date.month << "/"
             << this->enter_date.year << endl;

        cout << left << setw(labelWidth) << "Cumpleaños:" << " ";
        cout << this->birthday.day << "/" << this->birthday.month << "/"
             << this->birthday.year << endl;

        cout << left << setw(labelWidth)
             << "Fecha de última promoción:" << "  ";
        cout << this->last_promotion_date.day << "/"
             << this->last_promotion_date.month << "/"
             << this->last_promotion_date.year << endl;

        cout << "=============================" << endl;
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
    NodeType *removeNode(NodeType *&first_node_ptr, T nodeCheck) {
        NodeType *previous_ptr = nullptr;
        NodeType *current_ptr = first_node_ptr;
        NodeType *removed_head = nullptr;
        NodeType *removed_tail = nullptr;

        while (current_ptr != nullptr) {
            if (nodeCheck(current_ptr)) {
                NodeType *node_to_delete = current_ptr;
                if (current_ptr == first_node_ptr) {
                    first_node_ptr = current_ptr->next;
                    current_ptr = first_node_ptr;
                } else {
                    previous_ptr->next = current_ptr->next;
                    current_ptr = current_ptr->next;
                }
                if (removed_head == nullptr) {
                    removed_head = node_to_delete;
                    removed_tail = node_to_delete;
                } else {
                    removed_tail->next = node_to_delete;
                    removed_tail = node_to_delete;
                }
                node_to_delete->next = nullptr;
            } else {
                previous_ptr = current_ptr;
                current_ptr = current_ptr->next;
            }
        }

        return removed_head;
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
            current_ptr->printEmployeeData();
            cout << endl;
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

inline bool isDateGreater(const Date &date1, const Date &date2) {
    if (date1.year > date2.year)
        return true;
    if (date1.year == date2.year && date1.month > date2.month)
        return true;
    if (date1.year == date2.year && date1.month == date2.month &&
        date1.day > date2.day)
        return true;
    return false;
}

inline pair<Date, bool> askValidDate() {
    string date_str;
    cin >> date_str;

    Date date;

    if (sscanf(date_str.c_str(), "%d-%d-%d", &date.year, &date.month,
               &date.day) == 3) {
        if (date.year <= 2024 && date.month >= 1 && date.month <= 12 &&
            date.day >= 1 && date.day <= 31) {
            return {date, true};
        } else {
            cout << "Fecha fuera de rango. El año no debe ser mayor a 2024, "
                    "el "
                    "mes debe estar entre 1 y 12, y el día debe estar entre 1 "
                    "y 31."
                 << endl;
            return {Date(), false};
        }
    } else {
        cout << "Formato de fecha inválido. Por favor, use el formato "
                "YYYY-MM-DD."
             << endl;
        return {Date(), false};
    }
}

// check if id exist in the list using a searchEmployee
// function defined in LinkedListActions class
bool checkIdExist(int id, EmployeeNode *employee_list,
                  LinkedListActions<EmployeeNode> &employee_actions) {
    return employee_actions.searchNodes(
               employee_list,
               [id](EmployeeNode *node) { return node->id == id; }) != nullptr;
}

// function to add a new employee to the list
void addEmployee(EmployeeNode *&employee_list,
                 LinkedListActions<EmployeeNode> &employee_actions) {
    int id;
    string name;
    int salary;
    Date enter_date;
    Date birthday;
    Date last_promotion_date;

    clearScreen();

    cout << "Introduzca los datos del empleado:" << endl;
    cout << "----------------------------------" << endl;
    cout << endl;

    cout << "ID: ";
    auto [id_input, id_valid] =
        askValidInput<int>([](const int &id) { return id > 0; });
    while (!id_valid ||
           checkIdExist(id_input, employee_list, employee_actions)) {
        cout << "ID inválido. Por favor, introduzca un ID válido: ";
        tie(id_input, id_valid) =
            askValidInput<int>([](const int &id) { return id > 0; });
    }
    id = id_input;

    cout << "Nombre: ";
    auto [name_input, name_valid] =
        askValidInput<string>([](const string &name) { return !name.empty(); });
    while (!name_valid) {
        cout << "Nombre inválido. Por favor, introduzca un nombre válido: ";
        tie(name_input, name_valid) = askValidInput<string>(
            [](const string &name) { return !name.empty(); });
    }
    name = name_input;

    cout << "Salario: ";
    auto [salary_input, salary_valid] =
        askValidInput<int>([](const int &salary) { return salary > 0; });
    while (!salary_valid) {
        cout << "Salario inválido. Por favor, introduzca un salario válido: ";
        tie(salary_input, salary_valid) =
            askValidInput<int>([](const int &salary) { return salary > 0; });
    }
    salary = salary_input;

    cout << "Fecha de ingreso (YYYY-MM-DD): ";
    auto [enter_date_input, enter_date_valid] = askValidDate();
    while (!enter_date_valid) {
        cout << "Fecha inválida. Por favor, introduzca una fecha válida: ";
        tie(enter_date_input, enter_date_valid) = askValidDate();
    }
    enter_date = enter_date_input;

    cout << "Cumpleaños (YYYY-MM-DD): ";
    auto [birthday_input, birthday_valid] = askValidDate();
    birthday_input.year += 16;
    while (!birthday_valid || isDateGreater(birthday_input, enter_date)) {
        if (!birthday_valid) {
            cout << "Fecha inválida. Por favor, introduzca una fecha válida: ";
        } else {
            cout << "Debe ser mayor de 16 años";
        }
        tie(birthday_input, birthday_valid) = askValidDate();
        birthday_input.year += 16;
    }
    birthday_input.year -= 16;
    birthday = birthday_input;

    cout << "Fecha de última promoción (YYYY-MM-DD): ";
    auto [last_promotion_date_input, last_promotion_date_valid] =
        askValidDate();
    while (!last_promotion_date_valid ||
           !isDateGreater(last_promotion_date_input, enter_date)) {
        if (!last_promotion_date_valid) {
            cout << "Fecha inválida. Por favor, introduzca una fecha válida: ";
        } else {
            cout << "La fecha de última promoción debe ser posterior a la "
                    "fecha de ingreso. ";
        }
        tie(last_promotion_date_input, last_promotion_date_valid) =
            askValidDate();
    }
    last_promotion_date = last_promotion_date_input;

    EmployeeNode *new_employee = new EmployeeNode(
        id, name, salary, enter_date, birthday, last_promotion_date);

    employee_actions.insertNode(employee_list, new_employee);

    cout << "Empleado agregado exitosamente." << endl;
    pauseScreen();
}

// remove employee function
void removeEmployee(EmployeeNode *&employee_list,
                    LinkedListActions<EmployeeNode> &employee_actions) {
    if (employee_list == nullptr) {
        cout << "La lista de empleados está vacía." << endl;
        pauseScreen();
        return;
    }

    int option = 0;
    clearScreen();

    cout << "Eliminar empleado por:" << endl;
    cout << "1. ID" << endl;
    cout << "2. Salario" << endl;
    cout << "\nSeleccione una opción: ";

    auto [option_input, option_valid] = askValidInput<int>(
        [](const int &option) { return option == 1 || option == 2; });
    while (!option_valid) {
        cout << "Opción inválida. Por favor, seleccione una opción válida: ";
        tie(option_input, option_valid) = askValidInput<int>(
            [](const int &option) { return option == 1 || option == 2; });
    }
    option = option_input;

    if (option == 1) {
        EmployeeNode *removed_nodes = nullptr;
        int id;

        cout << "Introduzca el ID del empleado a eliminar: ";
        auto [id_input, id_valid] =
            askValidInput<int>([](const int &id) { return id > 0; });

        while (!id_valid) {
            cout << "ID inválido. Por favor, introduzca un ID válido: ";
            tie(id_input, id_valid) =
                askValidInput<int>([](const int &id) { return id > 0; });
        }
        id = id_input;

        removed_nodes = employee_actions.removeNode(
            employee_list, [id](EmployeeNode *node) { return node->id == id; });
        if (removed_nodes != nullptr) {
            cout << "Empleado(s) eliminado(s):" << endl;
            employee_actions.printList(removed_nodes);
            cout << "Empleado con ID " << id << " eliminado." << endl;
        } else {
            cout << "Empleado con ID " << id << " no encontrado." << endl;
        }
    } else if (option == 2) {
        EmployeeNode *removed_nodes = nullptr;
        int salary;

        cout << "Introduzca el salario del empleado a eliminar: ";
        auto [salary_input, salary_valid] =
            askValidInput<int>([](const int &salary) { return salary > 0; });

        while (!salary_valid) {
            cout << "Salario inválido. Por favor, introduzca un salario "
                    "válido: ";
            tie(salary_input, salary_valid) = askValidInput<int>(
                [](const int &salary) { return salary > 0; });
        }
        salary = salary_input;

        removed_nodes = employee_actions.removeNode(
            employee_list,
            [salary](EmployeeNode *node) { return node->salary == salary; });
        if (removed_nodes != nullptr) {
            cout << "Empleado(s) eliminado(s):" << endl;
            employee_actions.printList(removed_nodes);
            cout << "Empleado con salario " << salary << " eliminado." << endl;
        } else {
            cout << "Empleado con salario " << salary << " no encontrado."
                 << endl;
        }
    } else {
        cout << "Opción inválida." << endl;
    }

    pauseScreen();
}

// search employee function
void searchEmployee(EmployeeNode *employee_list,
                    LinkedListActions<EmployeeNode> &employee_actions) {
    if (employee_list == nullptr) {
        cout << "La lista de empleados está vacía." << endl;
        pauseScreen();
        return;
    }

    int option = 0;
    clearScreen();

    cout << "Buscar empleado por:" << endl;
    cout << "1. Salario" << endl;
    cout << "2. ID" << endl;
    cout << "3. Rango de fechas de entrada a la empresa" << endl;
    cout << "4. Rango de fechas de cumpleaños" << endl;
    cout << "5. Rango de fechas de última promoción" << endl;
    cout << "0. Cancelar" << endl;
    cout << "\nSeleccione una opción: ";

    auto [option_input, option_valid] = askValidInput<int>(
        [](const int &option) { return 0 <= option && option <= 5; });
    while (!option_valid) {
        cout << "Opción inválida. Por favor, seleccione una opción válida: ";
        tie(option_input, option_valid) = askValidInput<int>(
            [](const int &option) { return 0 <= option && option <= 5; });
    }
    option = option_input;

    if (option == 1) {
        int salary;

        cout << "Introduzca el salario a buscar: ";
        auto [salary_input, salary_valid] =
            askValidInput<int>([](const int &salary) { return salary > 0; });

        while (!salary_valid) {
            cout << "Salario inválido. Por favor, introduzca un salario "
                    "válido: ";
            tie(salary_input, salary_valid) = askValidInput<int>(
                [](const int &salary) { return salary > 0; });
        }
        salary = salary_input;

        EmployeeNode *search_result = employee_actions.searchNodes(
            employee_list,
            [salary](EmployeeNode *node) { return node->salary == salary; });

        clearScreen();

        if (search_result != nullptr) {
            cout << "Empleado(s) encontrado(s):" << endl;
            employee_actions.printList(search_result);
        } else {
            cout << "Empleado con salario " << salary << " no encontrado."
                 << endl;
        }

        pauseScreen();
    } else if (option == 2) {
        int id;

        cout << "Introduzca el ID a buscar: ";
        auto [id_input, id_valid] =
            askValidInput<int>([](const int &id) { return id > 0; });

        while (!id_valid) {
            cout << "ID inválido. Por favor, introduzca un ID válido: ";
            tie(id_input, id_valid) =
                askValidInput<int>([](const int &id) { return id > 0; });
        }
        id = id_input;

        EmployeeNode *search_result = employee_actions.searchNodes(
            employee_list, [id](EmployeeNode *node) { return node->id == id; });

        clearScreen();

        if (search_result != nullptr) {
            cout << "Empleado(s) encontrado(s):" << endl;
            employee_actions.printList(search_result);
        } else {
            cout << "Empleado con ID " << id << " no encontrado." << endl;
        }

        pauseScreen();
    } else if (option == 3) {
        Date start_date;
        Date end_date;

        cout << "Introduzca el rango de fechas de entrada a la empresa:"
             << endl;
        cout << "Fecha de inicio (YYYY-MM-DD): ";
        auto [start_date_input, start_date_valid] = askValidDate();
        while (!start_date_valid) {
            cout << "Fecha inválida. Por favor, introduzca una fecha válida: ";
            tie(start_date_input, start_date_valid) = askValidDate();
        }
        start_date = start_date_input;

        cout << "Fecha de fin (YYYY-MM-DD): ";
        auto [end_date_input, end_date_valid] = askValidDate();
        while (!end_date_valid || isDateGreater(start_date, end_date_input)) {
            if (!end_date_valid) {
                cout << "Fecha inválida. Por favor, introduzca una fecha "
                        "válida: ";
            } else {
                cout << "La fecha de fin debe ser posterior a la fecha de "
                        "inicio. ";
            }
            tie(end_date_input, end_date_valid) = askValidDate();
        }
        end_date = end_date_input;

        EmployeeNode *search_result = employee_actions.searchNodes(
            employee_list, [start_date, end_date](EmployeeNode *node) {
                return isDateGreater(node->enter_date, start_date) &&
                       isDateGreater(end_date, node->enter_date);
            });

        clearScreen();

        if (search_result != nullptr) {
            cout << "Empleado(s) encontrado(s):" << endl;
            employee_actions.printList(search_result);
        } else {
            cout << "Empleado(s) no encontrado(s)." << endl;
        }

        pauseScreen();
    } else if (option == 4) {
        Date start_date;
        Date end_date;

        cout << "Introduzca el rango de fechas de cumpleaños:" << endl;
        cout << "Fecha de inicio (YYYY-MM-DD): ";
        auto [start_date_input, start_date_valid] = askValidDate();
        while (!start_date_valid) {
            cout << "Fecha inválida. Por favor, introduzca una fecha válida: ";
            tie(start_date_input, start_date_valid) = askValidDate();
        }
        start_date = start_date_input;

        cout << "Fecha de fin (YYYY-MM-DD): ";
        auto [end_date_input, end_date_valid] = askValidDate();
        while (!end_date_valid || isDateGreater(start_date, end_date_input)) {
            if (!end_date_valid) {
                cout << "Fecha inválida. Por favor, introduzca una fecha "
                        "válida: ";
            } else {
                cout << "La fecha de fin debe ser posterior a la fecha de "
                        "inicio. ";
            }
            tie(end_date_input, end_date_valid) = askValidDate();
        }
        end_date = end_date_input;

        EmployeeNode *search_result = employee_actions.searchNodes(
            employee_list, [start_date, end_date](EmployeeNode *node) {
                return isDateGreater(node->birthday, start_date) &&
                       isDateGreater(end_date, node->birthday);
            });

        clearScreen();

        if (search_result != nullptr) {
            cout << "Empleado(s) encontrado(s):" << endl;
            employee_actions.printList(search_result);
        } else {
            cout << "Empleado(s) no encontrado(s)." << endl;
        }

        pauseScreen();
    } else if (option == 5) {
        Date start_date;
        Date end_date;

        cout << "Introduzca el rango de fechas de última promoción:" << endl;
        cout << "Fecha de inicio (YYYY-MM-DD): ";
        auto [start_date_input, start_date_valid] = askValidDate();
        while (!start_date_valid) {
            cout << "Fecha inválida. Por favor, introduzca una fecha válida: ";
            tie(start_date_input, start_date_valid) = askValidDate();
        }
        start_date = start_date_input;

        cout << "Fecha de fin (YYYY-MM-DD): ";
        auto [end_date_input, end_date_valid] = askValidDate();
        while (!end_date_valid || isDateGreater(start_date, end_date_input)) {
            if (!end_date_valid) {
                cout << "Fecha inválida. Por favor, introduzca una fecha "
                        "válida: ";
            } else {
                cout << "La fecha de fin debe ser posterior a la fecha de "
                        "inicio. ";
            }
            tie(end_date_input, end_date_valid) = askValidDate();
        }
        end_date = end_date_input;

        EmployeeNode *search_result = employee_actions.searchNodes(
            employee_list, [start_date, end_date](EmployeeNode *node) {
                return isDateGreater(node->last_promotion_date, start_date) &&
                       isDateGreater(end_date, node->last_promotion_date);
            });

        clearScreen();

        if (search_result != nullptr) {
            cout << "Empleado(s) encontrado(s):" << endl;
            employee_actions.printList(search_result);
        } else {
            cout << "Empleado(s) no encontrado(s)." << endl;
        }

        pauseScreen();
    } else if (option == 0) {
        return;
    } else {
        cout << "Opción inválida." << endl;
        pauseScreen();
    }
}

// viewList function
void viewList(EmployeeNode *employee_list,
              LinkedListActions<EmployeeNode> &employee_actions) {

    clearScreen();

    if (employee_list == nullptr) {
        cout << "No hay empleados en la lista." << endl;
        pauseScreen();
        return;
    }

    employee_actions.printList(employee_list);

    pauseScreen();
}

// menu with options for:
// - Add employee
// - Remove employee (by id or salary)
// - Search by salary, id, date range
// - View list
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    EmployeeNode *employee_list = nullptr;
    LinkedListActions<EmployeeNode> employee_actions;

    // define insert order of employees by salary, descending
    employee_actions.setInsertBehaviour([](EmployeeNode *previous_ptr,
                                           EmployeeNode *actual_ptr,
                                           EmployeeNode *add_ptr) {
        return add_ptr->salary > actual_ptr->salary;
    });

    // pre-add some employees
    employee_actions.insertNode(employee_list,
                                new EmployeeNode(24358902, "Juan Pérez", 1000,
                                                 {2019, 5, 15}, {2020, 3, 22},
                                                 {2020, 6, 10}));
    employee_actions.insertNode(employee_list,
                                new EmployeeNode(3124389, "María López", 1500,
                                                 {2018, 7, 20}, {1991, 8, 14},
                                                 {2019, 9, 25}));
    employee_actions.insertNode(employee_list,
                                new EmployeeNode(1253894, "Pedro Ramírez", 2000,
                                                 {2017, 11, 30}, {1952, 12, 5},
                                                 {2018, 12, 15}));

    string menu_header_msg = "Menú de opciones\n";
    string ask_option_msg = "\nIntroduzca la opción deseada: ";
    string menu_option_text = "1. Agregar empleado\n"
                              "2. Eliminar empleado (por ID o salario)\n"
                              "3. Buscar por salario, ID, rango de fechas\n"
                              "4. Ver lista\n";

    map<int, MenuOption> menu_options = {
        {1,
         {"1. Agregar empleado",
          [&employee_list, &employee_actions] {
              addEmployee(employee_list, employee_actions);
          }}},
        {2,
         {"2. Eliminar empleado (por ID o salario)",
          [&employee_list, &employee_actions] {
              removeEmployee(employee_list, employee_actions);
          }}},
        {3,
         {"3. Buscar por salario, ID, rango de fechas",
          [&employee_list, &employee_actions] {
              searchEmployee(employee_list, employee_actions);
          }}},
        {4,
         {"4. Ver lista",
          [&employee_list, &employee_actions] {
              viewList(employee_list, employee_actions);
          }}},
    };

    display_menu(menu_header_msg, menu_options, ask_option_msg);

    return 0;
}
