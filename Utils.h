#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <format>
#include <vector>
#include <unordered_map>
#include "Pipe.h"
#include "Cs.h"


#define LOG_PARAM(out, x) out << #x << "=" << x << std::endl

class redirect_output_wrapper {
    std::ostream& stream;
    std::streambuf* const old_buf;
public:
    explicit redirect_output_wrapper(std::ostream& src)
        : old_buf(src.rdbuf()), stream(src) {
    }

    ~redirect_output_wrapper() { stream.rdbuf(old_buf); }

    void redirect(std::ostream& dest) { 
        stream.rdbuf(dest.rdbuf()); }
};


inline std::string initLogging(redirect_output_wrapper& wrapper, std::ofstream& logfile) {

    auto now = std::chrono::system_clock::now();
    std::string time_str = std::format("{:%d_%m_%Y %H_%M_%OS}", now);
    std::string filename = "log_" + time_str;

    logfile.open(filename);
    if (logfile.is_open()) {
        wrapper.redirect(logfile);
        std::cerr << "Лабораторная работа запущена\n";
    }
    else {
        std::cerr << "ОШИБКА: Не удалось создать лог-файл!\n";
    }
    return filename; 
}

int readInt(const std::string& prompt);
double readDouble(const std::string& prompt);
std::vector<int> findPipes(const std::unordered_map<int, Pipe>& pipes);
std::vector<int> findCS(const std::unordered_map<int, Cs>& stations);