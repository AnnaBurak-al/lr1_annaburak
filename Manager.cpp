#include "Manager.h"
#include "Utils.h"
#include <iostream>
#include <unordered_map>

using namespace std;

void Manager::managePipes(unordered_map<int, Pipe>& pipes) {
    auto found = findPipes(pipes);
    if (found.empty()) {
        cout << "Ничего не найдено.\n";
        return;
    }

    cout << "Найдено: " << found.size() << "\n";
    for (int id : found) cout << pipes.at(id) << endl;

    int act = readInt("Выберите действие: 1-В ремонт, 2-Из ремонта, 3-Удалить, 0-Отмена : ");
    if (act == 0) return;

    cerr << "Пакетная операция над трубами. Действие: " << act << "\n";

    for (int id : found) {
        Pipe& p = pipes.at(id); 

        if (act == 1) {
            if (p.isRepair()) {
                cout << "Труба ID=" << id << " уже находится в ремонте.\n";
            }
            else {
                p.ent_repair(); 
            }
        }
        else if (act == 2) {
            if (!p.isRepair()) {
                cout << "Труба ID=" << id << " уже работает (не в ремонте).\n";
            }
            else {
                p.ent_repair(); 
            }
        }
        else if (act == 3) {
            pipes.erase(id);
            cerr << "Удалена труба ID=" << id << "\n";
            cout << "Труба ID=" << id << " удалена.\n";
        }
    }
}

void Manager::manageCS(unordered_map<int, Cs>& stations) {
    auto found = findCS(stations);
    if (found.empty()) {
        cout << "Ничего не найдено.\n";
        return;
    }

    cout << "Найдено: " << found.size() << "\n";
    for (int id : found) cout << stations.at(id) << endl;

    int act = readInt("Выберите действие: 1-Запуск цеха, 2-Остановка цеха, 3-Удалить, 0-Отмена : ");
    if (act == 0) return;

    cerr << "Пакетная операция над КС. Действие: " << act << "\n";
    for (int id : found) {
        if (act == 1) stations.at(id).startWorkshop();
        else if (act == 2) stations.at(id).stopWorkshop();
        else if (act == 3) {
            stations.erase(id);
            cerr << "Удалена КС ID=" << id << "\n";
        }
    }
}