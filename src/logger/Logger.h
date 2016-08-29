#pragma once

#include <list>
#include <string>
#include <array>
#include <iostream>
#include <map>
#include <vector>


struct LogRow {
    int level;
    std::string text;
};

class Logger {
public:
    static std::map<int, std::string> levels;
    static std::map<int, std::array<float,4>> colors;
//    static std::map<int, std::vector<float>> colors;

    static Logger* instance();
    void addRow(int level, std::string text, bool print=true);
    void input(std::string str) { addRow(0, str.c_str()); }
    void debug(std::string str) { addRow(1, str.c_str()); }
    void info(std::string str) { addRow(2, str.c_str()); }
    void warn(std::string str) { addRow(3, str.c_str()); }
    void error(std::string str) { addRow(4, str.c_str()); }

    std::string getRowString(LogRow &row);
    std::array<float, 4> getRowColor(LogRow &row);
    std::list<LogRow*> rows;
private:

    Logger(){};
    Logger(Logger const&){};
    Logger& operator=(Logger const&){};
    static Logger* m_instance;
};

inline void logDebug(std::string str) { Logger::instance()->debug(str);}
inline void logInfo(std::string str) { Logger::instance()->info(str);}
inline void logWarn(std::string str) { Logger::instance()->warn(str);}
inline void logError(std::string str) { Logger::instance()->error(str);}