/*
Usted ha sido contratado por Dupont, líder mundial en fabricación de pintura
para el sector automotriz. Su Jefe, al revisar su curriculum, detecta que usted
tiene conocimientos de programación en C++ y le solicita que programe el sistema
de elaboración de las dos pinturas lideres para el mercado venezolano: Azul
Marino (AzMarino) y Azul Celeste (AzCeleste).

El programa debe cumplir con las siguientes premisas:

1ro.- El proceso arranca por comando del tablero "Botón de arranque de mezcla"
de Mezcla.

2do.- Cualquier bomba debe detenerse si: (1) el interruptor de flujo a la
entrada de la válvula de descarga pasa a "Alarma" (2) si la presión a la
descarga de la válvula pasa los 50 psi (3) La cantidad de pintura que debía
bombear ya se encuentra en el mezclador.

3ro.- Cuando una bomba se encuentra trabajando con con la válvula de succión y
descarga abierta su caudal de operación es de 100 lts/mi.

4to.- La presión a su descarga debe ubicarse alrededor de 33 psi si las válvulas
a la entrada y a la salida se encuentran abiertas. Si en ese instante se cierra
la válvula de descarga, el caudal inmediatamente cae a 0 (no pasa ninguna
cantidad de base de pintura al tanque de mezclado). adicionalmente, la presión
comienza a aumentar y al pasar los 50 psi la bomba se apaga por por sobre
presión. Si la válvula se abre la presión desciende hasta 20 psi en donde la
bomba arranca nuevamente y se estabiliza en 33 psi, al re-arrancar la bomba
vuelve a enviar los 100 lts/min.

5to.- Cuando una bomba se encuentra trabajando a su caudal máximo de 100 lts/min
y se activa el Switch de bajo Flujo (Alarma) la bomba debe apagarse de
inmediato. La presión a la descarga debe descender a 0 psi si la válvula se
encuentra abierta, si se encuentra cerrada la presión se mantiene en el último
valor. Al recuperar el Switch de bajo Flujo su condición de funcionamiento
(Normal), la bomba re-arrancará cuando la presión a la descarga baje por debajo
de 20 psi y durante ese tiempo la presión se incrementará la presión hasta su
nivel normal de operación alrededor de 33 psi.

6to.- Cuando se desea mezclar un tipo de pintura se debe garantizar que el
tanque de mezclado reciba la cantidad correcta de las bases necesarias para
obtener el color requerido. Por ejemplo si deseamos obtener Azul Marino
(AzMarino), según la tabla la relación 2 partes de negro por cada parte de Azul.
Como el Tanque destino tiene capacidad de 200 lts  pero los lotes se fabrican de
150 lts, por lo tanto debo prender la bomba P203 (Negro) el tiempo necesario
para bombear 100 lts de Negro (60 segundos) y la Bomba P202 (Azul) el tiempo
necesario para bombear 50 lts (30 segundos) de Azul. En pantalla debe mostrarse
la cantidad de segundos en los cuales cada bomba aporta base de pintura al
mezclador. No presentar estos contadores descalifican al programa entregado.

7mo.- Una vez bombeada la cantidad de base necesaria, se apagan las bombas de
base de pintura y se enciende el motor de mezclado por 30 segundos.

8vo.- Si durante el proceso de bombeo se detiene alguna bomba por algún
inconveniente, las otras bombas deben completar su proceso de bombeo. Si después
de un tiempo la bomba que falló se recupera ella debe completar el bombeo de la
base de pintura faltante para asegurar la mezcla. Solo cuando se haya terminado
de bombear los 150 litros y se hayan apagado las bombas de base de pintura
(P201, P202 y P203) es que se arrancara el motor de mezclado M401 por los 30
segundos estipulados.

9no.- El programa debe impedir que se arranque un nuevo lote de mezclado de
pintura si el lote en curso no se ha completado. En caso de intentar arrancar el
proceso nuevamente sin que el lote de preparación actual este completado, el
programa deberá presentar un mensaje en pantalla que informe que el ultimo
proceso de mezclado no se ha completado y la solicitud no será aceptada.

10mo.- Para que el proceso de mezcla pueda arrancar el interruptor de bajo nivel
del mezclador debe estar en alarma, de lo contrario el sistema no aceptara el
comando de arranque.

11vo.- Para que arranque la preparación de un nuevo lote de pintura es necesario
que el interruptor de bajo nivel del mezclador este activado y que el botón de
arranque se encuentre en OFF y pase a ON. Esta condición será verificada. Los
procesos de elaboración de lotes no puede arrancar de forma automática.

Condiciones del Profesor:
El Archivo de texto contendrá las Válvulas V201, V202, V203, V401, V402, V403,
el Color a mezclar (AzMarino / AzCeleste) y el comando de arranque de
fabricación (ON/OFF); si este comando pasa a ON y el mezclador esta vacío se
procederá a fabricar el lote de pintura definida según el Color a mezclar. Si
durante el proceso de fabricación de un lote se coloca en OFF el comando de
arranque, el proceso de fabricación en curso deberá completarse. Se debe indicar
tiempo de funcionamiento de cada bomba en segundos y los transmisores de niveles
de los tanques bases y el mezclador, de forma de verificar el funcionamiento del
programa. Usted debe simular todos los elementos del esquema y su
funcionamiento. Se debe monitorear todos los elementos  en pantalla. una vez
finalice el ciclo de mezclado el mezclador debe vaciarse a razón de 4% cada
segundo (25 seg totales) Condiciones Iniciales Los niveles de los tanques bases
son de 25% el nivel del mezclador en 0% Los interruptores de Flujo en Normal.
Todas las válvulas abiertas.
Las bombas apagadas.
Los transmisores de presión en 0 psi.
El comando de arranque de fabricación en OFF.
El selector de tipo de pintura en AzCeleste
 */

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <locale.h>
#include <map>
#include <math.h>
#include <string>
#include <vector>
#include <windows.h>

