#pragma once
#include <string>
#include <vector>
#include <map>
#include "Pipe.h"
#include "Cs.h"

int readInt(const std::string& prompt);
double readDouble(const std::string& prompt);
std::vector<int> findPipes(const std::map<int, Pipe>& pipes);
std::vector<int> findCS(const std::map<int, Cs>& stations);
