#include "Pipe.h"

int Pipe::nextId = 1;

Pipe::Pipe() : id(nextId++), length(0.0), diametr(0), repair(false) {}

void Pipe::updateNextId(int loadedId) {
    if (loadedId >= nextId) 
        nextId = loadedId + 1;
}

int Pipe::getId() const { 
    return id; 
}
std::string Pipe::getName() const { 
    return name; 
}
bool Pipe::isRepair() const { 
    return repair; 
}

void Pipe::read() {
    std::cout << "Введите название трубы: ";
    std::getline(std::cin >> std::ws, name);

    while (true) {
        std::cout << "Введите длину в км: ";
        if (std::cin >> length && std::cin.peek() == '\n' && length > 0) break;
        std::cout << "Введите положительное число.\n";
        std::cin.clear(); 
        std::cin.ignore(10000, '\n');
    }
    while (true) {
        std::cout << "Введите диаметр в мм: ";
        if (std::cin >> diametr && std::cin.peek() == '\n' && diametr > 0) break;
        std::cout << "Введите положительное число\n";
        std::cin.clear(); 
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore(10000, '\n');

    std::string input;
    while (true) {
        std::cout << "В ремонте? (1 - да, 0 - нет): ";
        std::getline(std::cin, input);
        if (input == "0" || input == "1") 
        { repair = (input == "1"); break; 
        }
        std::cout << "Введите 0 или 1.\n";
    }
    Logger::getInstance().log("Создана труба ID = " + std::to_string(id) + ": " + name);
}

std::ostream& operator<<(std::ostream& os, const Pipe& p) {
    os << "\nИтоговая информация о трубе (ID: " << p.id << ")\n";
    os << "Название: " << p.name << "\n";
    os << "Длина: " << p.length << " км\n";
    os << "Диаметр: " << p.diametr << " мм\n";
    os << "В ремонте?: " << (p.repair ? "да" : "нет") << "\n";
    return os;
}

void Pipe::ent_repair() {
    repair = !repair;
    std::cout << "Статус изменен: " << (repair ? "В ремонте" : "В работе") << "\n";
    Logger::getInstance().log("Труба ID=" + std::to_string(id) + " сменила статус ремонта");
}

bool Pipe::matchesName(const std::string& q) const 
{ return name.find(q) != std::string::npos; }

bool Pipe::matchesRepair(bool state) const 
{ return repair == state; }

void Pipe::saveToFile(std::ofstream& out) const {
    out << id << "\n";
    out << name << "\n";
    out << length << "\n";
    out << diametr << "\n";
    out << (repair ? 1 : 0) << "\n";
}

bool Pipe::loadFromFile(std::ifstream& in) {
    if (!(in >> id)) 
        return false;
    in.ignore();
    if (!std::getline(in, name)) 
        return false;
    if (!(in >> length >> diametr)) 
        return false;
    int temp; 
    if (!(in >> temp)) 
        return false;
    repair = (temp == 1);
    in.ignore(10000, '\n');
    updateNextId(id);
    return true;
}