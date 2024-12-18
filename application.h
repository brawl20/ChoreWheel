#pragma once

#include <list>
    using std::list;
#include <string>
    using std::string;
#include <utility>
    using std::pair;
#include <array>
    using std::array;
#include <filesystem>
    using std::filesystem::path;
    using std::filesystem::file_status;
    using std::filesystem::exists;

#include "imgui/imgui.h"

#include "users.h"
#include "tasks.h"
#include "schedules.h"

class App
{
public:
    void buildWindow(bool *show_demo);
    void RestoreModal();
    void menuBar(bool *show_demo);
    void absentUserPopup();
    void addUserPopup();
    void addTaskPopup();
    void taskToUserPopup();
    void removeTaskFromUserPopup();
    void showUserIncompletes();

private:
    Schedules schedules;
    list<pair<char const*, char const*>> scheduleDocket;
    ImGuiIO *io;
    void BuildTasksByPerson();
    void GetUserData();
};