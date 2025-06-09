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

namespace SystemConstants {
const bool NORMAL_STATUS = true;
const bool ALARM_STATUS = false;
const int ONE_SECOND_IN_MS = 1000;
const double INITIAL_TANK_CAPACITY = 20000.0;
const double INITIAL_BASE_TANK_LEVELS = 25.0;
const double INITIAL_MIXER_TANK_LEVEL = 0.0;
const double NORMAL_OPERATING_PRESSURE = 33.0;
const double HIGH_PRESSURE_THRESHOLD = 50.0;
const double LOW_PRESSURE_THRESHOLD = 20.0;
const double PRESSURE_INCREMENT = 3.0;
const double INITIAL_PRESSURE = 0.0;
const double DEFAULT_FLOW_RATE = 100.0;
const bool INITIAL_PUMP_STATE = false;
const bool INITIAL_FLOW_TRANSMITTER_STATE = NORMAL_STATUS;
const string CONFIG_FILE_PATH = "./tercer_parcial_config.txt";
} // namespace SystemConstants

struct SystemConfig {
    map<string, string> valve_states;
    string color_a_mezclar;
    string arranque_de_fabricacion;
};

class StringUtils {
  public:
    static string trim_whitespace(const string &s) {
        auto start = s.find_first_not_of(" \t\r\n");
        auto end = s.find_last_not_of(" \t\r\n");
        if (start == string::npos)
            return "";
        return s.substr(start, end - start + 1);
    }
};

