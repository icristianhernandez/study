/*
1. En una institución bancaria, se ha depositado un monto de capital m, por el
cual se recibe un interés X anual, el problema consiste en determinar el capital
que se obtendrá al cabo de n años. Escriba un programa recursivo que realice el
cálculo sabiendo que la fórmula es m (1+x %)^ n
*/

#include "ConsoleUtils.h"
#include <iostream>

double acumulatedInterestRate(double rate_percentage, int rate_steps) {
    if (rate_steps == 0) {
        return 1;
    }

    return rate_percentage *
           acumulatedInterestRate(rate_percentage, rate_steps - 1);
}

int main() {
    enableUTF8Output();

    double initial_capital, interest_rate, resulting_capital = 0;
    int years_to_interest = 0;
    double percentage_conversion = 1.00 / 100.00;
    double one_hundred_percentage = 1.00;

    clearConsole();
    cout << "Ingrese el capital inicial: ";
    initial_capital = promptValidInput<double>(
        "Número Inválido. Intente nuevamente: ",
        [](const double &input) { return input >= 0; });

    cout << "Ingrese la tasa de interes: ";
    interest_rate = one_hundred_percentage +
                    percentage_conversion *
                        promptValidInput<double>(
                            "Número Inválido. Intente nuevamente: ",
                            [](const double &input) { return input >= 0; });

    cout << "Ingrese la cantidad de años de aplicar interes: ";
    years_to_interest =
        promptValidInput<int>("Número Inválido. Intente nuevamente: ",
                              [](const int &input) { return input >= 0; });

    resulting_capital = initial_capital * acumulatedInterestRate(
                                              interest_rate, years_to_interest);

    cout << "\n\nEl capital resultante en " << years_to_interest
         << " años es de: " << resulting_capital;

    cout << "\n\n";
    pauseConsole();
    clearConsole();

    return 0;
}
