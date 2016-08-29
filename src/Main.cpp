#include "imgui.h"
#include "imgui-SFML.h"
#include "logger/Logger.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "ui/UIWindow.h"
#include "ui/UIConsoleWindow.h"

void runCommand(std::string str){
    // Just testing
    char *cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());

    char *array[10];
    int i=0;
    array[i] = strtok(cstr," ");
    while(array[i]!=NULL) {
        array[++i] = strtok(NULL," ");
    }
    if(std::string(array[0]).compare("echo") == 0 && str.length() > 5) {
        logInfo(str.substr(5, str.length()));
    } else {
        logError("Invalid command: \"" + str + "\"");
    }

}

int main() {
    logDebug("Starting main");
    logInfo("Starting main");
    logWarn("Starting main");
    logError("Starting main");
    ImVec4 c = ImVec4(0.25f, 0.25f, 0.25f, 0);

    std::function<void(std::string)> cmdCallback = [](std::string cmd){
        runCommand(cmd);
    };

    std::function<void()> color = [&c](){
        ImGui::ColorEdit3("Color", (float*)&c);
    };

    std::function<void()> buttons = [](){
        if(ImGui::Button("Add input")){
            Logger::instance()->addRow(0, "test input");
        }
        if(ImGui::Button("Add debug")){
            logDebug("test debug");
        }
        if(ImGui::Button("Add info")){
            logInfo("test info");
        }
        if(ImGui::Button("Add warn")){
            logWarn("test warn");
        }
        if(ImGui::Button("Add error")){
            logError("test error");
        }
    };

    std::function<void()> text = [](){
        ImGui::LabelText("Test", "fml");
        ImGui::LabelText("Another", "fml taas");
    };

    auto uiButtonGroup = new UILambdaGroup(buttons);
    auto uiTextGroup = new UILambdaGroup(text);
    auto uiColorGroup = new UILambdaGroup(color);

    auto uiButtonWindow = new UIGroupWindow("ButtonWindow");
    uiButtonWindow->groups.push_back(uiButtonGroup);

    auto uiTextWindow = new UIGroupWindow("TextWindow");
    uiTextWindow->groups.push_back(uiTextGroup);

    auto uiColorWindow = new UIGroupWindow("ColorWindow");
    uiColorWindow->groups.push_back(uiColorGroup);

    auto uiConsoleWindow = new UIConsoleWindow("ConsoleWindow", cmdCallback);

    auto uiWindowGroup = new UIWindowGroup();
    uiWindowGroup->windows.push_back(uiButtonWindow);
    uiWindowGroup->windows.push_back(uiTextWindow);
    uiWindowGroup->windows.push_back(uiColorWindow);
    uiWindowGroup->windows.push_back(uiConsoleWindow);

    sf::RenderWindow window(sf::VideoMode(600, 600, 32), "Hello!");
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if(event.type == sf::Event::Closed){
                window.close();
            }

            ImGui::SFML::Update(deltaClock.restart());

            uiWindowGroup->draw();

            window.clear(c);

            ImGui::Render();
            window.display();
        }
    }
    return 0;
}