using namespace std;

// global initial values:
const bool Normal = true;
const bool Alerta = false;

int ONE_SECOND_IN_MS = 1000;
double INITIAL_TANK_CAPACITY = 20000.0;
double INITIAL_BASE_TANK_LEVELS = 25.0;
const double INITIAL_MIXER_TANK_LEVEL = 0.0;
const bool INITIAL_FLOW_TRANSMISSOR_STATE = Normal;
const bool INITIAL_PUMP_STATE = false;
const double INITIAL_PRESSURE_FOR_ALL = 0.0;
const string CONFIG_FILE_PATH = "./tercer_parcial_config.txt";

class ConfigManager {
  public:
    struct Config {
        map<string, string> valve_states;
        string color_a_mezclar;
        string arranque_de_fabricacion;
    };

    static string trim_whitespace(const string &s) {
        auto start = s.find_first_not_of(" \t\r\n");
        auto end = s.find_last_not_of(" \t\r\n");
        if (start == string::npos)
            return "";
        return s.substr(start, end - start + 1);
    }

    static void open_config_file(ifstream &file, const string &filename) {
        file.open(filename);
        if (!file.is_open()) {
            throw runtime_error("Error: Could not open config file: " +
                                filename);
        }
    }

    static bool parse_config_line(const string &line, string &key,
                                  string &value) {
        auto eq_pos = line.find('=');
        if (eq_pos == string::npos)
            return false;
        key = trim_whitespace(line.substr(0, eq_pos));
        value = trim_whitespace(line.substr(eq_pos + 1));
        return !(key.empty() || value.empty());
    }

