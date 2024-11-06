#include "ConsoleUtils.h"
#include "DoublyLinkedList.h"
#include <algorithm>
#include <iomanip>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <cstring>

struct ContactData {
    string name;
    string phone;
};

void contactDataPrinter(const ContactData &contact) {
    int labelWidth = 0;
    for (const auto &label : {"Nombre", "Teléfono"}) {
        labelWidth = max(labelWidth, static_cast<int>(string(label).length()));
    }
    labelWidth += 3;

    displayColoredText("=============================\n", 4);
    displayColoredText("      Datos del Contacto     \n", 4);
    displayColoredText("=============================\n", 4);

    cout << left << setw(labelWidth) << "Nombre:";
    cout << contact.name << endl;

    cout << left << setw(labelWidth) << "Teléfono:";
    cout << contact.phone << endl;

    cout << endl;
}

void addContact(DoublyLinkedList<ContactData> &contacts) {
    string name, phone = "";

    clearConsole();
    cout << "Introduzca los datos del contacto:" << endl;
    cout << "----------------------------------" << endl;
    cout << endl;
    cout << "Nombre: ";
    name = promptValidInput<string>(
        "Nombre inválido o ya existe. Por favor, introduzca un nombre válido y "
        "único: ",
        [&contacts](const string &inputName) {
            bool not_empty_name = !inputName.empty();
            bool not_repeated_name =
                contacts
                    .search([&inputName](const ContactData &contact) {
                        return contact.name == inputName;
                    })
                    .isEmpty();

            return not_empty_name && not_repeated_name;
            return not_repeated_name;
        });

    cout << "Teléfono: ";
    phone = promptValidInput<string>(
        "Teléfono inválido o ya existe. Por favor, introduzca un teléfono "
        "válido y único: ",
        [&contacts](const string &inputPhone) {
            bool all_digits =
                all_of(inputPhone.begin(), inputPhone.end(), ::isdigit);
            bool not_repeated_phone =
                contacts
                    .search([&inputPhone](const ContactData &contact) {
                        return contact.phone == inputPhone;
                    })
                    .isEmpty();

            return all_digits && not_repeated_phone;
        });

    ContactData new_contact = {name, phone};

    contacts.insert(new_contact);
    clearConsole();
    displayColoredText("Contacto añadido exitosamente.\n", 2);
    contactDataPrinter(new_contact);

    pauseConsole();
}

bool containSubstring(const string &str, const string &substr) {
    if (substr.empty())
        return false;

    return str.find(substr) != string::npos;
}

void searchByName(DoublyLinkedList<ContactData> &contacts) {
    clearConsole();

    string name;
    cout << "Introduzca el nombre a buscar: ";
    name = promptValidInput<string>(
        "Introduzca el nombre a buscar: ",
        [](const string &inputName) { return !inputName.empty(); });
    auto results = contacts.search([&name](const ContactData &contact) {
        return containSubstring(contact.name, name);
    });

    clearConsole();

    if (results.isEmpty()) {
        cout << "No se encontraron contactos con el nombre proporcionado."
             << endl;
    } else {
        results.print();
    }

    pauseConsole();
}

void searchByPhone(DoublyLinkedList<ContactData> &contacts) {
    clearConsole();

    string phone;
    cout << "Introduzca el teléfono a buscar: ";
    phone = promptValidInput<string>(
        "Teléfono inválido. Por favor, introduzca un teléfono válido: ",
        [](const string &inputPhone) {
            return !inputPhone.empty() &&
                   all_of(inputPhone.begin(), inputPhone.end(), ::isdigit);
        });
    auto results = contacts.search([&phone](const ContactData &contact) {
        return containSubstring(contact.phone, phone);
    });

    clearConsole();

    if (results.isEmpty()) {
        cout << "No se encontraron contactos con el teléfono proporcionado."
             << endl;
    } else {
        results.print();
    }

    pauseConsole();
}

void filter(DoublyLinkedList<ContactData> &contacts) {
    vector<MenuOption> search_options = {
        {"1", "Buscar por Nombre", [&contacts]() { searchByName(contacts); }},
        {"2", "Buscar por Teléfono",
         [&contacts]() { searchByPhone(contacts); }},
    };
    string menu_header_msg = "Buscar Contacto por:";
    string ask_option_msg = "\nSeleccione una opción: ";
    string invalid_input_msg = "\nOpción inválida. Intente de nuevo: ";
    displayUserMenu(search_options, menu_header_msg, ask_option_msg,
                    invalid_input_msg);
}

void viewList(DoublyLinkedList<ContactData> &contacts) {
    clearConsole();
    cout << "Contactos:" << endl << endl;
    contacts.print();
    pauseConsole();
}

void removeContact(DoublyLinkedList<ContactData> &contacts) {
    clearConsole();
    cout << "¿Desea eliminar por:" << endl;
    cout << "1. Nombre" << endl;
    cout << "2. Teléfono" << endl;
    cout << "Seleccione una opción (1 o 2): ";

    string option = promptValidInput<string>(
        "Opción inválida. Por favor, seleccione 1 o 2: ",
        [](const string &input) { return input == "1" || input == "2"; });

    string identifier;
    auto predicate = [&](const ContactData &contact) -> bool {
        if (option == "1") {
            return contact.name == identifier;
        } else {
            return contact.phone == identifier;
        }
    };

    if (option == "1") {
        cout << "Introduzca el nombre del contacto a eliminar: ";
    } else {
        cout << "Introduzca el teléfono del contacto a eliminar: ";
    }

    identifier = promptValidInput<string>(
        "Entrada inválida. Por favor, intente de nuevo: ",
        [&contacts, option](const string &input) {
            if (option == "1") {
                return !input.empty();
            } else {
                return !input.empty() &&
                       all_of(input.begin(), input.end(), ::isdigit);
            }
        });

    auto result = contacts.search(predicate);

    clearConsole();

    if (result.isEmpty()) {
        cout << "No se encontró un contacto con el "
             << (option == "1" ? "nombre" : "teléfono") << " proporcionado."
             << endl;
    } else {
        auto removed_contacts = contacts.remove(predicate);
        displayColoredText("Contacto eliminado exitosamente.\n", 1);
        removed_contacts.print();
    }

    pauseConsole();
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    DoublyLinkedList<ContactData> contacts;
    contacts.setNodePrinter(contactDataPrinter);
    contacts.setInsertLogic(
        [](const ContactData &data_to_check, const ContactData &new_data) {
            return data_to_check.name > new_data.name;
        });

    contacts.insert({"Juan Perez", "04241792430"});
    contacts.insert({"María Lopez", "04163403539"});
    contacts.insert({"Pedro Ramirez", "04161919084"});
    contacts.insert({"Ana Garcia", "04221919084"});
    contacts.insert({"Cristian Hernandez", "04241919084"});
    contacts.insert({"Cristian Alfredo", "02123031790"});
    contacts.insert({"Cristian", "04162345678"});

    vector<MenuOption> menu_options = {
        {"1", "Añadir contacto", [&contacts]() { addContact(contacts); }},
        {"2", "Buscar contacto", [&contacts]() { filter(contacts); }},
        {"3", "Eliminar contacto", [&contacts]() { removeContact(contacts); }},
        {"4", "Ver lista de contactos", [&contacts]() { viewList(contacts); }},
    };
    string menu_header_msg = "Menú de contactos\n";
    string ask_option_msg = "\nSeleccione una opción: ";
    string invalid_input_msg = "\nOpción inválida. Intente de nuevo: ";

    displayUserMenu(menu_options, menu_header_msg, ask_option_msg,
                    invalid_input_msg);
}
