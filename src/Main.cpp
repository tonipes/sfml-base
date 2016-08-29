#include "imgui.h"
#include "imgui-SFML.h"
#include "logger/Logger.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "ui/UIWindow.h"

int main() {
    logDebug("Starting main");

    auto buttonGroup = new UIButtonGroup();
    auto groupWindow = new UIGroupWindow("GroupWindow");
    groupWindow->groups.push_back(buttonGroup);

    char cmd_buf[16] = "";
    char log_buf[128] = "";

    ImVec4 color = ImVec4(0.25f, 0.25f, 0.25f, 0);
    static float f = 0.0f;

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

            ImGui::Begin("Controls");
            ImGui::PushItemWidth(-1);

            ImGui::InputText("", cmd_buf, 64);

            if(ImGui::Button("Add to log")) {
                if(strlen(log_buf) + strlen(cmd_buf) < 128){
                    strcat(log_buf, cmd_buf);
                    strcat(log_buf, "\n");
                }
            }

            ImGui::Checkbox("Show groupWindow", &groupWindow->visible);
            ImGui::Checkbox("Show buttonGroup", &buttonGroup->visible);

            ImGui::SliderFloat("Float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("Color", (float*)&color);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();

            ImGui::Begin("Log");
            ImGui::BeginGroup();

            ImGui::PushItemWidth(-1);
            ImGui::InputTextMultiline("Log", log_buf, 1024);

            if(ImGui::Button("Clear log")) {
                memset(&log_buf[0], 0, sizeof(log_buf));
            }
            ImGui::EndGroup();
            ImGui::End();

            groupWindow->draw();

//            consoleWindow->draw();

            window.clear(color);

            ImGui::Render();
            window.display();
        }
    }
    return 0;
}