    static void process_config_pair(Config &config, const string &key,
                                    const string &value) {
        static const vector<string> known_valve_keys = {"V201", "V202", "V203",
                                                        "V401", "V402", "V403"};
        const string K_COLOR = "COLOR_A_MEZCLAR";
        const string K_ARRANQUE = "ARRANQUE_DE_FABRICACIÓN";

        if (key == K_COLOR) {
            if (value != "AzMarino" && value != "AzCeleste") {
                throw runtime_error("Invalid value for COLOR_A_MEZCLAR: " +
                                    value);
            }
            config.color_a_mezclar = value;
        } else if (key == K_ARRANQUE) {
            if (value != "ON" && value != "OFF") {
                throw runtime_error(
                    "Invalid value for ARRANQUE_DE_FABRICACIÓN: " + value);
            }
            config.arranque_de_fabricacion = value;
        } else if (find(known_valve_keys.begin(), known_valve_keys.end(),
                        key) != known_valve_keys.end()) {
            if (value != "OPEN" && value != "CLOSED") {
                throw runtime_error("Invalid value for valve " + key + ": " +
                                    value);
            }
            config.valve_states[key] = value;
        } else {
            throw runtime_error("Invalid configuration key found: " + key);
        }
    }

    static Config read_config(const string &filename = CONFIG_FILE_PATH) {
        Config config;
        ifstream file;
        open_config_file(file, filename);
        string line, key, value;
        int line_number = 0;

        while (getline(file, line)) {
            line_number++;
            string trimmed = trim_whitespace(line);

            if (trimmed.empty() || trimmed[0] == '#')
                continue;

            if (!parse_config_line(trimmed, key, value)) {
                cerr << "Warning: Malformed config line " << line_number << ": "
                     << line << endl;
                continue;
            }
            process_config_pair(config, key, value);
        }

        if (config.color_a_mezclar.empty()) {
            throw runtime_error("Missing required setting: COLOR_A_MEZCLAR");
        }
        if (config.arranque_de_fabricacion.empty()) {
            throw runtime_error(
                "Missing required setting: ARRANQUE_DE_FABRICACIÓN");
        }
        const vector<string> required_valves = {"V201", "V202", "V203",
                                                "V401", "V402", "V403"};
        for (const auto &valve : required_valves) {
            if (config.valve_states.find(valve) == config.valve_states.end()) {
                throw runtime_error("Missing required valve setting: " + valve);
            }
        }
        return config;
    }

    static void
    repair_or_create_config_file(const string &filename = CONFIG_FILE_PATH) {
        const char *default_config =
            "# Válvulas de entrada \n"
            "# Valores Posibles: OPEN / CLOSE\n"
            "V201 = OPEN\n"
            "V202 = OPEN\n"
            "V203 = OPEN\n"
            "\n"
            "# Válvulas de salida\n"
            "# Valores Posibles: OPEN / CLOSE\n"
            "V401 = OPEN\n"
            "V402 = OPEN\n"
            "V403 = OPEN\n"
            "\n"
            "# Valores Posibles: AzMarino / AzCeleste\n"
            "COLOR_A_MEZCLAR = AzMarino\n"
            "\n"
            "# Valores Posibles: ON / OFF   (Se debe apagar <OFF> y volver a "
            "encender <ON>\n"
            "# para comenzar un nuevo lote)\n"
            "ARRANQUE_DE_FABRICACIÓN = OFF\n";
        ofstream out(filename, ios::trunc);

        if (!out) {
            throw runtime_error("Could not write default config file: " +
                                filename);
        }
        out << default_config;
        out.close();
    }
};

class LevelTransmitter {
  private:
    string code;
    double level;
    void evaluate_level(double &current_capacity, double &max_capacity) {
        if (current_capacity > max_capacity) {
            current_capacity = max_capacity;
        } else if (current_capacity < 0) {
            current_capacity = 0;
        }
        level = (current_capacity / max_capacity) * 100.0;
    }

  public:
    LevelTransmitter(string code)
        : code(code), level(INITIAL_MIXER_TANK_LEVEL) {}

    string get_code() const { return code; }

    double read_level(double &current_capacity, double &max_capacity) {
        evaluate_level(current_capacity, max_capacity);
        return level;
    }
};

class LiquidTank {
  private:
    string code;
    string liquid_name;
    double max_capacity;
    double current_capacity;
    LevelTransmitter level_transmitter;

