#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

int main() {
    static char cmd_buf[128];

    ImVec4 color = ImVec4(0,0,0,0);
    static float f = 0.0f;

    sf::RenderWindow window(sf::VideoMode(600, 600, 32), "Hello!");
//    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

//    sf::Font font;
//    font.loadFromFile("../OpenSans-Bold.ttf");
//    sf::Text text("Hello!", font, 11);

//    text.setFillColor(sf::Color::Black);
//    text.setCharacterSize(64);
//    text.setPosition(window.getSize().x/2 - text.getGlobalBounds().width/2,
//                     window.getSize().y/2 - text.getGlobalBounds().height/2);

    sf::Clock deltaClock;
    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if(event.type == sf::Event::Closed){
                window.close();
            }

            ImGui::SFML::Update(deltaClock.restart());

            ImGui::Begin("Hello, world!");

            ImGui::InputText("", cmd_buf, 128);

            if(ImGui::Button("Run")) {
                std::cout << "RUN: " << cmd_buf << "\n";
            }


            ImGui::SliderFloat("Float", &f, 0.0f, 1.0f);
            ImGui::ColorEdit3("Color", (float*)&color);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();

            window.clear(sf::Color::Blue);
//            window.draw(text);
            ImGui::Render();
            window.display();
        }
    }
    return 0;
}
