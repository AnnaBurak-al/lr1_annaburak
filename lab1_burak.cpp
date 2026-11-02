#include <iostream>
#include <string>
#include <clocale>
#include <fstream>
#include <unordered_map>
#include "Pipe.h"
#include "Cs.h"
#include "Utils.h"      
#include "Manager.h"  

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    redirect_output_wrapper cerr_out(cerr);
    ofstream logfile;
    string current_log_name = initLogging(cerr_out, logfile);

    if (!logfile.is_open()) 
        return 1;

    unordered_map<int, Pipe> pipes;
    unordered_map<int, Cs> stations;

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
        case 1: {
            Pipe p;
            p.read();
            pipes.emplace(p.getId(), p);
            cout << "Труба успешно добавлена.\n"; 
            break;
        }
        case 2: {
            Cs c; 
            c.read();
            stations.emplace(c.getId(), c);
            cout << "КС успешно добавлена.\n";
            break;
        }
        case 3: {
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
            break;
        }
        case 4: {
            int t = readInt("Выберите объект: 1-Трубы, 2-КС. ");
            if (t == 1) managePipes(pipes);
            else if (t == 2) manageCS(stations);
            else cout << "Неверный выбор.\n";
            break;
        }
        case 5: {
            string fname; 
            cout << "Имя файла: "; 
            cin >> fname;
            ofstream out(fname);
            if (!out.is_open()) { 
                cout << "Ошибка!\n"; break; }

            out << pipes.size() << "\n";
            for (const auto& x : pipes) x.second.saveToFile(out);
            out << stations.size() << "\n";
            for (const auto& x : stations) x.second.saveToFile(out);
            out.close();

            cerr << "Сохранение в: " << fname << "\n";
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

            cerr << "Загрузка из: " << fname << "\n";
            cout << "Загружено труб: " << pipes.size() << ", КС: " << stations.size() << "\n";
            break;
        }
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