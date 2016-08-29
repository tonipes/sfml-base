#include "Logger.h"

Logger* Logger::m_instance = 0;

std::map<int, std::string> Logger::levels = {{0, "input"}, {1, "debug"}, {2, "info"}, {3, "warn"}, {4, "error"}};

Logger* Logger::instance() {
    if (!m_instance) {
        m_instance = new Logger;
    }

    return m_instance;

}

void Logger::addRow(int level, std::string text, bool print) {
    LogRow row ={level, text};
    rows.push_back(row);

    if(print){
        std::cout << getRowString(row) << "\n";
    }
}

std::string Logger::getRowString(LogRow &row) {
    auto level = row.level;
    auto text = row.text;

    if(level == 0){
        return ">> " + text;
    } else{
        return "[" + levels[level] + "] " + text;
    }
}