  public:
    LiquidTank(string tank_code, string level_transmitter_code,
               string liquid_name, double max_capacity, double current_capacity)
        : code(tank_code), liquid_name(liquid_name), max_capacity(max_capacity),
          current_capacity(current_capacity),
          level_transmitter(level_transmitter_code) {}

    string get_liquid_in_tank_name() const { return liquid_name; }

    string get_code() const { return code; }

    double get_level() {
        return level_transmitter.read_level(current_capacity, max_capacity);
    }

    double drain(double amount) {
        double drained_amount = 1;

        if (current_capacity >= amount) {
            current_capacity -= amount;
            drained_amount = amount;
        } else {
            drained_amount = current_capacity;
            current_capacity = 1;
        }

        return drained_amount;
    }
};

class FlowSwitch {
  private:
    string code;
    bool status;

  public:
    FlowSwitch(const string &code)
        : code(code), status(INITIAL_FLOW_TRANSMISSOR_STATE) {}

    void evaluate_status(double drained) { status = (drained > 0); }

    string get_code() const { return code; }
};

class Valves {
  private:
    string code;
    bool is_open;

  public:
    Valves(const string &code, bool is_open = true)
        : code(code), is_open(is_open) {}

    void toggle_open() { this->is_open = !this->is_open; }

    void set_open(bool new_open_state) { this->is_open = new_open_state; }

    bool get_is_open() const { return is_open; }

    string get_code() const { return code; }
};

class LiquidPump {
  private:
    string code;
    double flow_rate_lts_min;
    double target_pump_duration_seconds;
    double pump_elapsed_seconds;
    bool is_on;

    void start() { is_on = true; }
    void stop() { is_on = false; }

  public:
    LiquidPump(const string &code, double flow_rate = 100.0)
        : code(code), flow_rate_lts_min(flow_rate),
          target_pump_duration_seconds(0.0), pump_elapsed_seconds(0.0),
          is_on(INITIAL_PUMP_STATE) {}

    bool get_is_on() const { return is_on; }

    double get_flow_rate() const { return flow_rate_lts_min; }

    string get_code() const { return code; }

    void update_pump_state(const FlowSwitch &flow_switch,
                           double &current_pressure) {

        if (flow_switch.get_code() == "Alarma" || current_pressure > 50.0 ||
            pump_elapsed_seconds >= target_pump_duration_seconds) {
            stop();
        } else {
            // Only start the pump if it is currently off and pressure is less
            // than 20
            if (!this->is_on && current_pressure >= 20.0) {
                return;
            }
            start();
        }
    }

    void set_pump_lts(double amount_lts) {
        target_pump_duration_seconds = (amount_lts / flow_rate_lts_min) * 60.0;
        pump_elapsed_seconds = 0.0;
    }
};

class PressureTransmitter {
  private:
    string code;
    double pressure;

  public:
    PressureTransmitter(const string &code,
                        double pressure = INITIAL_PRESSURE_FOR_ALL)
        : code(code), pressure(pressure) {}

    string get_code() const { return code; }

    void update_pressure(const Valves &enter_valve, const Valves &exit_valve,
                         const LiquidPump &pump) {
        if (enter_valve.get_is_open() && exit_valve.get_is_open()) {
            if (pump.get_is_on()) {
                pressure = 100.0; // Normal operating pressure
            } else {
                pressure += 3.0; // Pressure increases when pump is off
            }
        } else {
            pressure = 0.0; // No flow, no pressure
        }
    }

    double read_pressure() const { return pressure; }
};

class PumpLine {
  private:
    LiquidPump pump;
    Valves enter_valve;
    Valves exit_valve;
    FlowSwitch flow_switch;
    PressureTransmitter pressure_transmitter;
    LiquidTank tank;

  public:
    PumpLine(const string &pump_code, const string &enter_valve_code,
             const string &exit_valve_code, const string &flow_switch_code,
             const string &pressure_transmitter_code, const string &tank_code,
             const string &liquid_name, double max_capacity,
             double current_capacity,
             string level_transmitter_code = "LevelTransmitter")
        : pump(pump_code), enter_valve(enter_valve_code),
          exit_valve(exit_valve_code), flow_switch(flow_switch_code),
          pressure_transmitter(pressure_transmitter_code),
          tank(tank_code, level_transmitter_code, liquid_name, max_capacity,
               current_capacity) {}

