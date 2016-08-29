#include "Logger.h"
#include <array>


Logger* Logger::m_instance = 0;

std::map<int, std::string> Logger::levels = {{0, "input"}, {1, "debug"}, {2, "info "}, {3, "warn "}, {4, "error"}};
std::map<int, std::array<float, 4>> Logger::colors = {
        {0, {0.9f, 0.75f, 0.75f, 0.75f}},
        {1, {0.75f, 0.75f, 0.75f, 0.75f}},
        {2, {0.6f, 0.6f, 0.9f, 1.0f}},
        {3, {1.0f, 0.5f, 0.0f, 1.0f}},
        {4, {1.0f, 0.0f, 0.0f, 1.0f}}
};

Logger* Logger::instance() {
    if (!m_instance) {
        m_instance = new Logger;
    }

    return m_instance;

}

void Logger::addRow(int level, std::string text, bool print) {
    auto row = new LogRow;
    row->text = text;
    row->level = level;
    rows.push_back(row);

    if(print){
        std::cout << getRowString(*row) << "\n";
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

std::array<float, 4> Logger::getRowColor(LogRow &row) {
    auto level = row.level;
    return colors[level];
}