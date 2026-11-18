#include <iostream>
#include <string>
#include <clocale>
#include <fstream>
#include <unordered_map>
#include "Manager.h"
#include "Pipe.h"
#include "Cs.h"
#include "Utils.h"      


using namespace std;

void addPipe(unordered_map<int, Pipe>& pipes);
void addCs(unordered_map<int, Cs>& stations);
void viewAll(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Cs>& stations);
void searchAndEdit(unordered_map<int, Pipe>& pipes, unordered_map<int, Cs>& stations, Manager& manager);
void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Cs>& stations);
void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Cs>& stations);
void showLog(const string& logName);



void addPipe(unordered_map<int, Pipe>& pipes) {
    Pipe p;
    cin >> p; 
    pipes.emplace(p.getId(), p);
    cout << "Труба успешно добавлена.\n";
}

void addCs(unordered_map<int, Cs>& stations) {
    Cs c;
    cin >> c; 
    stations.emplace(c.getId(), c);
    cout << "КС успешно добавлена.\n";
}

void viewAll(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Cs>& stations) {
    if (!pipes.empty()) {
        cout << "\nВСЕ ТРУБЫ:\n";
        for (const auto& x : pipes) cout << x.second << endl;
    }
    else cout << "\nТрубы еще не созданы\n";

    if (!stations.empty()) {
        cout << "\nВСЕ КОМПРЕССОРНЫЕ СТАНЦИИ:\n";
        for (const auto& x : stations) cout << x.second << endl;
    }
    else cout << "\nКС еще не созданы\n";
}

void searchAndEdit(unordered_map<int, Pipe>& pipes, unordered_map<int, Cs>& stations, Manager& manager) {
    int t = readInt("Выберите объект: 1-Трубы, 2-КС. ");
    if (t == 1) manager.managePipes(pipes); 
    else if (t == 2) manager.manageCS(stations); 
    else cout << "Неверный выбор.\n";
}

void saveToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, Cs>& stations) {
    string fname;
    cout << "Имя файла: ";
    cin >> fname;
    ofstream out(fname);
    if (!out.is_open()) {
        cout << "Ошибка!\n"; return;
    }

    out << pipes.size() << "\n";
    for (const auto& x : pipes) x.second.saveToFile(out);
    out << stations.size() << "\n";
    for (const auto& x : stations) x.second.saveToFile(out);
    out.close();

    cerr << "Сохранение в: " << fname << "\n";
    cout << "Сохранено.\n";
}

void loadFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, Cs>& stations) {
    string fname;
    cout << "Имя файла: ";
    cin >> fname;
    ifstream in(fname);
    if (!in.is_open()) {
        cout << "Файл не найден!\n"; return;
    }

    pipes.clear();
    stations.clear();
    int pc, sc;
    if (!(in >> pc)) {
        cout << "Ошибка файла!\n"; return;
    }
    in.ignore();
    for (int i = 0; i < pc; ++i) {
        Pipe p;
        if (p.loadFromFile(in))
            pipes.emplace(p.getId(), p);
    }
    if (!(in >> sc)) {
        cout << "Ошибка файла!\n"; return;
    }
    in.ignore();
    for (int i = 0; i < sc; ++i) {
        Cs c;
        if (c.loadFromFile(in))
            stations.emplace(c.getId(), c);
    }
    in.close();

    cerr << "Загрузка из: " << fname << "\n";
    cout << "Загружено труб: " << pipes.size() << ", КС: " << stations.size() << "\n";
}

void showLog(const string& logName) {
    ifstream logFile(logName);
    if (!logFile.is_open()) {
        cout << "Ошибка чтения лога.\n";
        return;
    }

    cout << "\nЛОГ-ФАЙЛ (" << logName << ") \n";
    string line;
    while (getline(logFile, line)) {
        if (!line.empty())
            cout << line << "\n";
    }
}




int main() {
    setlocale(LC_ALL, "Russian");

    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile;
    string current_log_name = initLogging(cerr_out, logfile);

    if (!logfile.is_open()) 
        return 1;

    unordered_map<int, Pipe> pipes;
    unordered_map<int, Cs> stations;
    Manager manager; 


    while (true) {
        cout << "\nМеню\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить КС\n";
        cout << "3. Просмотр всех объектов\n";
        cout << "4. Поиск и пакетное редактирование\n";
        cout << "5. Сохранить в файл\n";
        cout << "6. Загрузить из файла\n";
        cout << "7. Считать с Logger\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";

        int choice;

        if (cin.peek() == '-') {
            cout << "Неверное число. Введите от 0 до 6.\n";
            cin.ignore(10000, '\n');
            continue;
        }

        if (!(cin >> choice) || cin.peek() != '\n') {
            cout << "Введите одно число от 0 до 6.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore(10000, '\n');

        if (choice > 7) {
            cout << "Неверное число. Введите от 0 до 7.\n";
            continue;
        }

        if (choice == 0) {
            cerr << "Программа завершена пользователем\n";
            break;
        }

        switch (choice) {
        case 1: addPipe(pipes); break;
        case 2: addCs(stations); break;
        case 3: viewAll(pipes, stations); break;
        case 4: searchAndEdit(pipes, stations, manager); break;
        case 5: saveToFile(pipes, stations); break;
        case 6: loadFromFile(pipes, stations); break;
        case 7: {
            cerr.flush();
            logfile.flush();

            ifstream logFile(current_log_name);

            if (!logFile.is_open()) {
                cout << "Ошибка чтения лога.\n";
                break;
            }

            cout << "\nЛОГ-ФАЙЛ (" << current_log_name << ") \n";
            string line;
            while (getline(logFile, line)) {
                if (!line.empty()) 
                    cout << line << "\n";
            }
            break;
        }
        default: cout << "Неверный пункт.\n";
        }
    }
    return 0;
}