    void update_pump_state(double &current_pressure) {
        pump.update_pump_state(flow_switch, current_pressure);
        pressure_transmitter.update_pressure(enter_valve, exit_valve, pump);
    }

    LiquidPump get_pump() const { return pump; }
};

class Factory {
  private:
    map<string, PumpLine> pump_lines;
    bool batch_in_proccess;

  public:
    Factory() : batch_in_proccess(false) {}

    void add_pump_line(const PumpLine &pump_line) {
        pump_lines.emplace(pump_line.get_pump().get_code(), pump_line);
    }

    bool is_batch_in_process() const { return batch_in_proccess; }

    void set_batch_in_process(bool status) { batch_in_proccess = status; }

    PumpLine get_pump_line(const string &pump_code) const {
        return pump_lines.at(pump_code);
    }
};

class Display {
  private:
    void clear_screen() { system("cls"); }

    bool prompt_config_repair(const runtime_error &e) {
        clear_screen();
        cerr << "Ha ocurrido un error leyendo la configuración: " << e.what()
             << endl;
        cout << "¿Quieres que se corrija la configuración con un archivo de "
                "configuración con las configuraciones iniciales? "
                "Escribe 'si', o escribe 'no' para cerrar el programa."
             << endl;

        cout << "Tu opción: ";
        string user_choice;
        cin >> user_choice;

        if (user_choice != "si") {
            cout << "El usuario eligió no reparar la configuración." << endl;
            return false; // User chose not to repair
        }
        return true; // User chose to repair
    }

    void show_config_repair_success() {
        cout << "El archivo de configuración ha sido escrito en: "
             << CONFIG_FILE_PATH << endl;
        cout << "Por favor, ajusta la configuración según sea necesario."
             << endl;
        cout << "Cuando hayas terminado, presiona Enter para continuar..."
             << endl;
        cin.ignore(numeric_limits<streamsize>::max(),
                   '\n'); // Clear buffer
        cin.get();
    }

    void show_config_repair_error(const exception &ex) {
        cerr << "Error en reparar la configuración: " << ex.what() << endl;
    }

    bool attempt_config_repair() {
        try {
            ConfigManager::repair_or_create_config_file();
            show_config_repair_success();
            return true;
        } catch (const exception &ex) {
            show_config_repair_error(ex);
            return false;
        }
    }

    bool handle_config_error(const runtime_error &e) {
        if (!prompt_config_repair(e)) {
            return false; // User declined repair
        }

        return attempt_config_repair();
    }

  public:
    void general_simulation_tracker_ui() {}

    ConfigManager::Config handle_config_loading() {
        while (true) {
            try {
                return ConfigManager::read_config();
            } catch (const runtime_error &e) {
                if (!handle_config_error(e)) {
                    throw runtime_error(
                        "La configuración no pudo ser corregida con la "
                        "herramineta de reparación. El programa se cerrará.");
                }
                // If repair succeeded, continue loop to try reading again
            }
        }
    }

    void clear_display() { clear_screen(); }
};

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    bool is_running = true;
    ConfigManager::Config user_config;
    Factory factory;
    Display ui_wrapper = Display();

    while (is_running) {
        try {
            user_config = ui_wrapper.handle_config_loading();
        } catch (const runtime_error &e) {
            cerr << "Error crítico durante el manejo del archivo de "
                    "configuración: "
                 << e.what() << endl;
            system("pause");
            return 1;
        }

        ui_wrapper.clear_display();
        ui_wrapper.general_simulation_tracker_ui();

        if (!factory.is_batch_in_process()) {
            // Process can start
        }
        // si falta tiempo por cumplir en las bombas, bombeo
        else {
            // Continue pumping
        }

        Sleep(ONE_SECOND_IN_MS);
    }

    return 0;
}
