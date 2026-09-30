// lab1_burak.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <clocale>
#include <fstream>

struct Pipe {
    std::string name;
    double length = 0.0;
    double diametr = 0.0;
    bool repair = false;
    bool flag = true;

    void read() {
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
        flag = false;
    }

    void print() const {
        if (flag) {
            std::cout << "\nТруба еще не добавлена\n";
            return;
        }
        std::cout << "\nИтоговая информация о трубе\n";
        std::cout << "Название: " << name << "\n";
        std::cout << "Длина: " << length << " км\n";
        std::cout << "Диаметр: " << diametr << " мм\n";
        std::cout << "В ремонте?: " << (repair ? "да" : "нет") << "\n";
    }

    void ent_repair() {
        if (flag) {
            std::cout << "\nСначала добавьте трубу\n";
            return;
        }
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

    void saveToFile(std::ofstream& out) const {
        if (flag) return;
        out << "PIPE\n";
        out << name << "\n";
        out << length << "\n";
        out << diametr << "\n";
        out << (repair ? 1 : 0) << "\n";
    }

    void loadFromFile(std::ifstream& in) {
        flag = true;
        name = ""; length = 0; diametr = 0; repair = false;
        std::streampos pos = in.tellg();

        std::string marker;
        if (!std::getline(in, marker)) return;

        while (marker.empty() && std::getline(in, marker)) {}
        if (marker.empty()) return;

        if (marker != "PIPE") {
            in.seekg(pos);
            return;
        }

        std::string tempName;
        if (!std::getline(in, tempName)) return;
        if (tempName.empty()) return;

        name = tempName;

        if (!(in >> length)) return;
        if (!(in >> diametr)) return;

        int temp;
        if (!(in >> temp)) return;

        repair = (temp == 1);
        flag = false;

        in.ignore(10000, '\n');
    }
};

struct CS {
    std::string name;
    int kol_tsex = 0;
    int active_tsex = 0;
    int class_stan = 0;
    bool flag = true;

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
            std::string input;
            std::getline(std::cin, input); 

            bool isValid = true; 
            if (input.empty()) {
                isValid = false;
            }
            else {
                for (char c : input) {
                    if (!isdigit(c)) {
                        isValid = false; 
                        break;           
                    }
                }
            }

            if (isValid) {
                int val = std::stoi(input);

                if (val >= 0 && val <= kol_tsex) {
                    active_tsex = val; 
                    break;            
                }
            }

            std::cout << "Введите число от 0 до " << kol_tsex << ".\n";
        }
        while (true) {
            std::cout << "Введите класс станции: ";
            if (std::cin >> class_stan && std::cin.peek() == '\n' && class_stan > 0) break;
            std::cout << "Введите положительное целое число.\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }
        flag = false;
    }

    void print() const {
        if (flag) {
            std::cout << "\nКомпрессорная станция еще не добавлена\n";
            return;
        }
        std::cout << "\nИтоговая информация о КС\n";
        std::cout << "Название: " << name << "\n";
        std::cout << "Количество цехов: " << kol_tsex << "\n";
        std::cout << "Количество активных цехов: " << active_tsex << "\n";
        std::cout << "Класс станции: " << class_stan << "\n";
    }

    void work_cs() {
        if (flag) {
            std::cout << "\nСначала добавьте КС\n";
            return;
        }

        std::string input;
        int work;
        std::cout << "\nЗапустить или остановить цех КС " << name << ":\n";
        std::cout << "1 - запустить цех\n";
        std::cout << "2 - остановить цех\n";

        while (true) {
            std::cout << "Выберите действие: ";
            std::getline(std::cin, input);

            if (input == "1" || input == "2") {
                work = std::stoi(input);
                break;
            }
            std::cout << "Введите 1 или 2\n";
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

    void saveToFile(std::ofstream& out) const {
        if (flag) return;
        out << "CS\n";
        out << name << "\n";
        out << kol_tsex << "\n";
        out << active_tsex << "\n";
        out << class_stan << "\n";
    }

    void loadFromFile(std::ifstream& in) {
        flag = true;
        name = ""; kol_tsex = 0; active_tsex = 0; class_stan = 0;
        std::streampos pos = in.tellg();

        std::string marker;
        if (!std::getline(in, marker)) return;

        while (marker.empty() && std::getline(in, marker)) {}
        if (marker.empty()) return;

        if (marker != "CS") {
            in.seekg(pos);
            return;
        }

        std::string tempName;
        if (!std::getline(in, tempName)) return;
        if (tempName.empty()) return;

        name = tempName;

        if (!(in >> kol_tsex >> active_tsex >> class_stan)) return;

        flag = false;
        in.ignore(10000, '\n');
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Pipe pipe;
    CS cs;

    std::string inputStr;

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

        if (!std::getline(std::cin, inputStr)) break;

        if (inputStr.length() != 1 || !isdigit(inputStr[0])) {
            std::cout << "Введите одно число от 0 до 7.\n";
            continue;
        }

        int choice = inputStr[0] - '0';
        if (choice == 0) break;

        switch (choice) {
        case 1: pipe.read(); break;
        case 2: cs.read(); break;
        case 3:
            pipe.print();
            cs.print();
            break;
        case 4: pipe.ent_repair(); break;
        case 5: cs.work_cs(); break;
        case 6: {
            std::ofstream outFile("buraklr1.txt");
            if (outFile.is_open()) {
                pipe.saveToFile(outFile);
                cs.saveToFile(outFile);
                outFile.close();
                std::cout << "Данные сохранены в файл buraklr1.txt\n";
            }
            else { std::cout << "Ошибка открытия файла для записи\n"; }
            break;
        }
        case 7: {
            std::ifstream inFile("buraklr1.txt");
            if (inFile.is_open()) {
                pipe.loadFromFile(inFile);
                cs.loadFromFile(inFile);
                inFile.close();
                std::cout << "Данные загружены из buraklr1.txt\n";
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