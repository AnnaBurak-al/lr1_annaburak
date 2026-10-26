#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Logger.h"

class Pipe {
private:
    int id;
    std::string name;
    double length;
    int diametr;    
    bool repair;
    static int nextId;

public:
    Pipe();

    int getId() const;
    std::string getName() const;
    bool isRepair() const;

    void read();
    friend std::ostream& operator<<(std::ostream& os, const Pipe& p);

    void ent_repair();

    bool matchesName(const std::string& q) const;
    bool matchesRepair(bool state) const;

    void saveToFile(std::ofstream& out) const;
    bool loadFromFile(std::ifstream& in);
    static void updateNextId(int loadedId);
};