//
// Created by Toni on 8/29/16.
//

#include <functional>
#include "UIWindow.h"
#include "../logger/Logger.h"

#ifndef CPP_CLION_TEST_UICONSOLEWINDOW_H
#define CPP_CLION_TEST_UICONSOLEWINDOW_H

#endif //CPP_CLION_TEST_UICONSOLEWINDOW_H

class UIConsoleOutputGroup: public UIGroup {
private:
    Logger* logger;
    unsigned long lastRowCount = 0;
public:
    UIConsoleOutputGroup(): logger(Logger::instance()) {};
protected:
    void drawInside(){
        ImGui::BeginChild("ScrollingRegion", ImVec2(0,-ImGui::GetItemsLineHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::BeginPopupContextWindow()) {
            ImGui::EndPopup();
        }
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(3,1));
        auto currentRowCount = logger->rows.size();

        for (auto row : logger->rows){
            auto str = logger->getRowString(*row).c_str();
            auto c = logger->getRowColor(*row).data();
            ImVec4 col = ImVec4(c[0], c[1], c[2], c[3]);

            ImGui::PushStyleColor(ImGuiCol_Text, col);
            ImGui::TextUnformatted(str);
            ImGui::PopStyleColor();
        }
        if(currentRowCount > lastRowCount)
            ImGui::SetScrollHere();
        lastRowCount = currentRowCount;
        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();
    };
};

class UIConsoleInputGroup: public UIGroup {
private:
    std::function<void(std::string)>& callFunc;
    char inputBuffer[256] = {'\0'};
public:
    UIConsoleInputGroup(std::function<void(std::string)>& callFunc_)
            : callFunc(callFunc_){
    };
protected:
    void drawInside(){
        if (ImGui::InputText("Input", inputBuffer, 256, ImGuiInputTextFlags_EnterReturnsTrue) && inputBuffer[0] != '\0'){
            Logger::instance()->addRow(0, std::string(inputBuffer));

            callFunc(std::string(inputBuffer));

            memset(&inputBuffer[0], 0, sizeof(inputBuffer));
            inputBuffer[0] = '\0';
        }

        if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    };
};

class UIConsoleWindow: public UIGroupWindow {
public:
    UIConsoleWindow(std::string name_, std::function<void(std::string)>& callFunc_);
};

UIConsoleWindow::UIConsoleWindow(std::string name_, std::function<void(std::string)> &callFunc_)
        : UIGroupWindow(name_){

    groups.push_back(new UIConsoleOutputGroup());
    groups.push_back(new UIConsoleInputGroup(callFunc_));

}