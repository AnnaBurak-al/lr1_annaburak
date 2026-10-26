#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "Logger.h"

class Cs {
private:
    int id;
    std::string name;
    int kol_tsex;     
    int active_tsex;  
    int class_stan;   
    static int nextId;

public:
    Cs();

    int getId() const;
    std::string getName() const;
    double getIdlePercent() const;

    void read();
    friend std::ostream& operator<<(std::ostream& os, const Cs& c);

    void work_cs();          
    void startWorkshop();    
    void stopWorkshop();     

    bool matchesName(const std::string& q) const;
    bool matchesIdle(double min) const;

    void saveToFile(std::ofstream& out) const;
    bool loadFromFile(std::ifstream& in);
    static void updateNextId(int loadedId);
};