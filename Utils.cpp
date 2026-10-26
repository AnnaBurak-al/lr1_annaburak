#include "Utils.h"
#include <iostream>

using namespace std;

int readInt(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) 
            return val;
        cout << "Введите целое число.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

double readDouble(const string& prompt) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val) 
            return val;
        cout << "Введите число.\n";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

vector<int> findPipes(const map<int, Pipe>& pipes) {
    vector<int> res;
    int ch = readInt("Поиск труб: 1-По названию, 2-По ремонту. Выбор: ");
    if (ch == 1) {
        string q;
        cout << "Название: ";
        getline(cin >> ws, q);
        for (const auto& p : pipes)
            if (p.second.matchesName(q)) 
                res.push_back(p.first);
    }
    else if (ch == 2) {
        int st = readInt("В ремонте? (1-Да, 0-Нет): ");
        for (const auto& p : pipes)
            if (p.second.matchesRepair(st == 1)) 
                res.push_back(p.first);
    }
    return res;
}

vector<int> findCS(const map<int, Cs>& stations) {
    vector<int> res;
    int ch = readInt("Поиск КС: 1-По названию, 2-По % незадействованных цехов. Выбор: ");
    if (ch == 1) {
        string q;
        cout << "Название: ";
        getline(cin >> ws, q);
        for (const auto& s : stations)
            if (s.second.matchesName(q)) 
                res.push_back(s.first);
    }
    else if (ch == 2) {
        double pct = readDouble("Мин. % незадействованных цехов: ");
        for (const auto& s : stations)
            if (s.second.matchesIdle(pct)) 
                res.push_back(s.first);
    }
    return res;
}