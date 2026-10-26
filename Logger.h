#pragma once
#include <fstream>
#include <string>

class Logger {
private:
    std::ofstream logFile;

    Logger() {
        logFile.open("debug_log.txt", std::ios::app);
    }

public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void log(const std::string& msg) {
        if (logFile.is_open()) {
            logFile << msg << "\n";
        }
    }

    ~Logger() {
        if (logFile.is_open()) logFile.close();
    }
};