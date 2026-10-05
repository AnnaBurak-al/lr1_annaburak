// lab1_burak.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <clocale>
#include <fstream>

struct Pipe {
    std::string name;
    double length = 0.0;
    int diametr = 0; 
    bool repair = false;

    void read()
    {
        std::cout << "Введите название трубы: ";
        std::getline(std::cin, name);

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
            if (input == "0" || input == "1") {
                repair = (input == "1");
                break;
            }
            std::cout << "Введите 0 или 1.\n";
        }
    }

    void print() const {
        std::cout << "\nИтоговая информация о трубе\n";
        std::cout << "Название: " << name << "\n";
        std::cout << "Длина: " << length << " км\n";
        std::cout << "Диаметр: " << diametr << " мм\n";
        std::cout << "В ремонте?: " << (repair ? "да" : "нет") << "\n";
    }

    void ent_repair() {
        std::string input;
        while (true) {
            std::cout << "\nИзменить признак в ремонте (1 - в ремонте, 0 - не в ремонте): ";
            std::getline(std::cin, input);
            if (input == "0" || input == "1") {
                repair = (input == "1");
                break;
            }
            std::cout << "Введите 0 или 1.\n";
        }
    }

    void saveToFile(std::ofstream& out) {
        out << "PIPE\n";
        out << name << "\n";
        out << length << "\n";
        out << diametr << "\n";
        out << (repair ? 1 : 0) << "\n";
    }

    bool loadFromFile(std::ifstream& in) {
        std::string marker;
        if (!std::getline(in, marker)) return false;

        while (marker.empty() && std::getline(in, marker)) {}
        if (marker.empty()) return false;

        if (marker != "PIPE") {
            return false;
        }

        std::string tempName;
        if (!std::getline(in, tempName)) return false;
        if (tempName.empty()) return false;

        name = tempName;

        if (!(in >> length)) return false;
        if (!(in >> diametr)) return false;

        int temp;
        if (!(in >> temp)) return false;

        repair = (temp == 1);

        in.ignore(10000, '\n');

        return true;
    }
};

struct CS {
    std::string name;
    int kol_tsex = 0;
    int active_tsex = 0;
    int class_stan = 0;

    void read() {
        std::cout << "\nВведите название КС: ";
        std::getline(std::cin, name);

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
            if (std::cin >> active_tsex && std::cin.peek() == '\n' && active_tsex >= 0 && active_tsex <= kol_tsex) break;
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
    }

    void print() const {
        std::cout << "\nИтоговая информация о КС\n";
        std::cout << "Название: " << name << "\n";
        std::cout << "Количество цехов: " << kol_tsex << "\n";
        std::cout << "Количество активных цехов: " << active_tsex << "\n";
        std::cout << "Класс станции: " << class_stan << "\n";
    }

    void work_cs() {
        int work;
        std::cout << "\nЗапустить или остановить цех КС " << name << ":\n";
        std::cout << "1 - запустить цех\n";
        std::cout << "2 - остановить цех\n";

        while (true) {
            std::cout << "Выберите действие: ";
            if (std::cin >> work && std::cin.peek() == '\n' && (work == 1 || work == 2)) break;
            std::cout << "Введите 1 или 2\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        if (work == 1) {
            if (active_tsex < kol_tsex) {
                active_tsex++;
                std::cout << "Цех запущен, активных цехов: " << active_tsex << "\n";
            }
            else {
                std::cout << "Все цеха уже работают\n";
            }
        }
        else if (work == 2) {
            if (active_tsex > 0) {
                active_tsex--;
                std::cout << "Цех остановлен, активных цехов: " << active_tsex << "\n";
            }
            else {
                std::cout << "Нет работающих цехов для остановки\n";
            }
        }
    }

    void saveToFile(std::ofstream& out) {
        out << "CS\n";
        out << name << "\n";
        out << kol_tsex << "\n";
        out << active_tsex << "\n";
        out << class_stan << "\n";
    }

    bool loadFromFile(std::ifstream& in) {
        std::string marker;
        if (!std::getline(in, marker)) return false;

        while (marker.empty() && std::getline(in, marker)) {}
        if (marker.empty()) return false;

        if (marker != "CS") {
            return false;
        }

        std::string tempName;
        if (!std::getline(in, tempName)) return false;
        if (tempName.empty()) return false;

        name = tempName;

        if (!(in >> kol_tsex >> active_tsex >> class_stan)) return false;

        in.ignore(10000, '\n');

        return true;
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Pipe pipe;
    CS cs;

    bool pipeExists = false;
    bool csExists = false;

    int choice;

    while (true) {
        std::cout << "\nМеню\n";
        std::cout << "1. Добавить трубу\n";
        std::cout << "2. Добавить КС\n";
        std::cout << "3. Просмотр всех объектов\n";
        std::cout << "4. Редактировать трубу\n";
        std::cout << "5. Редактировать КС (запуск/остановка цеха)\n";
        std::cout << "6. Сохранить в файл\n";
        std::cout << "7. Загрузить из файла\n";
        std::cout << "0. Выход\n";
        std::cout << "\nВыберите действие: ";

        if (!(std::cin >> choice) || std::cin.peek() != '\n') {
            std::cout << "Введите одно число от 0 до 7.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore(10000, '\n');

        if (choice < 0 || choice > 7) {
            std::cout << "Введите одно число от 0 до 7.\n";
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
        case 1:
        {
            pipe.read();
            pipeExists = true;
            break;
        }
        case 2:
        {
            cs.read();
            csExists = true;
            break;
        }
        case 3:
            if (pipeExists) {
                pipe.print();
            }
            else {
                std::cout << "\nТруба еще не создана\n";
            }
            if (csExists) {
                cs.print();
            }
            else {
                std::cout << "\nКомпрессорная станция еще не создана\n";
            }
            break;
        case 4:
            if (pipeExists) {
                pipe.ent_repair();
            }
            else {
                std::cout << "\nТруба еще не создана\n";
            }
            break;
        case 5:
            if (csExists) {
                cs.work_cs();
            }
            else {
                std::cout << "\nКомпрессорная станция еще не создана\n";
            }
            break;
        case 6: {
            std::ofstream outFile("buraklr1.txt");
            if (outFile.is_open()) {
                if (pipeExists) {
                    pipe.saveToFile(outFile);
                }
                if (csExists) {
                    cs.saveToFile(outFile);
                }
                outFile.close();
                std::cout << "Данные сохранены в файл buraklr1.txt\n";
            }
            else {
                std::cout << "Ошибка открытия файла для записи\n";
            }
            break;
        }
        case 7: {
            std::ifstream inFile("buraklr1.txt");
            if (inFile.is_open()) {
                bool foundPipe = false;
                bool foundCS = false;

                if (pipe.loadFromFile(inFile)) {
                    pipeExists = true;
                    foundPipe = true;
                }

                if (cs.loadFromFile(inFile)) {
                    csExists = true;
                    foundCS = true;
                }

                inFile.close();

                if (foundPipe || foundCS) {
                    std::cout << "Данные загружены из buraklr1.txt\n";
                }
                else {
                    std::cout << "Файл пуст или не содержит данных\n";
                }
            }
            else {
                std::cout << "Файл buraklr1.txt не найден\n";
            }
            break;
        }
        default: std::cout << "Неверный пункт меню\n";
        }
    }
    return 0;
}