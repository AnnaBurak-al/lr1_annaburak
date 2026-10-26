#include "Manager.h"
#include "Utils.h"
#include "Logger.h"
#include <iostream>

using namespace std;

void managePipes(map<int, Pipe>& pipes) {
    auto found = findPipes(pipes);
    if (found.empty()) {
        cout << "Ничего не найдено.\n";
        return;
    }

    cout << "Найдено: " << found.size() << "\n";
    for (int id : found) cout << pipes.at(id) << endl;

    int act = readInt("Выберите действие: 1-В ремонт, 2-Из ремонта, 3-Удалить, 0-Отмена : ");
    if (act == 0) return;

    Logger::getInstance().log("Пакетная операция над трубами. Действие: " + to_string(act));
    for (int id : found) {
        if (act == 1 || act == 2) pipes.at(id).ent_repair();
        else if (act == 3) {
            pipes.erase(id);
            Logger::getInstance().log("Удалена труба ID=" + to_string(id));
        }
    }
}

void manageCS(map<int, Cs>& stations) {
    auto found = findCS(stations);
    if (found.empty()) {
        cout << "Ничего не найдено.\n";
        return;
    }

    cout << "Найдено: " << found.size() << "\n";
    for (int id : found) cout << stations.at(id) << endl;

    int act = readInt("Выберите действие: 1-Запуск цеха, 2-Остановка цеха, 3-Удалить, 0-Отмена : ");
    if (act == 0) return;

    Logger::getInstance().log("Пакетная операция над КС. Действие: " + to_string(act));
    for (int id : found) {
        if (act == 1) stations.at(id).startWorkshop();
        else if (act == 2) stations.at(id).stopWorkshop();
        else if (act == 3) {
            stations.erase(id);
            Logger::getInstance().log("Удалена КС ID=" + to_string(id));
        }
    }
}