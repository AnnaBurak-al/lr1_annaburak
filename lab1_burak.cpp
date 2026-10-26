#include <iostream>
#include <string>
#include <clocale>
#include <fstream>
#include <map>
#include <limits>
#include "Logger.h"
#include "Pipe.h"
#include "Cs.h"
#include "Utils.h"      
#include "Manager.h"   

using namespace std;

int main() {

    setlocale(LC_ALL, "Russian");
    Logger::getInstance().log("ПРОГРАММА ЗАПУЩЕНА");

    map<int, Pipe> pipes;
    map<int, Cs> stations;

    while (true) {
        cout << "\nМеню\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить КС\n";
        cout << "3. Просмотр всех объектов\n";
        cout << "4. Поиск и пакетное редактирование\n";
        cout << "5. Сохранить в файл\n";
        cout << "6. Загрузить из файла\n";
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

        if (choice > 6) {
            cout << "Неверное число. Введите от 0 до 6.\n";
            continue;
        }

        if (choice == 0) {
            Logger::getInstance().log("ПРОГРАММА ЗАВЕРШЕНА");
            break;
        }

        switch (choice) {
        case 1: {
            Pipe p;
            p.read();
            pipes.emplace(p.getId(), p);
            break;
        }
        case 2: {
            Cs c;
            c.read();
            stations.emplace(c.getId(), c);
            break;
        }
        case 3: {
            if (!pipes.empty()) {
                cout << "\nВСЕ ТРУБЫ: \n";
                for (const auto& x : pipes) cout << x.second << endl;
            }
            else {
                cout << "\nТруба еще не создана\n";
            }

            if (!stations.empty()) {
                cout << "\nВСЕ КОМПРЕССОРНЫЕ СТАНЦИИ: \n";
                for (const auto& x : stations) cout << x.second << endl;
            }
            else {
                cout << "\nКомпрессорная станция еще не создана\n";
            }
            break;
        }
        case 4: {
            int t = readInt("Выберите с чем работаем: 1-Трубы, 2-КС. ");
            if (t == 1) 
                managePipes(pipes);
            else if (t == 2) 
                manageCS(stations);
            else 
                cout << "Неверный выбор.\n";
            break;
        }
        case 5: {
            string fname;
            cout << "Имя файла: ";
            cin >> fname;
            ofstream out(fname);
            if (!out.is_open()) { 
                cout << "Ошибка!\n"; 
                break; }

            out << pipes.size() << "\n";
            for (const auto& x : pipes) x.second.saveToFile(out);

            out << stations.size() << "\n";
            for (const auto& x : stations) x.second.saveToFile(out);
            out.close();

            Logger::getInstance().log("Сохранение в: " + fname);
            cout << "Сохранено.\n";
            break;
        }
        case 6: {
            string fname;
            cout << "Имя файла: ";
            cin >> fname;
            ifstream in(fname);
            if (!in.is_open()) { 
                cout << "Файл не найден!\n"; break; }

            pipes.clear();
            stations.clear();

            int pc, sc;

            if (!(in >> pc)) { 
                cout << "Ошибка файла!\n"; break; }
            in.ignore();
            for (int i = 0; i < pc; ++i) {
                Pipe p;
                if (p.loadFromFile(in)) 
                    pipes.emplace(p.getId(), p);
            }

            if (!(in >> sc)) { 
                cout << "Ошибка файла!\n"; break; }
            in.ignore();
            for (int i = 0; i < sc; ++i) {
                Cs c;
                if (c.loadFromFile(in)) 
                    stations.emplace(c.getId(), c);
            }
            in.close();

            Logger::getInstance().log("Загрузка из: " + fname);
            cout << "Загружено труб: " << pipes.size() << ", КС: " << stations.size() << "\n";
            break;
        }
        default:
            cout << "Неверный пункт.\n";
        }
    }
    return 0;
}