class ConfigFileHandler {
  public:
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
        key = StringUtils::trim_whitespace(line.substr(0, eq_pos));
        value = StringUtils::trim_whitespace(line.substr(eq_pos + 1));
        return !(key.empty() || value.empty());
    }

    static void create_default_config_file(
        const string &filename = SystemConstants::CONFIG_FILE_PATH) {
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

class ConfigValidator {
  private:
    static const vector<string> KNOWN_VALVE_KEYS;
    static const string K_COLOR;
    static const string K_ARRANQUE;

  public:
    static void validate_and_set_config_pair(SystemConfig &config,
                                             const string &key,
                                             const string &value) {
        if (key == K_COLOR) {
            validate_color_value(value);
            config.color_a_mezclar = value;
        } else if (key == K_ARRANQUE) {
            validate_start_command_value(value);
            config.arranque_de_fabricacion = value;
        } else if (is_known_valve(key)) {
            validate_valve_value(key, value);
            config.valve_states[key] = value;
        } else {
            throw runtime_error("Invalid configuration key found: " + key);
        }
    }

    static void validate_complete_config(const SystemConfig &config) {
        if (config.color_a_mezclar.empty()) {
            throw runtime_error("Missing required setting: COLOR_A_MEZCLAR");
        }
        if (config.arranque_de_fabricacion.empty()) {
            throw runtime_error(
                "Missing required setting: ARRANQUE_DE_FABRICACIÓN");
        }

        for (const auto &valve : KNOWN_VALVE_KEYS) {
            if (config.valve_states.find(valve) == config.valve_states.end()) {
                throw runtime_error("Missing required valve setting: " + valve);
            }
        }
    }

  private:
    static void validate_color_value(const string &value) {
        if (value != "AzMarino" && value != "AzCeleste") {
            throw runtime_error("Invalid value for COLOR_A_MEZCLAR: " + value);
        }
    }

    static void validate_start_command_value(const string &value) {
        if (value != "ON" && value != "OFF") {
            throw runtime_error("Invalid value for ARRANQUE_DE_FABRICACIÓN: " +
                                value);
        }
    }

    static void validate_valve_value(const string &key, const string &value) {
        if (value != "OPEN" && value != "CLOSED") {
            throw runtime_error("Invalid value for valve " + key + ": " +
                                value);
        }
    }

    static bool is_known_valve(const string &key) {
        return find(KNOWN_VALVE_KEYS.begin(), KNOWN_VALVE_KEYS.end(), key) !=
               KNOWN_VALVE_KEYS.end();
    }
};

const vector<string> ConfigValidator::KNOWN_VALVE_KEYS = {
    "V201", "V202", "V203", "V401", "V402", "V403"};
const string ConfigValidator::K_COLOR = "COLOR_A_MEZCLAR";
const string ConfigValidator::K_ARRANQUE = "ARRANQUE_DE_FABRICACIÓN";

class ConfigManager {
  public:
    static SystemConfig
    read_config(const string &filename = SystemConstants::CONFIG_FILE_PATH) {
        SystemConfig config;
        ifstream file;
        ConfigFileHandler::open_config_file(file, filename);
        string line, key, value;
        int line_number = 0;

        while (getline(file, line)) {
            line_number++;
            string trimmed = StringUtils::trim_whitespace(line);

            if (trimmed.empty() || trimmed[0] == '#')
                continue;

            if (!ConfigFileHandler::parse_config_line(trimmed, key, value)) {
                cerr << "Warning: Malformed config line " << line_number << ": "
                     << line << endl;
                continue;
            }
            ConfigValidator::validate_and_set_config_pair(config, key, value);
        }

        ConfigValidator::validate_complete_config(config);
        return config;
    }

    static void repair_or_create_config_file(
        const string &filename = SystemConstants::CONFIG_FILE_PATH) {
        ConfigFileHandler::create_default_config_file(filename);
    }
};

class LevelTransmitter {
  private:
    string code_;
    double level_;

    void evaluate_level(double &current_capacity, double &max_capacity) {
        if (current_capacity > max_capacity) {
            current_capacity = max_capacity;
        } else if (current_capacity < 0) {
            current_capacity = 0;
        }
        level_ = (current_capacity / max_capacity) * 100.0;
    }

  public:
    explicit LevelTransmitter(const string &code)
        : code_(code), level_(SystemConstants::INITIAL_MIXER_TANK_LEVEL) {}

    const string &get_code() const { return code_; }

    double read_level(double &current_capacity, double &max_capacity) const {
        const_cast<LevelTransmitter *>(this)->evaluate_level(current_capacity,
                                                             max_capacity);
        return level_;
    }
};

class LiquidTank {
  private:
    string code_;
    string liquid_name_;
    double max_capacity_;
    double current_capacity_;
    LevelTransmitter level_transmitter_;

  public:
    LiquidTank(const string &tank_code, const string &level_transmitter_code,
               const string &liquid_name, double max_capacity,
               double current_capacity)
        : code_(tank_code), liquid_name_(liquid_name),
          max_capacity_(max_capacity), current_capacity_(current_capacity),
          level_transmitter_(level_transmitter_code) {}

    const string &get_liquid_in_tank_name() const { return liquid_name_; }
    const string &get_code() const { return code_; }
    double get_max_capacity() const { return max_capacity_; }
    double get_current_capacity() const { return current_capacity_; }

    double get_level() const {
        return level_transmitter_.read_level(
            const_cast<double &>(current_capacity_),
            const_cast<double &>(max_capacity_));
    }

    double drain(double amount) {
        if (amount <= 0) {
            return 0.0;
        }

        double drained_amount;
        if (current_capacity_ >= amount) {
            current_capacity_ -= amount;
            drained_amount = amount;
        } else {
            drained_amount = current_capacity_;
            current_capacity_ = 0.0;
        }
        return drained_amount;
    }

    void add_liquid(double amount) {
        if (amount > 0) {
            current_capacity_ = min(current_capacity_ + amount, max_capacity_);
        }
    }
};

class FlowSwitch {
  private:
    string code_;
    bool status_;

  public:
    explicit FlowSwitch(
        const string &code,
        bool initial_status = SystemConstants::INITIAL_FLOW_TRANSMITTER_STATE)
        : code_(code), status_(initial_status) {
        if (code.empty()) {
            throw invalid_argument("FlowSwitch code cannot be empty");
        }
    }

    void evaluate_status(double flow_rate) {
        status_ = (flow_rate > 0) ? SystemConstants::NORMAL_STATUS
                                  : SystemConstants::ALARM_STATUS;
    }

    const string &get_code() const { return code_; }
    bool is_normal() const { return status_ == SystemConstants::NORMAL_STATUS; }
    bool is_alarm() const { return status_ == SystemConstants::ALARM_STATUS; }
};

class Valve {
  private:
    string code_;
    bool is_open_;

  public:
    explicit Valve(const string &code, bool is_open = true)
        : code_(code), is_open_(is_open) {}

    void toggle() { is_open_ = !is_open_; }
    void set_open(bool new_open_state) { is_open_ = new_open_state; }
    bool is_open() const { return is_open_; }
    const string &get_code() const { return code_; }
};

enum class PumpState {
    STOPPED_LOW_PRESSURE,
    STOPPED_HIGH_PRESSURE,
    STOPPED_FLOW_ALARM,
    STOPPED_TARGET_REACHED,
    RUNNING
};

class LiquidPump {
  private:
    string code_;
    double flow_rate_lts_min_;
    double target_pump_duration_seconds_;
    double pump_elapsed_seconds_;
    bool is_on_;
    PumpState current_state_;

    void start() {
        is_on_ = true;
        current_state_ = PumpState::RUNNING;
    }

    void stop(PumpState reason) {
        is_on_ = false;
        current_state_ = reason;
    }

    bool should_stop_for_alarm(const FlowSwitch &flow_switch) const {
        return flow_switch.is_alarm();
    }

    bool should_stop_for_high_pressure(double current_pressure) const {
        return current_pressure > SystemConstants::HIGH_PRESSURE_THRESHOLD;
    }

    bool should_stop_for_target_reached() const {
        return pump_elapsed_seconds_ >= target_pump_duration_seconds_;
    }

    bool can_start_for_pressure(double current_pressure) const {
        return current_pressure < SystemConstants::LOW_PRESSURE_THRESHOLD;
    }

  public:
    explicit LiquidPump(const string &code,
                        double flow_rate = SystemConstants::DEFAULT_FLOW_RATE)
        : code_(code), flow_rate_lts_min_(flow_rate),
          target_pump_duration_seconds_(0.0), pump_elapsed_seconds_(0.0),
          is_on_(SystemConstants::INITIAL_PUMP_STATE),
          current_state_(PumpState::STOPPED_LOW_PRESSURE) {}

    bool is_on() const { return is_on_; }
    double get_flow_rate() const { return flow_rate_lts_min_; }
    const string &get_code() const { return code_; }
    PumpState get_state() const { return current_state_; }
    double get_elapsed_seconds() const { return pump_elapsed_seconds_; }
    double get_target_duration() const { return target_pump_duration_seconds_; }

    void update_pump_state(const FlowSwitch &flow_switch,
                           double current_pressure) {
        if (should_stop_for_alarm(flow_switch)) {
            stop(PumpState::STOPPED_FLOW_ALARM);
            return;
        }

        if (should_stop_for_high_pressure(current_pressure)) {
            stop(PumpState::STOPPED_HIGH_PRESSURE);
            return;
        }

        if (should_stop_for_target_reached()) {
            stop(PumpState::STOPPED_TARGET_REACHED);
            return;
        }

        if (!is_on_ && can_start_for_pressure(current_pressure)) {
            start();
        }
    }

    void set_pump_target_liters(double amount_lts) {
        if (amount_lts > 0) {
            target_pump_duration_seconds_ =
                (amount_lts / flow_rate_lts_min_) * 60.0;
            pump_elapsed_seconds_ = 0.0;
        }
    }

    void increment_elapsed_time(double seconds) {
        if (is_on_) {
            pump_elapsed_seconds_ += seconds;
        }
    }
};

class PressureTransmitter {
  private:
    string code_;
    double pressure_;

  public:
    explicit PressureTransmitter(
        const string &code, double pressure = SystemConstants::INITIAL_PRESSURE)
        : code_(code), pressure_(pressure) {}

    const string &get_code() const { return code_; }
    double read_pressure() const { return pressure_; }

    void update_pressure(const Valve &enter_valve, const Valve &exit_valve,
                         const LiquidPump &pump) {

        if (enter_valve.is_open() && exit_valve.is_open()) {
            if (pump.is_on()) {
                pressure_ = SystemConstants::NORMAL_OPERATING_PRESSURE;
            } else {
                pressure_ += SystemConstants::PRESSURE_INCREMENT;
            }
        } else if (!exit_valve.is_open()) {
            if (pump.is_on()) {
                pressure_ += SystemConstants::PRESSURE_INCREMENT * 2;
            }
        } else {
            pressure_ = SystemConstants::INITIAL_PRESSURE;
        }

        if (pressure_ < 0) {
            pressure_ = 0;
        }
    }
};

class PumpLine {
  private:
    LiquidPump pump_;
    Valve enter_valve_;
    Valve exit_valve_;
    FlowSwitch flow_switch_;
    PressureTransmitter pressure_transmitter_;
    LiquidTank tank_;

    // Private constructor - only accessible through static factory method
    PumpLine(const string &pump_code, const string &enter_valve_code,
             const string &exit_valve_code, const string &flow_switch_code,
             const string &pressure_transmitter_code, const string &tank_code,
             const string &liquid_name, double max_capacity,
             double current_capacity, const string &level_transmitter_code)
        : pump_(pump_code), enter_valve_(enter_valve_code),
          exit_valve_(exit_valve_code), flow_switch_(flow_switch_code),
          pressure_transmitter_(pressure_transmitter_code),
          tank_(tank_code, level_transmitter_code, liquid_name, max_capacity,
                current_capacity) {}

  public:
    // Single creation method for standard paint lines - SIMPLIFIED
    static PumpLine create_standard_paint_line(const string &pump_code,
                                               const string &liquid_name) {
        if (pump_code.empty())
            throw invalid_argument("Pump code required");
        if (liquid_name.empty())
            throw invalid_argument("Liquid name required");

        return PumpLine(pump_code,
                        "V" + pump_code.substr(1),  // P201 -> V201
                        "V4" + pump_code.substr(2), // P201 -> V401
                        "FS" + pump_code.substr(1), "PT" + pump_code.substr(1),
                        "T" + pump_code.substr(1), liquid_name,
                        SystemConstants::INITIAL_TANK_CAPACITY,
                        SystemConstants::INITIAL_TANK_CAPACITY *
                            SystemConstants::INITIAL_BASE_TANK_LEVELS / 100.0,
                        "LT" + pump_code.substr(1));
    }

    void update_system_state() {
        double current_flow = pump_.is_on() ? pump_.get_flow_rate() : 0.0;
        flow_switch_.evaluate_status(current_flow);
        pump_.update_pump_state(flow_switch_,
                                pressure_transmitter_.read_pressure());
        pressure_transmitter_.update_pressure(enter_valve_, exit_valve_, pump_);
    }

    const LiquidPump &get_pump() const { return pump_; }
    const Valve &get_enter_valve() const { return enter_valve_; }
    const Valve &get_exit_valve() const { return exit_valve_; }
    const FlowSwitch &get_flow_switch() const { return flow_switch_; }
    const PressureTransmitter &get_pressure_transmitter() const {
        return pressure_transmitter_;
    }
    const LiquidTank &get_tank() const { return tank_; }

    LiquidPump &get_pump_mutable() { return pump_; }
    Valve &get_enter_valve_mutable() { return enter_valve_; }
    Valve &get_exit_valve_mutable() { return exit_valve_; }
    LiquidTank &get_tank_mutable() { return tank_; }
};

class Factory {
  private:
    map<string, PumpLine> pump_lines_;
    bool batch_in_process_;

    // Private constructor ensures controlled initialization
    explicit Factory(const vector<PumpLine> &pump_lines)
        : batch_in_process_(false) {
        if (pump_lines.empty()) {
            throw runtime_error("Factory must have at least one pump line");
        }
        for (const auto &line : pump_lines) {
            pump_lines_.emplace(line.get_pump().get_code(), line);
        }
    }

  public:
    // Static factory method for standard Dupont paint mixing configuration
    static Factory create_dupont_paint_factory() {
        vector<PumpLine> pump_lines;

        pump_lines.push_back(
            PumpLine::create_standard_paint_line("P201", "Blanco"));
        pump_lines.push_back(
            PumpLine::create_standard_paint_line("P202", "Azul"));
        pump_lines.push_back(
            PumpLine::create_standard_paint_line("P203", "Negro"));

        return Factory(pump_lines);
    }

    // Static factory method for custom configurations
    static Factory create_custom_factory(const vector<PumpLine> &pump_lines) {
        return Factory(pump_lines);
    }

    bool is_batch_in_process() const { return batch_in_process_; }

    void set_batch_in_process() {
        if (!batch_in_process_) {
            batch_in_process_ = true;
        };
    }

    const PumpLine &get_pump_line(const string &pump_code) const {
        auto it = pump_lines_.find(pump_code);
        if (it == pump_lines_.end()) {
            throw runtime_error("Pump line not found: " + pump_code);
        }
        return it->second;
    }

    PumpLine &get_pump_line_mutable(const string &pump_code) {
        auto it = pump_lines_.find(pump_code);
        if (it == pump_lines_.end()) {
            throw runtime_error("Pump line not found: " + pump_code);
        }
        return it->second;
    }

    const map<string, PumpLine> &get_all_pump_lines() const {
        return pump_lines_;
    }

    void update_all_pump_lines() {
        for (auto &[code, pump_line] : pump_lines_) {
            pump_line.update_system_state();
        }
    }

    void reset() {
        for (auto &[code, pump_line] : pump_lines_) {
            pump_line.get_pump_mutable().set_pump_target_liters(0);
            pump_line.get_pump_mutable().increment_elapsed_time(
                -pump_line.get_pump().get_elapsed_seconds());
            pump_line.get_tank_mutable().add_liquid(
                -pump_line.get_tank().get_current_capacity());
            pump_line.get_enter_valve_mutable().set_open(true);
            pump_line.get_exit_valve_mutable().set_open(true);
        }
        batch_in_process_ = false;
    }
};

class UserInterface {
  private:
    void clear_screen() { system("cls"); }

  public:
    void clear_display() { clear_screen(); }

    void show_simulation_status(const Factory &factory,
                                const SystemConfig &config) {
        clear_screen();
        cout << "=== Sistema de Mezcla de Pintura Dupont ===" << endl;
        cout << "Color a mezclar: " << config.color_a_mezclar << endl;
        cout << "Estado de fabricación: " << config.arranque_de_fabricacion
             << endl;
        cout << "Lote en proceso: "
             << (factory.is_batch_in_process() ? "SÍ" : "NO") << endl;
        cout << endl;

        cout << "=== Estado de las Líneas de Bombeo ===" << endl;
        for (const auto &[code, pump_line] : factory.get_all_pump_lines()) {
            show_pump_line_status(pump_line);
        }
    }

  private:
    void show_pump_line_status(const PumpLine &pump_line) {
        const auto &pump = pump_line.get_pump();
        const auto &tank = pump_line.get_tank();
        const auto &pressure = pump_line.get_pressure_transmitter();

        cout << "Bomba " << pump.get_code() << " ("
             << tank.get_liquid_in_tank_name() << "):" << endl;
        cout << "  Estado: " << (pump.is_on() ? "ENCENDIDA" : "APAGADA")
             << endl;
        cout << "  Tiempo transcurrido: " << pump.get_elapsed_seconds() << "s"
             << endl;
        cout << "  Tiempo objetivo: " << pump.get_target_duration() << "s"
             << endl;
        cout << "  Nivel tanque: " << tank.get_level() << "%" << endl;
        cout << "  Presión: " << pressure.read_pressure() << " psi" << endl;
        cout << endl;
    }
};

class ConfigurationUI {
  private:
    UserInterface ui_;

    bool prompt_config_repair(const runtime_error &e) {
        ui_.clear_display();
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
            return false;
        }
        return true;
    }

    void show_config_repair_success() {
        cout << "El archivo de configuración ha sido escrito en: "
             << SystemConstants::CONFIG_FILE_PATH << endl;
        cout << "Por favor, ajusta la configuración según sea necesario."
             << endl;
        cout << "Cuando hayas terminado, presiona Enter para continuar..."
             << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            return false;
        }
        return attempt_config_repair();
    }

  public:
    SystemConfig handle_config_loading() {
        while (true) {
            try {
                return ConfigManager::read_config();
            } catch (const runtime_error &e) {
                if (!handle_config_error(e)) {
                    throw runtime_error(
                        "La configuración no pudo ser corregida con la "
                        "herramienta de reparación. El programa se cerrará.");
                }
            }
        }
    }
};

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    try {
        bool is_running = true;
        SystemConfig user_config;

        // Create factory with standard Dupont paint mixing configuration
        Factory factory = Factory::create_dupont_paint_factory();

        ConfigurationUI config_ui;
        UserInterface main_ui;

        while (is_running) {
            try {
                user_config = config_ui.handle_config_loading();
            } catch (const runtime_error &e) {
                cerr << "Error crítico durante el manejo del archivo de "
                        "configuración: "
                     << e.what() << endl;
                system("pause");
                return 1;
            }

            main_ui.show_simulation_status(factory, user_config);

            if (!factory.is_batch_in_process()) {
                if (user_config.arranque_de_fabricacion == "ON") {
                    factory.set_batch_in_process();
                    factory.reset();
                    // set new pump targets
                }
            } else {
                factory.update_all_pump_lines();
            }

            Sleep(SystemConstants::ONE_SECOND_IN_MS);
        }
    } catch (const exception &e) {
        cerr << "Error crítico en el programa: " << e.what() << endl;
        return 1;
    }

    return 0;
}
