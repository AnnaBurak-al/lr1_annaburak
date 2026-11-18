#pragma once
#include <unordered_map>
#include "Pipe.h"
#include "Cs.h"

class Manager {
public:
    void managePipes(std::unordered_map<int, Pipe>& pipes);
    void manageCS(std::unordered_map<int, Cs>& stations);
};