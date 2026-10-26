#include "Cs.h"

int Cs::nextId = 1;

Cs::Cs() : id(nextId++), kol_tsex(0), active_tsex(0), class_stan(0) {}

void Cs::updateNextId(int loadedId) {
    if (loadedId >= nextId) nextId = loadedId + 1;
}

int Cs::getId() const { 
    return id; }
std::string Cs::getName() const { 
    return name; }
double Cs::getIdlePercent() const {
    return kol_tsex > 0 ? (kol_tsex - active_tsex) * 100.0 / kol_tsex : 0;
}

void Cs::read() {
    std::cout << "\nВведите название КС: ";
    std::getline(std::cin >> std::ws, name);

    while (true) {
        std::cout << "Введите количество цехов (всего): ";
        if (std::cin >> kol_tsex && std::cin.peek() == '\n' && kol_tsex > 0) break;
        std::cout << "Введите положительное целое число.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore(10000, '\n');

    while (true) {
        std::cout << "Введите количество цехов в работе: ";
        if (std::cin >> active_tsex && std::cin.peek() == '\n' &&
            active_tsex >= 0 && active_tsex <= kol_tsex) break;
        std::cout << "Введите число от 0 до " << kol_tsex << ".\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    while (true) {
        std::cout << "Введите класс станции: ";
        if (std::cin >> class_stan && std::cin.peek() == '\n' && class_stan > 0) break;
        std::cout << "Введите положительное целое число.\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    Logger::getInstance().log("Создана КС ID=" + std::to_string(id) + ": " + name);
}

std::ostream& operator<<(std::ostream& os, const Cs& c) {
    os << "\nИтоговая информация о КС (ID: " << c.id << ")\n";
    os << "Название: " << c.name << "\n";
    os << "Количество цехов: " << c.kol_tsex << "\n";
    os << "Количество активных цехов: " << c.active_tsex << "\n";
    os << "Класс станции: " << c.class_stan << "\n";
    return os;
}

void Cs::work_cs() {
    int work;
    std::cout << "\nЗапустить или остановить цех КС " << name << ":\n";
    std::cout << "1 - запустить цех\n2 - остановить цех\nВыберите действие: ";
    while (true) {
        if (std::cin >> work && std::cin.peek() == '\n' && (work == 1 || work == 2)) break;
        std::cout << "Введите 1 или 2\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }

    if (work == 1) startWorkshop();
    else if (work == 2) stopWorkshop();
}

void Cs::startWorkshop() {
    if (active_tsex < kol_tsex) {
        active_tsex++;
        Logger::getInstance().log("КС ID=" + std::to_string(id) + ": запущен цех (активных: " + std::to_string(active_tsex) + ")");
        std::cout << "Цех запущен, активных цехов: " << active_tsex << "\n";
    }
    else {
        std::cout << "Все цеха уже работают\n";
    }
}

void Cs::stopWorkshop() {
    if (active_tsex > 0) {
        active_tsex--;
        Logger::getInstance().log("КС ID=" + std::to_string(id) + ": остановлен цех (активных: " + std::to_string(active_tsex) + ")");
        std::cout << "Цех остановлен, активных цехов: " << active_tsex << "\n";
    }
    else {
        std::cout << "Нет работающих цехов для остановки\n";
    }
}

bool Cs::matchesName(const std::string& q) const {
    return name.find(q) != std::string::npos;
}
bool Cs::matchesIdle(double min) const {
    return getIdlePercent() >= min;
}

void Cs::saveToFile(std::ofstream& out) const {
    out << id << "\n";
    out << name << "\n";
    out << kol_tsex << "\n";
    out << active_tsex << "\n";
    out << class_stan << "\n";
}

bool Cs::loadFromFile(std::ifstream& in) {
    if (!(in >> id)) 
        return false;
    in.ignore();
    if (!std::getline(in, name)) 
        return false;
    if (!(in >> kol_tsex >> active_tsex >> class_stan)) 
        return false;
    in.ignore(10000, '\n');
    updateNextId(id);
    return true;
}